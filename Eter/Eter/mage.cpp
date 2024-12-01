//mage.cpp
module mage;
import board;
import player;
import <iostream>;
import <stdexcept>;
import <unordered_map>;
import <functional>;
import <optional>;
using eter::Mage;
using eter::Board;
using eter::Player;

Mage::Mage(MagicAbility ability) : m_ability(ability), m_used(false) {}

bool Mage::isUsed() {
	return m_used;
}

Mage::MagicAbility Mage::GetAbility() const {
	return m_ability;
}

//Constructor de copiere
Mage::Mage(const Mage& other)
	: m_ability(other.m_ability), m_used(other.m_used) {
}

//Operator de atribuire prin copiere
Mage& Mage::operator=(const Mage& other) {
	if (this != &other) {
		m_ability = other.m_ability;
		m_used = other.m_used;
	}
	return *this;
}

// Constructor de mutare
Mage::Mage(Mage&& other) noexcept
	: m_ability(std::move(other.m_ability)), m_used(other.m_used) {
	other.m_used = false; // Resetez starea obiectului mutat
}

// Operator de atribuire prin mutare
Mage& Mage::operator=(Mage&& other) noexcept {
	if (this != &other) {
		m_ability = std::move(other.m_ability);
		m_used = other.m_used;
		other.m_used = false; // Resetez starea obiectului mutat
	}
	return *this;
}

// Destructor
Mage::~Mage() {}

//descriere abilitati
const std::unordered_map<Mage::MagicAbility, std::string> abilityDescriptions = {
	{ Mage::MagicAbility::removeOpponentCard, "Remove from play an opponent’s card that covers one of your cards." },
	{ Mage::MagicAbility::removeEntireLine, "Remove all cards from a specific row or column on the board." },
	{ Mage::MagicAbility::coverOpponentCard, "Cover one of your opponent's cards with your own card." },
	{ Mage::MagicAbility::createPit, "Create a pit on the board that removes all cards from that position." },
	{ Mage::MagicAbility::moveOwnStack, "Move one of your own stacks to another position on the board." },
	{ Mage::MagicAbility::extraEterCard, "Add an extra Ether card to your hand." },
	{ Mage::MagicAbility::moveOpponentStack, "Move one of your opponent's stacks to a different position." },
	{ Mage::MagicAbility::shiftRowToEdge, "Shift a row of cards to the edge of the board." }
};

// Gasirea pozitiei unei carti pe tabla
std::optional<std::pair<size_t, size_t>> Mage::findCardPosition(const Card& card, Board& board) {
	for (size_t i = 0; i < board.GetRows(); ++i) {
		for (size_t j = 0; j < board.GetCols(); ++j) {
			if (auto& cellOpt = board[{i, j}]; cellOpt.has_value() && !cellOpt->empty()) {
				if (cellOpt->top() == card) {
					return std::make_pair(i, j);
				}
			}
		}
	}
	return std::nullopt;
}

// Eliminare carte dintr-o celula a tablei
void Mage::removeCardFromBoard(std::optional<std::stack<Card>>& stack) {
	if (stack.has_value() && !stack->empty()) {
		stack->pop();
		std::cout << "Card removed.\n";
	}
}

// Mutare teanc intre doua pozitii
void Mage::moveStack(const std::pair<int, int>& from, const std::pair<int, int>& to, Board& board) {
	if (from != to && board.isValidPosition(to.first, to.second)) {
		board[to] = board[from];
		board[from].reset();
		std::cout << "Stack moved from (" << from.first << ", " << from.second << ") to (" << to.first << ", " << to.second << ").\n";
	}
}

// Activare abilitate
void Mage::activate(Player& player, Player& opponent, Board& board) {
	if (isAbilityUsed()) {
		throw std::runtime_error("The ability has already been used!");
	}

	displayAbilityDescription();  // Afiseaza descrierea abilitatii

	if (!confirmAbilityActivation()) {  // Confirmarea utilizatorului
		cancelAbilityActivation();
		return;
	}
	std::cout << "P color " << player.GetColor() << " OP color" << opponent.GetColor() << '\n';
	bool success = false;  // Indicator pentru activarea cu succes a abilitatii
	success = executeAbility(player, opponent, board);  // Incearca activarea abilitatii
	std::cout << "success is: " << success << '\n';
	if (success) {
		updateAbilityUsage();  // Actualizeaza contorul utilizarii
		notifyAbilityActivated();  // Notificare de succes
	}
	else
		std::cout << "The ability was not activated successfully. Please try again.\n";
}

// Eliminare carte a oponentului
void Mage::removeOpponentCard(Player& player, Player& opponent, Board& board) {
	std::cout << "Activating ability: Remove Opponent Card\n";

	size_t row, col;
	bool validPosition = false;
	while (!validPosition) {
		std::cout << "Enter the position (row, column) of the opponent's card to cover: ";
		std::cin >> row >> col;
		if (!board.isValidPosition(row, col)) {
			std::cout << "Invalid position (" << row << ", " << col << ") on the board. Try again.\n";
			continue;
		}
		auto& cell = board[{row, col}];
		if (!cell.has_value() || cell->empty()) {
			std::cout << "No card found at position (" << row << ", " << col << "). Try again.\n";
			continue;  // Retry input
		}
		if (cell.has_value() && cell.value().top().GetColor() != opponent.GetColor()) {
			std::cout << "The top card at (" << row << ", " << col << ") is not an opponent's card. Try again.\n";
			continue;
		}
		validPosition = true;
	}
	auto& selectedCell = board[{row, col}];
	const Card cardToRemove = selectedCell.value().top();
	selectedCell->pop(); // Elimina cartea de sus din stiva
	if (!selectedCell->empty())
	{
		Card belowTop = selectedCell.value().top();
		if (belowTop.GetColor() == player.GetColor())
		{
			opponent.AddToEliminatedCards(selectedCell.value().top());
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
		selectedCell.reset(); // Reseteaza celula daca stiva devine goala
}

void eter::Mage::removeEntireLine(Player& player, Board& board) {
	std::cout << "Activating ability: Remove Entire Row or Column\n";
	char choice;
	std::cout << "Introduce R to remove row, C to remove column:";
	std::cin >> choice;
	if (toupper(choice) == 'R')
		removeEntireRow(player, board);
	else if (toupper(choice) == 'C')
		removeEntireColumn(player, board);
	else std::cout << "ERROR\n";
}

// Eliminare rand intreg
void eter::Mage::removeEntireRow(Player& player, Board& board) {
	std::cout << "Activating ability: Remove Entire Row\n";

	// Solicita utilizatorului randul pe care doreste sa-l elimine
	size_t row;
	bool validRow = false;
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
	size_t selectedRow = row;
	board.eliminateCardsOnRow(row);
	std::cout << "Row " << row << " has been removed!\n";
}

void eter::Mage::removeEntireColumn(Player& player, Board& board) {
	std::cout << "Activating ability: Remove Entire Column\n";

	// Solicita utilizatorului randul pe care doreste sa-l elimine
	size_t col;
	bool validCol = false;
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
	size_t selectedCol = col;
	board.eliminateCardsOnColumn(col);
	std::cout << "Column " << col << " has been removed!\n";
}

// Acoperire carte adversar
void Mage::coverOpponentCard(Player& player, Player& opponent, Board& board) {
	std::cout << "Activating ability: Cover Opponent Card\n";

	size_t row, col;
	bool validPosition = false;
	while (!validPosition) {
		std::cout << "Enter the position (row, column) of the opponent's card to cover: ";
		std::cin >> row >> col;
		if (!board.isValidPosition(row, col)) {
			std::cout << "Invalid position (" << row << ", " << col << ") on the board. Try again.\n";
			continue;
		}
		auto& cell = board[{row, col}];
		if (!cell.has_value() || cell->empty()) {
			std::cout << "No card found at position (" << row << ", " << col << "). Try again.\n";
			continue;  // Retry input
		}
		if (cell.value().top().GetColor() != opponent.GetColor()) {
			std::cout << opponent.GetColor() << " " << player.GetColor() << " ";
			std::cout << "The top card at (" << row << ", " << col << ") is not an opponent's card. Try again.\n";
			continue;
		}
		validPosition = true;
	}
	auto& selectedCell = board[{row, col}];
	const Card& opponentCard = selectedCell->top();
	// Afiseaza cartile din mana jucatorului
	player.PrintCardsInHand();
	size_t cardIndex;
	bool validCardIndex = false;
	while (!validCardIndex) {
		std::cout << "Introduce card index of the card you want to place: ";
		std::cin >> cardIndex;
		if (cardIndex >= player.GetCardsInHand().size()) {
			std::cout << "Invalid card index. Try again.\n";
			continue;
		}
		const Card& playerCard = player.GetCardsInHand().at(cardIndex);
		if (playerCard.GetValue() >= opponentCard.GetValue()) {
			std::cout << "The selected card must have a lower value than the opponent's card. Try again.\n";
			continue;
		}
		validCardIndex = true;
	}
	const Card& selectedCard = player.GetCardsInHand().at(cardIndex);
	selectedCell->push(selectedCard); // Pune cartea in stiva
	// Elimina cartea din mana jucatorului
	player.GetCardsInHand().erase(player.GetCardsInHand().begin() + cardIndex);
	player.AddPlayedCard(selectedCard); // Adauga cartea la cele jucate
	std::cout << "Card placed successfully at (" << row << ", " << col << ").\n";
}

// Creare groapa
void Mage::createPit(Board& board) {
	std::cout << "Activating ability: Create Pit\n";

	int row, col;
	std::cout << "Enter the position (row, column) where you want to create a pit: ";
	std::cin >> row >> col;

	if (!board.isValidPosition(row, col)) {
		std::cout << "Invalid position (" << row << ", " << col << ").\n";
		return;
	}

	auto& cell = board[{row, col}];
	if (cell.has_value() && !cell->empty()) {
		std::cout << "Cannot create a pit at (" << row << ", " << col << ") because it is occupied.\n";
		return;
	}

	cell.reset(); // Creeaza groapa prin golirea celulei
	std::cout << "Pit created at (" << row << ", " << col << ").\n";
}


// Adaugare carte Eter
void Mage::addExtraEterCard(Player& player, Board& board) {
	std::cout << "Activating ability: Add Extra Ether Card\n";

	size_t row, col;

	// Solicita utilizatorului sa introduca pozitia unde va fi plasata cartea
	while (true) {
		std::cout << "Enter the position (row, column) to place the Ether card: ";
		std::cin >> row >> col;

		// Verifica daca pozitia este valida
		if (!board.isValidPosition(row, col)) {
			std::cout << "Invalid position (" << row << ", " << col << ") on the board. Try again.\n";
			continue;
		}

		// Verifica daca pozitia este goala
		if (board[{row, col}].has_value()) {
			std::cout << "The position (" << row << ", " << col << ") is not empty. Try again.\n";
			continue;
		}

		// Daca pozitia este valida si goala, iesi din bucla
		break;
	}

	// Creeaza o carte Eter si o plaseaza pe tabla
	Card etherCard(1, "eter", true);
	board.placeCard(row, col, etherCard);

	std::cout << "Extra Ether card placed at (" << row << ", " << col << ").\n";
}


// Mutare teanc propriu
void Mage::moveOwnStack(Player& player, Board& board) {
	std::cout << "Activating ability: Move Own Stack\n";

	size_t fromRow, fromCol, toRow, toCol;
	bool isFromValid = false;
	while (!isFromValid) {
		std::cout << "Enter the original position (row, column) of the stack: ";
		std::cin >> fromRow >> fromCol;
		std::cout << "player color: " << player.GetColor() << '\n';
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
		isFromValid = true;
	}
	bool isToValid = false;
	while (!isToValid) {
		std::cout << "Enter the destination position (row, column): ";
		std::cin >> toRow >> toCol;
		auto& toCell = board[{toRow, toCol}];
		if (toCell.has_value()) {
			std::cout << "Destination position is not empty.\n";
			continue;
		}
		isToValid = true;
	}
	auto& srcCell = board[{fromRow, fromCol}];
	auto& destCell = board[{toRow, toCol}];
	destCell = std::move(srcCell); // Muta teancul
	srcCell.reset();             // Goleste pozitia sursa
	std::cout << "Stack moved from (" << fromRow << ", " << fromCol << ") to (" << toRow << ", " << toCol << ").\n";
}

// Mutare teanc adversar
void Mage::moveOpponentStack(Player& player, Player& opponent, Board& board) {
	std::cout << "Activating ability: Move Opponent's Stack\n";

	size_t fromRow, fromCol, toRow, toCol;
	bool isFromValid = false;
	while (!isFromValid) {
		std::cout << "Enter the original position (row, column) of the opponent's stack: ";
		std::cin >> fromRow >> fromCol;

		if (!board.isValidPosition(fromRow, fromCol)) {
			std::cout << "Invalid position! Try again.\n";
			continue;
		}

		auto& fromCell = board[{fromRow, fromCol}];
		if (!fromCell.has_value() || fromCell->empty()) {
			std::cout << "No stack found at the original position.\n";
			continue;
		}
		std::cout << "op color: " << opponent.GetColor() << " p color " << player.GetColor();
		if (!board.containsOpponentCardsOnCell(fromRow, fromCol, opponent.GetColor())) {
			std::cout << "The original cell doesn't contain opponent's cards at all.\n";
			continue;
		}

		isFromValid = true;
	}
	bool isToValid = false;
	while (!isToValid) {
		std::cout << "Enter the destination position (row, column): ";
		std::cin >> toRow >> toCol;

		if (!board.isValidPosition(toRow, toCol)) {
			std::cout << "Invalid position! Try again.\n";
			continue;
		}

		auto& toCell = board[{toRow, toCol}];
		if (toCell.has_value()) {
			std::cout << "Destination position is not empty.\n";
			continue;
		}

		isToValid = true;
	}
	auto& srcCell = board[{fromRow, fromCol}];
	auto& destCell = board[{toRow, toCol}];
	destCell = std::move(srcCell); // Move the stack to the destination
	srcCell.reset();               // Clear the source cell

	std::cout << "Opponent's stack moved from (" << fromRow << ", " << fromCol
		<< ") to (" << toRow << ", " << toCol << ").\n";
}


// Mutare rand la marginea tablei
void Mage::shiftRowToEdge(Board& board) {
	std::cout << "Activating ability: Shift Row to Edge\n";

	int fromRow, toRow;

	// Solicita utilizatorului randul de plecare
	while (true) {
		std::cout << "Enter the row number to move (must be on the edge): ";
		std::cin >> fromRow;

		// Verifica daca randul este la margine
		if (fromRow != 0 && fromRow != board.GetRows() - 1) {
			std::cout << "Invalid row. You can only move rows on the edges (0 or "
				<< board.GetRows() - 1 << "). Try again.\n";
			continue;
		}

		// Verifica daca randul are cel putin 3 pozitii ocupate
		int occupiedCount = 0;
		for (size_t col = 0; col < board.GetCols(); ++col) {
			if (board[{fromRow, col}].has_value()) {
				++occupiedCount;
			}
		}

		if (occupiedCount < 3) {
			std::cout << "The selected row must have at least 3 occupied positions. Try again.\n";
			continue;
		}

		break;
	}

	// Solicita utilizatorului randul de destinatie
	while (true) {
		std::cout << "Enter the destination row (must be on the edge): ";
		std::cin >> toRow;

		// Verifica daca randul de destinatie este la margine si diferit de cel de plecare
		if ((toRow != 0 && toRow != board.GetRows() - 1) || toRow == fromRow) {
			std::cout << "Invalid destination row. You can only move to the opposite edge (0 or "
				<< board.GetRows() - 1 << ") and not the same as the source row. Try again.\n";
			continue;
		}

		break;
	}

	// Muta randul
	for (size_t col = 0; col < board.GetCols(); ++col) {
		if (board[{fromRow, col}].has_value()) {
			board[{toRow, col}] = board[{fromRow, col}];
			board[{fromRow, col}].reset();
		}
	}

	std::cout << "Row " << fromRow << " moved to row " << toRow << ".\n";
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
	case MagicAbility::shiftRowToEdge: return "Shift Row to Edge";
	default: return "Unknown Ability";
	}
}

//Functii ajutatoare
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
	static const std::unordered_map<MagicAbility, std::function<void()>> abilityMap = {
		{ MagicAbility::removeOpponentCard, [&]() { removeOpponentCard(player,  opponent, board); } },
		{ MagicAbility::removeEntireLine,    [&]() { removeEntireLine(player, board); } },
		{ MagicAbility::coverOpponentCard,   [&]() { coverOpponentCard(player,  opponent, board); } },
		{ MagicAbility::createPit,          [&]() { createPit(board); } },
		{ MagicAbility::moveOwnStack,       [&]() { moveOwnStack(player, board); } },
		{ MagicAbility::extraEterCard,      [&]() { addExtraEterCard(player, board); } },
		{ MagicAbility::moveOpponentStack,  [&]() { moveOpponentStack(player, opponent, board); } },
		{ MagicAbility::shiftRowToEdge,     [&]() { shiftRowToEdge(board); } }
	};

	auto abilityIt = abilityMap.find(m_ability);
	if (abilityIt != abilityMap.end()) {
		if (abilityIt->second) { // Check if the function pointer or callable object exists
			abilityIt->second();  // Activate the ability
			return true;          // Success
		}
		else {
			std::cout << "Couldn't activate ability\n";
			return false;         // Failure due to missing callable
		}
	}
	else {
		std::cout << "Unknown ability\n";
		return false;             // Failure for unknown ability
	}

}

void Mage::updateAbilityUsage() {
	++abilityUsage[m_ability];
	m_used = true;
}

void Mage::notifyAbilityActivated() const {
	std::cout << "Ability successfully activated.\n";
}
