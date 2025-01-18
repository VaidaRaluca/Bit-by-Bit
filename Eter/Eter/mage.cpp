
#include "Board.h"
#include "Player.h"
module mage;
import <iostream>;
import <stdexcept>;
import <unordered_map>;
import <functional>;
import <optional>;
using eter::Mage;
using eter::Board;
using eter::Player;
using eter::Card;

Mage::Mage(MagicAbility ability) : m_ability(ability), m_used(false) {}

bool Mage::isUsed() {
	return m_used;
}

Mage::MagicAbility Mage::GetAbility() const {
	return m_ability;
}


Mage::Mage(const Mage& other)
	: m_ability{ other.m_ability }, m_used{ other.m_used } {
}


Mage& Mage::operator=(const Mage& other) {
	Mage temp{ other };
	swap(temp);
	return *this;
}


Mage::Mage(Mage&& other) noexcept
{
	this->swap(other);
}


Mage& Mage::operator=(Mage&& other) noexcept {
	this->swap(other);
	return *this;
}


Mage::~Mage() {}

void Mage::swap(Mage& other) noexcept
{
	MagicAbility tempAbility = m_ability;
	m_ability = other.m_ability;
	other.m_ability = tempAbility;

	bool tempUsed = m_used;
	m_used = other.m_used;
	other.m_used = tempUsed;
}


const std::unordered_map<Mage::MagicAbility, std::string> abilityDescriptions = {
	{ Mage::MagicAbility::removeOpponentCard, "Remove from play an opponent’s card that covers one of your cards." },
	{ Mage::MagicAbility::removeEntireLine, "Remove all cards from a specific row or column on the board." },
	{ Mage::MagicAbility::coverOpponentCard, "Cover one of your opponent's cards with your own card." },
	{ Mage::MagicAbility::createPit, "Create a pit on the board that removes all cards from that position." },
	{ Mage::MagicAbility::moveOwnStack, "Move one of your own stacks to another position on the board." },
	{ Mage::MagicAbility::extraEterCard, "Use an extra ETER card." },
	{ Mage::MagicAbility::moveOpponentStack, "Move one of your opponent's stacks to a different position." },
	{ Mage::MagicAbility::shiftEdge, "Shift a row or column from one edge to another." }
};



void Mage::activate(Player& player, Player& opponent, Board& board) {
	if (isAbilityUsed()) {
		std::cout << "The ability has already been used!\n";
		return;
	}

	displayAbilityDescription();  

	if (!confirmAbilityActivation()) {  
		cancelAbilityActivation();
		return;
	}
	bool success{ false };  
	success = executeAbility(player, opponent, board);  
	std::cout << "success is: " << success << '\n';
	if (success) {
		updateAbilityUsage();  
		notifyAbilityActivated();  
	}
	else
		std::cout << "The ability was not activated successfully. Please try again.\n";
}


void Mage::removeOpponentCard(Player& player, Player& opponent, Board& board) {
	std::cout << "Activating ability: Remove Opponent Card\n";

	size_t row, col;
	bool validPosition{ false };
	while (!validPosition) 
	{
		std::cout << "Enter the position (row, column) of the opponent's card to cover: ";
		std::cin >> row >> col;
		if (!board.isValidPosition(row, col))
		{
			std::cout << "Invalid position (" << row << ", " << col << ") on the board. Try again.\n";
			continue;
		}
		auto& cell{ board[{row, col}] };
		if (!cell.has_value() || cell->empty()) {
			std::cout << "No card found at position (" << row << ", " << col << "). Try again.\n";
			continue;  
		}
		if (cell.has_value() && cell.value().top().GetColor() != opponent.GetColor()) {
			std::cout << "The top card at (" << row << ", " << col << ") is not an opponent's card. Try again.\n";
			continue;
		}
		validPosition = true;
	}
	auto& selectedCell{ board[{row, col}] };
	const Card& cardToRemove{ selectedCell.value().top() };
	selectedCell->pop();
	if (!selectedCell->empty())
	{
		const Card& belowTop{ selectedCell.value().top() };
		if (belowTop.GetColor() == player.GetColor())
		{
			opponent.addToEliminatedCards(selectedCell.value().top());
			std::cout << "Opponent's card removed from (" << row << ", " << col << ").\n";
		}
		else
		{
			selectedCell->push(cardToRemove);
			std::cout << "Opponent's card does not cover yours\n";
			std::cout << selectedCell.value().top().GetColor() << " ";

		}
	}
	else
	{
		selectedCell->push(cardToRemove);
		std::cout << "There's no card of yours underneath opponent's.\n";

	}

	if (selectedCell->empty())
		selectedCell.reset(); 
}

void eter::Mage::removeEntireLine(Player& player, Board& board) {
	std::cout << "Activating ability: Remove Entire Row or Column\n";
	char choice;
	std::cout << "Introduce R to remove row, C to remove column: ";
	std::cin >> choice;
	if (toupper(choice) == 'R')
		removeEntireRow(player, board);
	else if (toupper(choice) == 'C')
		removeEntireColumn(player, board);
	else std::cout << "ERROR\n";
}


void eter::Mage::removeEntireRow(Player& player, Board& board) {
	std::cout << "Activating ability: Remove Entire Row\n";

	size_t row;
	bool validRow{ false };
	while (!validRow) {
		std::cout << "Enter the row number to remove: ";
		std::cin >> row;
		if (!board.isValidRow(row)) {
			std::cout << "Invalid row number.\n";
			continue;
		}
		if (!board.containsOwnCardOnRow(row, player.GetColor()))
		{
			std::cout << "The row must contain at least one of your own visible cards.\n";
			continue;
		}
		if (board.countOccupiedCellsOnRow(row) < 3) {
			std::cout << "The row must have at least 3 occupied positions.\n";
			continue;
		}
		validRow = true;
	}
	size_t selectedRow{ row };
	board.eliminateCardsOnRow(row);
	board.updateAfterRemoval();
	std::cout << "Row " << row << " has been removed!\n";
}

void eter::Mage::removeEntireColumn(Player& player, Board& board) {
	std::cout << "Activating ability: Remove Entire Column\n";

	size_t col;
	bool validCol{ false };
	while (!validCol) {
		std::cout << "Enter the column number to remove: ";
		std::cin >> col;
		if (!board.isValidColumn(col)) {
			std::cout << "Invalid row number.\n";
			continue;
		}
		if (!board.containsOwnCardOnColumn(col, player.GetColor()))
		{
			std::cout << "The column must contain at least one of your own visible cards.\n";
			continue;
		}
		if (board.countOccupiedCellsOnColumn(col) < 3) {
			std::cout << "The column must have at least 3 occupied positions.\n";
			continue;
		}
		validCol = true;
	}
	size_t selectedCol{ col };
	board.eliminateCardsOnColumn(col);
	board.updateAfterRemoval();
	std::cout << "Column " << col << " has been removed!\n";
}

void Mage::coverOpponentCard(Player& player, Player& opponent, Board& board) {
	std::cout << "Activating ability: Cover Opponent Card\n";

	size_t row, col;
	bool validPosition{ false };
	while (!validPosition) {
		std::cout << "Enter the position (row, column) of the opponent's card to cover: ";
		std::cin >> row >> col;
		if (!board.isValidPosition(row, col)) {
			std::cout << "Invalid position (" << row << ", " << col << ") on the board. Try again.\n";
			continue;
		}
		auto& cell{ board[{row, col}] };
		if (!cell.has_value() || cell->empty()) {
			std::cout << "No card found at position (" << row << ", " << col << "). Try again.\n";
			continue;  
		}
		if (cell.value().top().GetColor() != opponent.GetColor()) {
			std::cout << opponent.GetColor() << " " << player.GetColor() << " ";
			std::cout << "The top card at (" << row << ", " << col << ") is not an opponent's card. Try again.\n";
			continue;
		}
		if (cell.value().top().GetValue() == '/') {
			std::cout << "Cell is a hole\n";
			continue;
		}
		if (cell.value().top().GetValue() == 5) {
			std::cout << "Cannot cover ETER card\n";
			continue;
		}
		validPosition = true;
	}
	auto& selectedCell{ board[{row, col}] };
	const Card& opponentCard { selectedCell->top()};
	player.printCardsInHand();
	size_t cardIndex;
	bool validCardIndex{ false };
	while (!validCardIndex) {
		std::cout << "Introduce card index of the card you want to place: ";
		std::cin >> cardIndex;
		if (cardIndex >= player.GetCardsInHand().size()) {
			std::cout << "Invalid card index. Try again.\n";
			continue;
		}
		const Card& playerCard{ player.GetCardsInHand().at(cardIndex) };
		if (playerCard.GetValue() >= opponentCard.GetValue()) {
			std::cout << "The selected card must have a lower value than the opponent's card. Try again.\n";
			continue;
		}
		validCardIndex = true;
	}
	const Card& selectedCard{ player.GetCardsInHand().at(cardIndex) };
	selectedCell->push(selectedCard); 
	player.GetCardsInHand().erase(player.GetCardsInHand().begin() + cardIndex);
	player.addPlayedCardForPower(selectedCard, row, col); 
	std::cout << "Card placed successfully at (" << row << ", " << col << ").\n";
}

void Mage::createPit(Board& board) {
	std::cout << "Activating ability: Create Pit\n";

	size_t row, col;
	bool validPosition{ false };
	while (!validPosition) {
		std::cout << "Enter the position (row, column) where you want to create a hole: ";
		std::cin >> row >> col;
		if (!board.isValidPosition(row, col)) {
			std::cout << "Invalid position (" << row << ", " << col << ") on the board. Try again.\n";
			continue;
		}
		auto& cell{ board[{row, col}] };
		if (!cell.has_value() || cell->empty()) {
			if (!board.isAdjacentToOccupiedSpace(row, col)) {
				std::cout << "The position is not adjacent to any occupied space. Choose another position.\n";
				continue;
			}
			else
				validPosition = true;
		}
		else if (cell.value().top().GetValue() == 5) {
			std::cout << "Cannot create pit where ETER card is already placed\n";
			continue;
		}
		validPosition = true;
	}
	board.createHole(row, col);
	std::cout << "Pit created at (" << row << ", " << col << ").\n";
}


void Mage::addExtraEterCard(Player& player, Board& board) {
	std::cout << "Activating ability: Add Extra Eter Card\n";
	size_t row, col;
	bool validPosition{ false };
	while (!validPosition) {
		std::cout << "Enter the position (row, column) where you wnat to place ETER card: ";
		std::cin >> row >> col;
		if (!board.isValidPosition(row, col)) {
			std::cout << "Invalid position (" << row << ", " << col << ") on the board. Try again.\n";
			continue;
		}
		auto& cell{ board[{row, col}] };
		if (!cell.has_value() || cell->empty()) {
			if (!board.isAdjacentToOccupiedSpace(row, col)) {
				std::cout << "The position is not adjacent to any occupied space. Choose another position.\n";
				continue;
			}
			else
				validPosition = true;
		}
		else
		{
			std::cout << "Eter cards can only be placed on empty cells. Position (" << row << ", " << col << ") is occupied.\n";
			continue;
		}
	}
	board[{row, col}] = std::stack<Card>{}; 
	board[{row, col}]->push(Card{ 5, player.GetColor(), true });
	std::cout << "Extra Eter card placed at (" << row << ", " << col << ").\n";
}


void Mage::moveOwnStack(Player& player, Board& board) {
	std::cout << "Activating ability: Move Own Stack\n";

	size_t fromRow, fromCol, toRow, toCol;
	bool isFromValid{ false };
	while (!isFromValid) {
		std::cout << "Enter the original position (row, column) of the stack: ";
		std::cin >> fromRow >> fromCol;
		auto& fromCell = board[{fromRow, fromCol}];
		if (!board.isValidPosition(fromRow, fromCol))
		{
			std::cout << "Invalid position! Try again.\n";
			continue;
		}
		if (!fromCell.has_value() || fromCell->empty()) {
			std::cout << "No stack found at the original position.\n";
			continue;
		}
		if (fromCell.value().top().GetColor() != player.GetColor()) {
			std::cout << "The card on top is not yours.\n";
			continue;
		}
		if (fromCell.has_value() && fromCell.value().top().GetValue() == 5) {
			std::cout << "Cannot move ETER card.\n";
			continue;
		}
		isFromValid = true;
	}
	bool isToValid{ false };
	while (!isToValid) {
		std::cout << "Enter the destination position (row, column): ";
		std::cin >> toRow >> toCol;
		auto& toCell = board[{toRow, toCol}];
		if (!board.isAdjacentToOccupiedSpace(toRow, toCol)) {
			std::cout << "The position is not adjacent to any occupied space. Choose another position.\n";
			continue;
		}
		if (toCell.has_value()) {
			std::cout << "Destination position is not empty.\n";
			continue;
		}
		isToValid = true;
	}
	auto& srcCell{ board[{fromRow, fromCol}] };
	auto& destCell{ board[{toRow, toCol}] };
	destCell = std::move(srcCell); 
	srcCell.reset();             
	std::cout << "Stack moved from (" << fromRow << ", " << fromCol << ") to (" << toRow << ", " << toCol << ").\n";
}

void Mage::moveOpponentStack(Player& opponent, Board& board) {
	std::cout << "Activating ability: Move Opponent's Stack\n";

	size_t fromRow, fromCol, toRow, toCol;
	bool isFromValid{ false };
	while (!isFromValid) {
		std::cout << "Enter the original position (row, column) of the opponent's stack: ";
		std::cin >> fromRow >> fromCol;

		if (!board.isValidPosition(fromRow, fromCol)) {
			std::cout << "Invalid position! Try again.\n";
			continue;
		}
		auto& fromCell{ board[{fromRow, fromCol}] };
		if (!fromCell.has_value() || fromCell->empty()) {
			std::cout << "No stack found at the original position.\n";
			continue;
		}
		std::cout << "op color: " << opponent.GetColor();
		if (fromCell.value().top().GetColor() != opponent.GetColor()) {
			std::cout << "The original cell doesn't contain opponent's cards at all.\n";
			continue;
		}
		if (fromCell.has_value() && fromCell.value().top().GetValue() == 5) {
			std::cout << "Cannot move ETER card.\n";
			continue;
		}
		isFromValid = true;
	}
	bool isToValid{ false };
	while (!isToValid) {
		std::cout << "Enter the destination position (row, column): ";
		std::cin >> toRow >> toCol;

		if (!board.isValidPosition(toRow, toCol)) {
			std::cout << "Invalid position! Try again.\n";
			continue;
		}

		if (!board.isAdjacentToOccupiedSpace(toRow, toCol)) {
			std::cout << "The position is not adjacent to any occupied space. Choose another position.\n";
			continue;
		}
		auto& toCell{ board[{toRow, toCol}] };
		if (toCell.has_value()) {
			std::cout << "Destination position is not empty.\n";
			continue;
		}
		isToValid = true;
	}
	auto& srcCell{ board[{fromRow, fromCol}] };
	auto& destCell{ board[{toRow, toCol} ]};
	destCell = std::move(srcCell); 
	srcCell.reset();              

	std::cout << "Opponent's stack moved from (" << fromRow << ", " << fromCol
		<< ") to (" << toRow << ", " << toCol << ").\n";
}

void eter::Mage::shiftEdge(Board& board)
{
	std::cout << "Activating ability: Shift a Row or Column from an Edge to another Edge\n";
	char choice;
	std::cout << "Introduce R to shift row, C to shift column: ";
	std::cin >> choice;
	if (toupper(choice) == 'R')
		shiftRowToEdge(board);
	else if (toupper(choice) == 'C')
		shiftColumnToEdge(board);
	else std::cout << "ERROR\n";
}


void eter::Mage::shiftRowToEdge(Board& board) {
	std::cout << "Activating ability: Shift Row to another Edge\n";
	size_t row;
	bool validRow{ false };
	while (!validRow) {
		std::cout << "Enter the row number to move: ";
		std::cin >> row;
		if (!board.isEdgeRow(row)) {
			std::cout << "Row is not on the edge.\n";
			continue;
		}
		if (board.countOccupiedCellsOnRow(row) < 3) {
			std::cout << "The row must have at least 3 occupied positions.\n";
			continue;
		}
		validRow = true;
	}
	bool destValidRow{ false };
	size_t destRow;
	while (!destValidRow)
	{
		std::cout << "Introduce the row number to which you want to move the row: ";
		std::cin >> destRow;
		if (!board.isEdgeRow(destRow)) {
			std::cout << "Row is not on the edge.\n";
			continue;
		}
		destValidRow = true;
	}
	board.moveRow(row, destRow);
	std::cout << "The row has been moved successfully\n";

}

void eter::Mage::shiftColumnToEdge(Board& board) {
	std::cout << "Activating ability: Shift Column to another Edge\n";
	size_t col;
	bool validCol{ false };
	while (!validCol) {
		std::cout << "Enter the column number to move: ";
		std::cin >> col;
		if (!board.isEdgeColumn(col)) {
			std::cout << "Column is not on the edge.\n";
			continue;
		}
		if (board.countOccupiedCellsOnColumn(col) < 3) {
			std::cout << "The column must have at least 3 occupied positions.\n";
			continue;
		}
		validCol = true;
	}
	bool destValidCol{ false };
	size_t destCol;
	while (!destValidCol)
	{
		std::cout << "Introduce the column number to which you want to move the row: ";
		std::cin >> destCol;
		if (!board.isEdgeColumn(destCol)) {
			std::cout << "Column is not on the edge.\n";
			continue;
		}
		destValidCol = true;
	}
	board.moveColumn(col, destCol);
	std::cout << "The column has been moved successfully\n";
}



std::unordered_map<Mage::MagicAbility, int> Mage::abilityUsage = {};

std::string Mage::abilityToString(MagicAbility ability) {
	switch (ability) {
	case MagicAbility::removeOpponentCard: return "Remove Opponent Card";
	case MagicAbility::removeEntireLine: return "Remove Entire Row or Column";
	case MagicAbility::coverOpponentCard: return "Cover Opponent Card";
	case MagicAbility::createPit: return "Create Pit";
	case MagicAbility::moveOwnStack: return "Move Own Stack";
	case MagicAbility::extraEterCard: return "Add Extra Ether Card";
	case MagicAbility::moveOpponentStack: return "Move Opponent Stack";
	case MagicAbility::shiftEdge: return "Shift a Row or Column from an Edge to another Edge";
	default: return "Unknown Ability";
	}
}

bool Mage::isAbilityUsed() const {
	return m_used;
}

void Mage::displayAbilityDescription() const {
	auto it = abilityDescriptions.find(m_ability);
	if (it != abilityDescriptions.end()) {
		std::cout << "You are about to activate the following ability:\n";
		std::cout << it->second << "\n";
	}
	else {
		std::cout << "Unknown ability. Proceeding with activation.\n";
	}
}

bool Mage::confirmAbilityActivation() const {
	char confirmation;
	std::cout << "Do you want to proceed with this ability? (Y/N): ";
	std::cin >> confirmation;
	return std::toupper(confirmation) == 'Y';
}

void Mage::cancelAbilityActivation() const {
	std::cout << "Ability activation canceled.\n";
}

bool Mage::executeAbility(Player& player, Player& opponent, Board& board) {
	static const std::unordered_map<MagicAbility, std::function<void(Player&, Player&, Board&)>> abilityMap = {
	{ MagicAbility::removeOpponentCard, [](Player& player, Player& opponent, Board& board) { removeOpponentCard(player, opponent, board); } },
	{ MagicAbility::removeEntireLine,   [](Player& player, Player&, Board& board) { removeEntireLine(player, board); } },
	{ MagicAbility::coverOpponentCard,  [](Player& player, Player& opponent, Board& board) { coverOpponentCard(player, opponent, board); } },
	{ MagicAbility::createPit,          [](Player&, Player&, Board& board) { createPit(board); } },
	{ MagicAbility::moveOwnStack,       [](Player& player, Player&, Board& board) { moveOwnStack(player, board); } },
	{ MagicAbility::extraEterCard,      [](Player& player, Player&, Board& board) { addExtraEterCard(player, board); } },
	{ MagicAbility::moveOpponentStack,  [](Player&, Player& opponent, Board& board) { moveOpponentStack(opponent, board); } },
	{ MagicAbility::shiftEdge,     [](Player&, Player&, Board& board) { shiftEdge(board); } }
	};


	auto abilityIt = abilityMap.find(m_ability);
	if (abilityIt != abilityMap.end()) {
		if (abilityIt->second) {
			abilityIt->second(player, opponent, board); 
			return true;
		}
		else {
			std::cout << "Couldn't activate ability\n";
			return false;
		}
	}
	else {
		std::cout << "Unknown ability\n";
		return false;
	}

}

void Mage::updateAbilityUsage() {
	++abilityUsage[m_ability];
	m_used = true;
}

void Mage::notifyAbilityActivated() const {
	std::cout << "Ability successfully activated.\n";
}
