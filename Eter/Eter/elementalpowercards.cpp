module elementalpowercards;
import board;
import player;
import card;
import <stdexcept>;
import <unordered_map>;
import <iostream>;

namespace eter{
	void swap(elementalPowerCards& first, elementalPowerCards& second) noexcept
	{
		using std::swap;
		swap(first.m_power, second.m_power);
		swap(first.m_used, second.m_used);
	}
	std::ostream& operator<<(std::ostream& os, elementalPowerCards::powerAbility ability) {
	switch (ability) {
	case elementalPowerCards::powerAbility::controlledExplosion:
		os << "Controlled Explosion";
		break;
	case elementalPowerCards::powerAbility::destruction:
		os << "Destruction";
		break;
	case elementalPowerCards::powerAbility::flame:
		os << "Flame";
		break;
	case elementalPowerCards::powerAbility::fire:
		os << "Fire";
		break;
	case elementalPowerCards::powerAbility::ash:
		os << "ASH";
		break;
	case elementalPowerCards::powerAbility::spark:
		os << "Spark";
		break;
	case elementalPowerCards::powerAbility::squall:
		os << "Squall";
		break;
	case elementalPowerCards::powerAbility::gale:
		os << "Gale";
		break;
	case elementalPowerCards::powerAbility::hurricane:
		os << "Hurricane";
		break;
	case elementalPowerCards::powerAbility::gust:
		os << "Gust";
		break;
	case elementalPowerCards::powerAbility::mirage:
		os << "Mirage";
		break;
	case elementalPowerCards::powerAbility::storm:
		os << "Storm";
		break;
	case elementalPowerCards::powerAbility::tide:
		os << "Tide";
		break;
	case elementalPowerCards::powerAbility::mist:
		os << "Mist";
		break;
	case elementalPowerCards::powerAbility::wave:
		os << "Wave";
		break;
	case elementalPowerCards::powerAbility::whirlpool:
		os << "Whirlpool";
		break;
	case elementalPowerCards::powerAbility::blizzard:
		os << "Blizzard";
		break;
	case elementalPowerCards::powerAbility::waterfall:
		os << "Waterfall";
		break;
	case elementalPowerCards::powerAbility::support:
		os << "Support";
		break;
	case elementalPowerCards::powerAbility::earthQuake:
		os << "Earthquake";
		break;
	case elementalPowerCards::powerAbility::crumble:
		os << "Crumble";
		break;
	case elementalPowerCards::powerAbility::border:
		os << "Border";
		break;
	case elementalPowerCards::powerAbility::avalanche:
		os << "Avalanche";
		break;
	case elementalPowerCards::powerAbility::rock:
		os << "Rock";
		break;
	default:
		os << "Unknown Ability";
		break;
	}
	return os;
}

elementalPowerCards::elementalPowerCards(powerAbility power) : 
	m_power{power},
	m_used{false}
{}

void elementalPowerCards:: setUsed(bool used)
{
	m_used = used;
}

bool elementalPowerCards::getUsed() const
{
	return m_used;
}

void elementalPowerCards::setAbility(powerAbility power)
{
	m_power = power;
}

elementalPowerCards::powerAbility elementalPowerCards::getAbility() const
{
	return powerAbility();
}
void elementalPowerCards::activate(Player& player, Player& opponent, Board& board) 
{
	if (m_used)
		throw std::runtime_error("The elemental power has already been used!\n");
	switch (m_power)
	{
	case eter::elementalPowerCards::powerAbility::controlledExplosion:
		//se va apela o functie pentru puterea respectiva
		break;
	case eter::elementalPowerCards::powerAbility::destruction:
		activateDestruction(player, opponent, board);
		break;
	case eter::elementalPowerCards::powerAbility::flame:
		activateFlame(player,opponent,board);
		break;
	case eter::elementalPowerCards::powerAbility::fire:
		activateFire(player, opponent, board);
		break;
	case eter::elementalPowerCards::powerAbility::ash:
		activateASH(player, board);
		break;
	case eter::elementalPowerCards::powerAbility::spark:
		activateSpark(player, board);
		break;
	case eter::elementalPowerCards::powerAbility::squall:
		activateSquall(opponent);
		break;
	case eter::elementalPowerCards::powerAbility::gale:
		activateGale(player, opponent, board);
		break;
	case eter::elementalPowerCards::powerAbility::hurricane:
		activateHurricane(player, opponent,board);
		break;
	case eter::elementalPowerCards::powerAbility::gust:
		activateGust(board);
		break;
	case eter::elementalPowerCards::powerAbility::mirage:
		activateMirage(board, player);
		break;
	case eter::elementalPowerCards::powerAbility::storm:
		activateStorm(board, player, opponent);
		break;
	case eter::elementalPowerCards::powerAbility::tide:
		activateTide(board);
		break;
	case eter::elementalPowerCards::powerAbility::mist:
		activateMist(player, board);
		break;
	case eter::elementalPowerCards::powerAbility::wave:
		activateWave(board, player);
		break;
	case eter::elementalPowerCards::powerAbility::whirlpool:
		activateWhirlpool(board, player);
		break;
	case eter::elementalPowerCards::powerAbility::blizzard:
		activateBlizzard( board, player,opponent);
		break;
	case eter::elementalPowerCards::powerAbility::waterfall:
		activateWaterfall(board);
		break;
	case eter::elementalPowerCards::powerAbility::support:
		activateSupport(board, player);
		break;
	case eter::elementalPowerCards::powerAbility::earthQuake:
		activateEarthQuake(player, opponent, board);
		break;
	case eter::elementalPowerCards::powerAbility::crumble:
		activateCrumble(board, player);
		break;
	case eter::elementalPowerCards::powerAbility::border:
		break;
	case eter::elementalPowerCards::powerAbility::avalanche:
		activateAvalanche(board);
		break;
	case eter::elementalPowerCards::powerAbility::rock:
		activateRock(board,player);
		break;
	default:
		throw std::invalid_argument("Unknown power!\n!");
		break;
	}
	m_used = true;
}
void elementalPowerCards::activateDestruction(Player& player, Player& opponent, Board& board)
{

	const auto& opponentPlayedCards = opponent.GetPlayedCards();

	if (opponentPlayedCards.empty())
	{
		std::cout << "The opponent has not played any cards!\n";
		return;
	}

	const Card& lastCardPlayed = opponentPlayedCards.back();
	std::cout << "Last card played by opponent: "
		<< lastCardPlayed.GetValue() + 1 - 1 << " of color "
		<< lastCardPlayed.GetColor() << "\n";

	auto& grid = board.GetGrid();
	bool cardFound = false;

	for (size_t i = 0; i < 4; ++i) {
		for (size_t j = 0; j < 4; ++j) {
			auto& stackOpt = grid[i][j];

			if (stackOpt.has_value()) {
				const std::stack<Card>& cardStack = stackOpt.value();

				if (!cardStack.empty()) {
					std::cout << "Checking stack at position (" << i << ", " << j << "): ";
					std::cout << "Top card: " << cardStack.top().GetValue() + 1 - 1
						<< " of color " << cardStack.top().GetColor() << "\n";

					if (cardStack.top() == lastCardPlayed)
					{
						std::stack<Card>& modifiableCardStack = const_cast<std::stack<Card>&>(stackOpt.value());
						modifiableCardStack.pop();
						std::cout << "The card with value " << lastCardPlayed.GetValue() + 1 - 1
							<< " and color " << lastCardPlayed.GetColor()
							<< " has been removed from the game!\n";
						cardFound = true;
						break;
					}
				}
				else {
					std::cout << "The stack at position (" << i << ", " << j << ") is empty.\n";
				}
			}
			else {
				std::cout << "No stack at position (" << i << ", " << j << ").\n";
			}
		}

		if (cardFound) {
			break;
		}
	}

	if (cardFound) {
		std::cout << "Power activated successfully!\n";
		return;
	}

	// Dacă nu am găsit cardul pe tablă, afișăm un mesaj
	std::cout << "The card was not found on the board!\n";
}



void elementalPowerCards::activateSquall(Player& opponent)
{
	auto& playedCards = opponent.GetPlayedCards();
	auto it = std::find_if(playedCards.begin(), playedCards.end(), [](const Card& card) {
		return card.GetPosition() == true;
		});
	if (it != playedCards.end()) {
		Card visibleCard = *it;
		playedCards.erase(it);
		opponent.AddCardToHand(visibleCard);
		std::cout << "The card with value " << visibleCard.GetValue()
			<< " and color " << visibleCard.GetColor()
			<< " has been returned to the opponent's hand!\n";
	}
	else {
		throw std::invalid_argument("There is no visible card that can be returned to the opponent's hand!\n");
	}
}

void elementalPowerCards::activateFire(Player& player, Player& opponent, Board& board)
{
	std::unordered_map<uint8_t, uint8_t> visibleCardCounts;

	for (size_t i = 0; i < board.GetRows(); ++i) 
	{
		for (size_t j = 0; j < board.GetCols(); ++j) 
		{
			auto& stackOpt = board.GetGrid()[i][j];
			if (stackOpt.has_value() && !stackOpt.value().empty()) 
			{
				const Card& topCard = stackOpt.value().top();
				if (topCard.GetPosition()) 
					++visibleCardCounts[topCard.GetValue()];
			}
		}
	}

	uint8_t chosenNumber;
	while (true)
	{
		std::cout << "Enter a number with at least two visible cards on the board: ";
		std::cin >> chosenNumber;

		if (visibleCardCounts[chosenNumber] >= 2) 
			break; 
		else 
			std::cout << "Invalid choice. There are less than two visible cards with this number.\n";
	}

	for (size_t i = 0; i < board.GetRows(); ++i)
	{
		for (size_t j = 0; j < board.GetCols(); ++j)
		{
			auto& stackOpt = board.GetGrid()[i][j];
			if (stackOpt.has_value() && !stackOpt.value().empty()) 
			{
				std::stack<Card> cardStack = stackOpt.value();
				Card topCard = cardStack.top();

				if (topCard.GetPosition() && topCard.GetValue() == chosenNumber)
				{
					cardStack.pop();
					if (std::find(player.GetPlayedCards().begin(), player.GetPlayedCards().end(), topCard) != player.GetPlayedCards().end()) {
						player.AddCardToHand(topCard);
					}
					else if (std::find(opponent.GetPlayedCards().begin(), opponent.GetPlayedCards().end(), topCard) != opponent.GetPlayedCards().end()) {
						opponent.AddCardToHand(topCard);
					}
					std::cout << "The card with value " << static_cast<int>(topCard.GetValue())
						<< " has been returned to its owner's hand.\n";
				}
			}
		}
	}
}

void elementalPowerCards::activateASH(Player& player, Board& board)
{
	auto& eliminatedCards = player.GetEliminatedCards();

	if (eliminatedCards.empty())
		throw std::runtime_error("No eliminated cards to choose from!");

	std::cout << "Choose a card to play from your eliminated cards:\n";
	for (size_t i = 0; i < eliminatedCards.size(); ++i) 
		std::cout << i + 1 << ". Card with value " << eliminatedCards[i].GetValue()
			<< " and color " << eliminatedCards[i].GetColor() << '\n';

	size_t choice;
	std::cin >> choice;

	Card chosenCard = eliminatedCards[choice - 1];

	bool cardPlaced = false;
	for (int row = 0; row < board.GetRows(); ++row)
	{
		for (int col = 0; col < board.GetCols(); ++col) 
		{
			if (board.canPlaceCard(row, col, chosenCard)) 
			{
				board.placeCard(row, col, chosenCard);
				std::cout << "Card with value " << chosenCard.GetValue()
					<< " and color " << chosenCard.GetColor()
					<< " has been placed back on the board at position (" << row << ", " << col << ").\n";
				cardPlaced = true;
				break;
			}
		}
		if (cardPlaced) break;
	}

	if (!cardPlaced) 
		throw std::runtime_error("No valid position found to place the card!");

	eliminatedCards.erase(eliminatedCards.begin() + (choice - 1));
}

void elementalPowerCards::activateSpark(Player& player, Board& board)
{
	bool cardFound = false; 
	for (size_t row = 0; row < board.GetRows(); ++row) 
	{
		for (size_t col = 0; col < board.GetCols(); ++col)
		{
			if (board.GetGrid()[row][col].has_value()) 
			{
				std::stack<Card> stack = board.GetGrid()[row][col].value();
				if (stack.top().GetColor()!= player.GetColor())
					continue; 
				if (stack.size() > 1) 
				{ 
					cardFound = true;
					int newRow, newCol;
					std::cout << "Choose a new position to play the card (row col):";
					std::cin >> newRow >> newCol;

					if (board.isValidPosition(newRow, newCol) && board.canPlaceCard(newRow, newCol, stack.top()))
					{
						board.placeCard(newRow, newCol, stack.top());
						stack.pop();
						break;
					}
					else 
						throw std::invalid_argument("The chosen position is not valid or the card cannot be placed there.\n");
				}
			}
		}
	}
	if (!cardFound) 
	{
		std::cout << "There are no own cards covered by the opponent on the board.\n";
	}
}

void elementalPowerCards::activateEarthQuake(Player& player, Player& opponent, Board& board)
{
	for (int row = 0; row < board.GetRows(); ++row)
	{
		for (int col = 0; col < board.GetCols(); ++col) 
		{
			auto& cell = board[{row, col}];
			if (cell.has_value() && !cell->empty())
			{
				Card& topCard = cell->top();
				if (topCard.GetValue() == 1)
				{
					Player* owner = nullptr;

					if (topCard.GetColor() == player.GetColor()) 
						owner = &player;

					else if (topCard.GetColor() == opponent.GetColor())
						owner = &opponent;

					if (owner) 
						owner->AddToEliminatedCards(topCard);

					cell->pop();
					std::cout << "Removed card with value 1 at position (" << row << ", " << col << ").\n";

					if (cell->empty()) 
						cell.reset();
				}
			}
		}
	}
}

void elementalPowerCards::activateMist(Player& player, Board& board)
{
	uint8_t row, col;
	std::cout << "Enter the coordinates of the position to use an illusion:";
	std::cin >> row >> col;
	std::vector<Card>& cardsInHand = player.GetCardsInHand();
	int selectedCardIndex = -1;

	std::cout << "Select a new illusion from your hand:\n";
	for (size_t i = 0; i < cardsInHand.size(); ++i)
		std::cout << i << ": " << cardsInHand[i] << "\n";
	std::cin >> selectedCardIndex;

	if (selectedCardIndex < 0 || selectedCardIndex >= cardsInHand.size()) {
		std::cout << "Invalid selection. Mirage cancelled.\n";
		return;
	}

	Card newIllusion = cardsInHand[selectedCardIndex];
	player.useIllusion(row, col, board, newIllusion);
	player.AddPlayedCard(newIllusion);
	player.GetCardsInHand().erase(player.GetCardsInHand().begin() + selectedCardIndex);

}

void elementalPowerCards::activateGale(Player& player, Player& opponent, Board& board)
{
	for (int row = 0; row < static_cast<int>(board.GetRows()); ++row)
	{
		for (int col = 0; col < static_cast<int>(board.GetCols()); ++col)
		{
			auto& cell = board[{row, col}];

			if (cell.has_value() && cell->size() > 1)
			{
				std::stack<Card> tempStack;

				Card topCard = cell->top();
				cell->pop();

				while (!cell->empty()) 
				{
					Card coveredCard = cell->top();
					cell->pop();

					if (coveredCard.GetColor() == player.GetColor()) 
						player.AddCardToHand(coveredCard);

					else if (coveredCard.GetColor() == opponent.GetColor()) 
						opponent.AddCardToHand(coveredCard);
				}

				cell->push(topCard);
			}
		}
	}
}
void elementalPowerCards::activateGust(Board& board)
{
	int selectedRow, selectedCol;
	bool validCardSelected = false;
	while (!validCardSelected)
	{
		std::cout << "Select a visible card (row, column): ";
		std::cin >> selectedRow >> selectedCol;
		if (selectedRow < 0 || selectedRow >= board.GetRows() || selectedCol < 0 || selectedCol >= board.GetCols())
		{
			std::cout << "Invalid position. Try again.\n";
			continue;
		}
		auto& selectedStack = board[{selectedRow, selectedCol}];
		if (selectedStack.has_value() && !selectedStack->empty())
			validCardSelected = true;
		else
			std::cout << "No visible card at this position. Try again.\n";
	}

	std::vector<std::pair<int, int>> adjacentPositions = {{selectedRow - 1, selectedCol},
		{selectedRow + 1, selectedCol}, 
		{selectedRow, selectedCol - 1},
		{selectedRow, selectedCol + 1} 
	};

	std::vector<std::pair<int, int>> validPositions;

	auto& selectedStack = board[{selectedRow, selectedCol}];
	auto selectedCardValue = selectedStack->top().GetValue(); 

	for (const auto& [adjRow, adjCol] : adjacentPositions)
	{
		if (adjRow >= 0 && adjRow < board.GetRows() && adjCol >= 0 && adjCol < board.GetCols())
		{
			auto& adjacentStack = board[{adjRow, adjCol}];
			if (adjacentStack.has_value() && !adjacentStack->empty() &&
				adjacentStack->top().GetValue() < selectedCardValue)
			{
				validPositions.push_back({ adjRow, adjCol });
			}
		}
	}

	if (validPositions.empty())
	{
		std::cout << "No valid move found for the selected card.\n";
		return;
	}
	int chosenPositionIndex;
	std::cout << "Choose a position to place the card (0 - " << validPositions.size() - 1 << "): ";
	std::cin >> chosenPositionIndex;

	if (chosenPositionIndex < 0 || chosenPositionIndex >= validPositions.size())
	{
		std::cout << "Invalid position chosen. Aborting move.\n";
		return;
	}
	auto [chosenRow, chosenCol] = validPositions[chosenPositionIndex];
	auto& destinationStack = board[{chosenRow, chosenCol}];
	destinationStack->push(selectedStack->top());
	selectedStack->pop(); 
	std::cout << "Card placed successfully on position (" << chosenRow << ", " << chosenCol << ").\n";
}

void elementalPowerCards::activateTide(Board& board)
{
	int row1, col1, row2, col2;
	std::cout << "Enter the coordinates for the first stack (row, column): ";
	std::cin >> row1 >> col1;
	if (row1 < 0 || row1 >= board.GetRows() || col1 < 0 || col1 >= board.GetCols())
	{
		std::cout << "Invalid position for the first stack. Try again.\n";
		return;
	}
	std::cout << "Enter the coordinates for the second stack (row, column): ";
	std::cin >> row2 >> col2;

	if (row2 < 0 || row2 >= board.GetRows() || col2 < 0 || col2 >= board.GetCols())
	{
		std::cout << "Invalid position for the second stack. Try again.\n";
		return;
	}

	auto& stack1 = board[{row1, col1}];
	auto& stack2 = board[{row2, col2}];

	if (!stack1.has_value() || !stack2.has_value())
	{
		std::cout << "One or both of the positions do not contain any stacks of cards.\n";
		return;
	}

	if (stack1.value().size() <= 1 || stack2.value().size() <= 1)
	{
		std::cout << "Both stacks must contain more than one card to be swapped.\n";
		return;
	}

	std::stack<Card> tempStack;
	while (!stack1.value().empty())
	{
		tempStack.push(stack1.value().top());
		stack1.value().pop();
	}

	while (!stack2.value().empty())
	{
		stack1.value().push(stack2.value().top());
		stack2.value().pop();
	}

	while (!tempStack.empty())
	{
		stack2.value().push(tempStack.top());
		tempStack.pop();
	}
}

void elementalPowerCards::activateWave(Board& board, Player& player)
{
	int row, col;
	std::cout << "Enter the coordinates of the stack to move (row, column): ";
	std::cin >> row >> col;
	if (row < 0 || row >= board.GetRows() || col < 0 || col >= board.GetCols())
	{
		std::cout << "Invalid position. Try again.\n";
		return;
	}
	auto& stack = board[{row, col}];
	if (!stack.has_value() || stack->size() <= 1)
	{
		std::cout << "Selected stack must contain more than one card.\n";
		return;
	}
	int newRow, newCol;
	bool foundEmptyAdjacent = false;
	do {
		std::cout << "Enter the coordinates for an empty adjacent position (row, column): ";
		std::cin >> newRow >> newCol;
		if (board.isValidPosition(newRow, newCol) && !board[{newRow, newCol}].has_value())
			foundEmptyAdjacent = true;
		else
			std::cout << "The chosen position is not empty or is invalid. Try again.\n";
	} while (!foundEmptyAdjacent);

	board[{newRow, newCol}] = stack;
	stack.reset();
	if (player.GetCardsInHand().empty())
	{
		std::cout << "No cards available in hand to play.\n";
		return;
	}

	std::cout << "Choose a card to play from your hand:\n";
	for (size_t i = 0; i < player.GetCardsInHand().size(); ++i) 
	{
		std::cout << i + 1 << ": " << player.GetCardsInHand()[i].GetValue() << "\n";
	}
	int cardIndex;
	std::cin >> cardIndex;
	if (cardIndex < 1 || static_cast<size_t>(cardIndex) > player.GetCardsInHand().size())
	{
		std::cout << "Invalid choice.\n";
		return;
	}
	Card chosenCard = player.GetCardsInHand()[cardIndex - 1];
	board.placeCard(newRow, newCol, chosenCard);
	player.AddPlayedCard(chosenCard);
	player.GetCardsInHand().erase(player.GetCardsInHand().begin() + cardIndex - 1);
}

void elementalPowerCards::activateStorm(Board& board, Player& player, Player& opponent)
{
	for (size_t row = 0; row < board.GetRows(); ++row)
	{
		for (size_t col = 0; col < board.GetCols(); ++col)
		{
			auto& stack = board[{static_cast<int>(row), static_cast<int>(col)}];
			if (stack.has_value() && stack.value().size() >= 2)
			{
				while (!stack.value().empty())
				{
					Card topCard = stack.value().top();
					stack.value().pop();
					if (topCard.GetColor() == player.GetColor())
					{
						player.AddToEliminatedCards(topCard);
					}
					else if (topCard.GetColor() == opponent.GetColor())
					{
						opponent.AddToEliminatedCards(topCard);
					}
				}
			}
		}
	}
}

void elementalPowerCards::activateWaterfall(Board& board)
{
	char choice;
	std::cout << "Choose 'R' for row or 'C' for column: ";
	std::cin >> choice;
	if (choice == 'R') {
		int row;
		char direction;
		std::cout << "Enter the row number with at least 3 occupied positions: ";
		std::cin >> row;
		if (row < 0 || row >= board.GetRows())
		{
			std::cout << "Invalid row. Try again.\n";
			return;
		}

		int occupiedCount = 0;
		for (size_t col = 0; col < board.GetCols(); ++col)
			if (board[{row, static_cast<int>(col)}].has_value())
				++occupiedCount;

		if (occupiedCount < 3)
		{
			std::cout << "Selected row must have at least 3 occupied positions.\n";
			return;
		}

		std::cout << "Enter the direction of the cascade (D for down, U for up): ";
		std::cin >> direction;

		if (direction != 'D' && direction != 'U') {
			std::cout << "Invalid direction. Try again.\n";
			return;
		}

		std::stack<Card> finalStack;
		if (direction == 'D')
		{
			for (size_t col = 0; col < board.GetCols(); ++col)
			{
				if (board[{row, static_cast<int>(col)}].has_value())
				{
					auto& currentStack = board[{row, static_cast<int>(col)}].value();
					while (!currentStack.empty())
					{
						finalStack.push(currentStack.top());
						currentStack.pop();
					}
					board[{row, static_cast<int>(col)}].reset();
				}
			}
			board[{row, 0}] = finalStack;
		}
		else if (direction == 'U')
		{
			for (int col = static_cast<int>(board.GetCols() - 1); col >= 0; --col)
			{
				if (board[{row, col}].has_value())
				{
					auto& currentStack = board[{row, col}].value();
					while (!currentStack.empty())
					{
						finalStack.push(currentStack.top());
						currentStack.pop();
					}
					board[{row, col}].reset();
				}
			}
			board[{row, static_cast<int>(board.GetCols() - 1)}] = finalStack;
		}
	}
	else if (choice == 'C') {
		int col;
		char direction;
		std::cout << "Enter the column number with at least 3 occupied positions: ";
		std::cin >> col;
		if (col < 0 || col >= board.GetCols()) {
			std::cout << "Invalid column. Try again.\n";
			return;
		}

		int occupiedCount = 0;
		for (size_t row = 0; row < board.GetRows(); ++row) {
			if (board[{static_cast<int>(row), col}].has_value()) {
				++occupiedCount;
			}
		}

		if (occupiedCount < 3) {
			std::cout << "Selected column must have at least 3 occupied positions.\n";
			return;
		}

		std::cout << "Enter the direction of the cascade (U for up, D for down): ";
		std::cin >> direction;

		if (direction != 'U' && direction != 'D') {
			std::cout << "Invalid direction. Try again.\n";
			return;
		}

		std::stack<Card> finalStack;
		if (direction == 'U') {
			for (size_t row = 0; row < board.GetRows(); ++row) {
				if (board[{static_cast<int>(row), col}].has_value()) {
					auto& currentStack = board[{static_cast<int>(row), col}].value();
					while (!currentStack.empty()) {
						finalStack.push(currentStack.top());
						currentStack.pop();
					}
					board[{static_cast<int>(row), col}].reset();
				}
			}
			board[{0, col}] = finalStack;
		}
		else if (direction == 'D') {
			for (int row = static_cast<int>(board.GetRows() - 1); row >= 0; --row) {
				if (board[{row, col}].has_value()) {
					auto& currentStack = board[{row, col}].value();
					while (!currentStack.empty()) {
						finalStack.push(currentStack.top());
						currentStack.pop();
					}
					board[{row, col}].reset();
				}
			}
			board[{static_cast<int>(board.GetRows() - 1), col}] = finalStack;
		}
	}
	else {
		std::cout << "Invalid choice. Choose 'R' for row or 'C' for column.\n";
	}
}

void elementalPowerCards::activateWhirlpool(Board& board, Player& player)
{
	int row1, col1, row2, col2;
	std::cout << "Enter the coordinates for the first card (row, column): ";
	std::cin >> row1 >> col1;

	std::cout << "Enter the coordinates for the second card (row, column): ";
	std::cin >> row2 >> col2;

	if ((abs(row1 - row2) == 1 && col1 == col2) || (abs(col1 - col2) == 1 && row1 == row2))
	{
		if (board[{row1, col1}].has_value() && board[{row2, col2}].has_value())
		{
			auto& stack1 = board[{row1, col1}].value();
			auto& stack2 = board[{row2, col2}].value();
			if (stack1.size() == 1 && stack2.size() == 1)
			{
				Card card1 = stack1.top();
				Card card2 = stack2.top();

				stack1.pop();
				stack2.pop();
				if (card1.GetValue() < card2.GetValue())
				{
					board[{row1, col1}].value().push(card1);
					board[{row2, col2}].value().push(card2);
				}
				else if (card1.GetValue() > card2.GetValue())
				{
					board[{row1, col1}].value().push(card2);
					board[{row2, col2}].value().push(card1);
				}
				else
				{
					char choice;
					std::cout << "The cards have equal values. Do you want card1 or card2 on top? (1/2): ";
					std::cin >> choice;
					if (choice == '1')
					{
						board[{row1, col1}].value().push(card1);
						board[{row2, col2}].value().push(card2);
					}
					else if (choice == '2')
					{
						board[{row1, col1}].value().push(card2);
						board[{row2, col2}].value().push(card1);
					}
					else
					{
						std::cout << "Invalid choice. No change made.\n";
						return;
					}
				}
			}
			else 
			{
				std::cout << "Both positions must contain exactly one card!\n";
				return;
			}
		}
		else
		{
			std::cout << "One or both positions do not contain any cards!\n";
			return;
		}
	}
	else
		std::cout << "The positions are not adjacent. Please select adjacent positions.\n";
}

void eter::elementalPowerCards::activateFlame(Player& player,Player& opponent, Board& board)
{
	bool illusionFound = false;

	for (size_t row = 0; row < board.GetRows(); ++row) 
	{
		for (size_t col = 0; col < board.GetCols(); ++col)
		{
			auto& cell = board[{static_cast<int>(row), static_cast<int>(col)}];
			if (cell.has_value())
			{
				auto& stack = cell.value();
				if (!stack.empty())
				{
					Card& topCard = stack.top();
					if (!topCard.GetPosition() && topCard.GetColor() == opponent.GetColor())
					{
						topCard.SetPosition(true);
						illusionFound = true;
						break;
					}
				}
			}
		}
		if (illusionFound) break;
	}

	if (!illusionFound) 
		std::cout << "No illusion card found for the opponent.\n";

	auto& cardsInHand = player.GetCardsInHand();

	int choice;
	std::cout << "Enter the number of the card you want to play: ";
	std::cin >> choice;

	if (choice <= 0 || choice > static_cast<int>(cardsInHand.size())) 
	{
		std::cout << "Invalid choice.\n";
		return;
	}
	Card selectedCard = cardsInHand[choice - 1];
	cardsInHand.erase(cardsInHand.begin() + (choice - 1));
	player.AddPlayedCard(selectedCard);

	int row, col;
	std::cout << "Choose a position (x,y) to place the selected card.\n";
	std::cout << "Enter row: ";
	std::cin >> row;
	std::cout << "Enter column: ";
	std::cin >> col;

	if (row < 0 || row >= static_cast<int>(board.GetRows()) || col < 0 || col >= static_cast<int>(board.GetCols())) 
	{
		std::cout << "Invalid position.\n";
		return;
	}
	auto& cell = board[{row, col}];
	if (!cell.has_value()) 
		cell.emplace(); // stack nou dacă poziția este goală

	cell->push(selectedCard);
}

void eter::elementalPowerCards::activateHurricane(Player& player, Player& opponent,Board& board)
{
	char type;
	size_t index;
	char direction;

	std::cout << "Choose 'R' for row or 'C' for column: ";
	std::cin >> type;
	std::cout << "Enter the index of the row/column: ";
	std::cin >> index;
	std::cout << "Enter direction ('L', 'R' for row; 'U', 'D' for column): ";
	std::cin >> direction;

	if (type == 'R')
	{ 
		if (index >= board.GetRows())
		{
			std::cout << "Invalid row index.\n";
			return;
		}

		size_t occupiedCount = 0;
		for (size_t col = 0; col < board.GetCols(); ++col) 
		{
			if (board[{index, col}].has_value())
				++occupiedCount;
		}
		if (occupiedCount != board.GetCols())
		{
			std::cout << "The selected row is not fully occupied.\n";
			return;
		}

		if (direction == 'L')
		{
			auto tempStack = board[{index, 0}];
			for (size_t col = 0; col < board.GetCols() - 1; ++col)
			{
				board[{index, col}] = board[{index, col + 1}];
			}
			board[{index, board.GetCols() - 1}].reset(); 

			if (tempStack.has_value())
			{
				auto& stack = tempStack.value();
				while (!stack.empty())
				{
					Card topCard = stack.top();
					stack.pop();
					if (topCard.GetColor() == player.GetColor()) 
					{
						player.AddCardToHand(topCard);
					}
					else if (topCard.GetColor() == opponent.GetColor())
					{
						opponent.AddCardToHand(topCard);
					}
				}
			}
		}
		else if (direction == 'R') 
		{
			auto tempStack = board[{index, board.GetCols() - 1}];
			for (int col = board.GetCols() - 1; col > 0; --col)
			{
				board[{index, col}] = board[{index, col - 1}];
			}
			board[{index, 0}].reset(); 

			if (tempStack.has_value()) 
			{
				auto& stack = tempStack.value();
				while (!stack.empty()) 
				{
					Card topCard = stack.top();
					stack.pop();
					if (topCard.GetColor() == player.GetColor())
					{
						player.AddCardToHand(topCard);
					}
					else if (topCard.GetColor() == opponent.GetColor())
					{
						opponent.AddCardToHand(topCard);
					}
				}
			}
		}
		else {
			std::cout << "Invalid direction.\n";
		}
	}
	else if (type == 'C') 
	{
		if (index >= board.GetCols())
		{
			std::cout << "Invalid column index.\n";
			return;
		}

		size_t occupiedCount = 0;
		for (size_t row = 0; row < board.GetRows(); ++row)
		{
			if (board[{row, index}].has_value())
				++occupiedCount;
		}
		if (occupiedCount != board.GetRows()) 
		{
			std::cout << "The selected column is not fully occupied.\n";
			return;
		}

		if (direction == 'U') 
		{ 
			auto tempStack = board[{0, index}];
			for (size_t row = 0; row < board.GetRows() - 1; ++row)
			{
				board[{row, index}] = board[{row + 1, index}];
			}
			board[{board.GetRows() - 1, index}].reset(); 

			if (tempStack.has_value()) 
			{
				auto& stack = tempStack.value();
				while (!stack.empty())
				{
					Card topCard = stack.top();
					stack.pop();
					if (topCard.GetColor() == player.GetColor()) {
						player.AddCardToHand(topCard);
					}
					else if (topCard.GetColor() == opponent.GetColor())
					{
						opponent.AddCardToHand(topCard);
					}
				}
			}
		}
		else if (direction == 'D') 
		{ 
			auto tempStack = board[{board.GetRows() - 1, index}];
			for (int row = board.GetRows() - 1; row > 0; --row)
			{
				board[{row, index}] = board[{row - 1, index}];
			}
			board[{0, index}].reset();

			if (tempStack.has_value()) 
			{
				auto& stack = tempStack.value();
				while (!stack.empty()) {
					Card topCard = stack.top();
					stack.pop();
					if (topCard.GetColor() == player.GetColor())
					{
						player.AddCardToHand(topCard);
					}
					else if (topCard.GetColor() == opponent.GetColor())
					{
						opponent.AddCardToHand(topCard);
					}
				}
			}
		}
		else {
			std::cout << "Invalid direction.\n";
		}
	}
	else {
		std::cout << "Invalid type. Choose 'R' or 'C'.\n";
	}
}

void eter::elementalPowerCards::activateMirage(Board& board, Player& player)
{
	for (size_t row = 0; row < board.GetRows(); ++row) {
		for (size_t col = 0; col < board.GetCols(); ++col) {
			auto& cell = board[{row, col}];

			if (cell.has_value() && !cell->empty()) 
			{
				Card& topCard = cell->top();
				if (topCard.GetColor() == player.GetColor() && !topCard.GetPosition()) 
				{
					cell->pop();
					player.AddCardToHand(topCard);
					
					std::vector<Card>& cardsInHand = player.GetCardsInHand();
					int selectedCardIndex = -1;

					std::cout << "Select a new illusion from your hand:\n";
					for (size_t i = 0; i < cardsInHand.size(); ++i) 
						std::cout << i << ": " << cardsInHand[i] << "\n";
					std::cin >> selectedCardIndex;

					if (selectedCardIndex < 0 || selectedCardIndex >= cardsInHand.size()) {
						std::cout << "Invalid selection. Mirage cancelled.\n";
						return;
					}

					Card newIllusion = cardsInHand[selectedCardIndex];
					player.useIllusion(row, col, board, newIllusion);
					player.AddPlayedCard(newIllusion);
					player.GetCardsInHand().erase(player.GetCardsInHand().begin() + selectedCardIndex);
					return;
				}
			}
		}
	}

	std::cout << "No illusion found on the board to replace.\n";
}

void eter::elementalPowerCards::activateBlizzard(Board& board, Player& player, Player& opponent)
{
	bool hasFreeSpace = false;
	for (size_t row = 0; row < board.GetRows(); ++row) 
	{
		for (size_t col = 0; col < board.GetCols(); ++col)
		{
			if (!board[{row, col}].has_value())
			{
				hasFreeSpace = true;
				break;
			}
		}
		if (hasFreeSpace) break;
	}

	if (!hasFreeSpace) {
		std::cout << "Opponent does not have any free space to play a card. Blizzard cannot be activated.\n";
		return;
	}

	int x, y;
	std::cout << "Enter the position (row and column) to place the Blizzard card: ";
	std::cin >> x >> y;

	if (x < 0 || x >= board.GetRows() || y < 0 || y >= board.GetCols())
	{
		std::cout << "Invalid position. Blizzard cancelled.\n";
		return;
	}

	if (board[{x, y}].has_value()) 
	{
		std::cout << "Position is already occupied. Blizzard cancelled.\n";
		return;
	}
	Card blizzardCard('X', player.GetColor(),true); 
	board[{x, y}].emplace().push(blizzardCard);
	player.AddPlayedCard(blizzardCard);

	int blockedRow = -1, blockedCol = -1;
	char choice;
	std::cout << "Do you want to block a row (R) or a column (C)? ";
	std::cin >> choice;
	if (choice == 'R' || choice == 'r') 
	{
		blockedRow = x;
		std::cout << "Row " << blockedRow << " will be blocked.\n";
	}
	else if (choice == 'C' || choice == 'c') 
	{
		blockedCol = y;
		std::cout << "Column " << blockedCol << " will be blocked.\n";
	}
	//continuare pentru a face oponentul sa nu poata plasa o carte in urmatoarea tura
}

void eter::elementalPowerCards::activateSupport(Board& board, Player& player)
{
	int row, col;
	std::cout << "Enter the row and column of the card to boost (1/2/3): ";
	std::cin >> row >> col;

	if (row < 0 || row >= board.GetRows() || col < 0 || col >= board.GetCols()) {
		std::cout << "Invalid position on the board.\n";
		return;
	}

	auto& cell = board[{row, col}];
	if (!cell.has_value() || cell->empty()) {
		std::cout << "No cards at the specified position.\n";
		return;
	}

	Card& topCard = cell->top();

	if (topCard.GetColor() == player.GetColor() && (topCard.GetValue() >= 1 && topCard.GetValue() <= 3))
	{
		int originalValue = topCard.GetValue(); 
		topCard.SetValue(topCard.GetValue() + 1); 
	}
	//continuare
}

void eter::elementalPowerCards::activateCrumble(Board& board, Player& player)
{
	int row, col;
	std::cout << "Enter the row and column of the card to boost (1/2/3): ";
	std::cin >> row >> col;

	if (row < 0 || row >= board.GetRows() || col < 0 || col >= board.GetCols()) {
		std::cout << "Invalid position on the board.\n";
		return;
	}

	auto& cell = board[{row, col}];
	if (!cell.has_value() || cell->empty()) {
		std::cout << "No cards at the specified position.\n";
		return;
	}

	Card& topCard = cell->top();

	if (topCard.GetColor() == player.GetColor() && (topCard.GetValue() >= 1 && topCard.GetValue() <= 3))
	{
		int originalValue = topCard.GetValue();
		topCard.SetValue(topCard.GetValue() -1);
	}
	//continuare
}

void eter::elementalPowerCards::activateRock(Board& board, Player& player)
{
	std::vector<std::pair<int, int>> illusionPositions;

	for (size_t row = 0; row < board.GetRows(); ++row) 
	{
		for (size_t col = 0; col < board.GetCols(); ++col)
		{
			auto& cell = board[{row, col}];
			if (cell.has_value() && !cell->empty()) 
			{
				Card& topCard = cell->top();
				if (topCard.GetPosition()==0) 
					illusionPositions.push_back({ row, col });
			}
		}
	}

	if (illusionPositions.empty())
	{
		std::cout << "No Illusion cards found on the board. ROCK action cancelled.\n";
		return;
	}

	std::cout << "Select an Illusion card to cover from the following positions:\n";
	for (size_t i = 0; i < illusionPositions.size(); ++i)
		std::cout << i << ": Row " << illusionPositions[i].first << ", Column " << illusionPositions[i].second << "\n";

	uint8_t selectedPositionIndex;
	std::cin >> selectedPositionIndex;

	uint8_t selectedRow = illusionPositions[selectedPositionIndex].first;
	uint8_t selectedCol = illusionPositions[selectedPositionIndex].second;

	std::vector<Card>& cardsInHand = player.GetCardsInHand();
	uint8_t selectedCardIndex ;

	std::cout << "Select a card from your hand to cover the Illusion card:\n";
	for (size_t i = 0; i < cardsInHand.size(); ++i) 
		std::cout << i << ": " << cardsInHand[i] << "\n";

	std::cin >> selectedCardIndex;

	Card coverCard = cardsInHand[selectedCardIndex];
	player.AddPlayedCard(coverCard); 
	player.GetCardsInHand().erase(player.GetCardsInHand().begin() + selectedCardIndex);
	auto& cell = board[{selectedRow, selectedCol}];
	cell->push(coverCard); 
}
void elementalPowerCards::activateAvalanche(Board& board) //DE VERIFICAT!!
{
	int row1, col1, row2, col2;
	std::cout << "Enter the coordinates of the first stack (row col): ";
	std::cin >> row1 >> col1;
	std::cout << "Enter the coordinates of the second stack (row col): ";
	std::cin >> row2 >> col2;

	if ((row1 == row2 && abs(col1 - col2) == 1) || (col1 == col2 && abs(row1 - row2) == 1))
	{

		std::vector<std::pair<int, int>> emptyPositions;

		if (row1 == row2)
		{ 
			if (col1 > 0 && !board[{row1, col1 - 1}].has_value()) 
				emptyPositions.push_back({ row1, col1 - 1 });
			if (col1 + 1 < board.GetCols() && !board[{row1, col1 + 1}].has_value()) 
				emptyPositions.push_back({ row1, col1 + 1 });
			if (col2 > 0 && !board[{row2, col2 - 1}].has_value()) 
				emptyPositions.push_back({ row2, col2 - 1 });
			if (col2 + 1 < board.GetCols() && !board[{row2, col2 + 1}].has_value()) 
				emptyPositions.push_back({ row2, col2 + 1 });
		}
		else if (col1 == col2) 
		{ 
			if (row1 > 0 && !board[{row1 - 1, col1}].has_value())
				emptyPositions.push_back({ row1 - 1, col1 });
			if (row1 + 1 < board.GetRows() && !board[{row1 + 1, col1}].has_value()) 
				emptyPositions.push_back({ row1 + 1, col1 });
			if (row2 > 0 && !board[{row2 - 1, col1}].has_value()) 
				emptyPositions.push_back({ row2 - 1, col1 });
			if (row2 + 1 < board.GetRows() && !board[{row2 + 1, col1}].has_value()) 
				emptyPositions.push_back({ row2 + 1, col1 });
		}
		if (!emptyPositions.empty()) 
		{
			int selectedPosition;
			std::cout << "Select the position to shift both stacks to:\n";
			for (size_t i = 0; i < emptyPositions.size(); ++i)
			{
				std::cout << i << ": (" << emptyPositions[i].first << ", " << emptyPositions[i].second << ")\n";
			}
			std::cin >> selectedPosition;

			if (selectedPosition < 0 || selectedPosition >= emptyPositions.size())
			{
				std::cout << "Invalid selection. Avalanche cancelled.\n";
				return;
			}

			auto newPos = emptyPositions[selectedPosition];

			board[{newPos.first, newPos.second}] = board[{row1, col1}];
			board[{row1, col1}].reset();
			board[{newPos.first, newPos.second + 1}] = board[{row2, col2}];
			board[{row2, col2}].reset();
		}
		else 
			std::cout << "No valid empty positions to move the stacks. Avalanche cancelled.\n";
	}
	else 
		std::cout << "The stacks are not adjacent. Avalanche cancelled.\n";
}

 
 

};








