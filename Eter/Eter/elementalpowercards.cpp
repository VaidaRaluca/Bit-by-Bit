module elementalpowercards;
import board;
import player;
import card;
import <stdexcept>;
import <unordered_map>;
import <iostream>;

using namespace eter;

ElementalPowerCards::ElementalPowerCards(PowerAbility power) : 
	m_power{power},
	m_used{false}
{}

void ElementalPowerCards:: setUsed(bool used)
{
	m_used = used;
}

bool ElementalPowerCards::getUsed() const
{
	return m_used;
}

void ElementalPowerCards::setAbility(PowerAbility power)
{
	m_power = power;
}

ElementalPowerCards::PowerAbility ElementalPowerCards::getAbility() const
{
	return PowerAbility();
}
void ElementalPowerCards::activate(Player& player, Player& opponent, Board& board) 
{
	if (m_used)
		throw std::runtime_error("The elemental power has already been used!\n");
	switch (m_power)
	{
	case eter::ElementalPowerCards::PowerAbility::ControlledExplosion:
		//se va apela o functie pentru puterea respectiva
		break;
	case eter::ElementalPowerCards::PowerAbility::Destruction:
		activateDestruction(player, opponent, board);
		break;
	case eter::ElementalPowerCards::PowerAbility::Flame:
		activateFlame(player,opponent,board);
		break;
	case eter::ElementalPowerCards::PowerAbility::Fire:
		activateFire(player, opponent, board);
		break;
	case eter::ElementalPowerCards::PowerAbility::ASH:
		activateASH(player, board);
		break;
	case eter::ElementalPowerCards::PowerAbility::Spark:
		activateSpark(player, board);
		break;
	case eter::ElementalPowerCards::PowerAbility::Squall:
		activateSquall(opponent);
		break;
	case eter::ElementalPowerCards::PowerAbility::Gale:
		activateGale(player, opponent, board);
		break;
	case eter::ElementalPowerCards::PowerAbility::Hurricane:
		activateHurricane(player, opponent,board);
		break;
	case eter::ElementalPowerCards::PowerAbility::Gust:
		activateGust(board);
		break;
	case eter::ElementalPowerCards::PowerAbility::Mirage:
		activateMirage(board, player);
		break;
	case eter::ElementalPowerCards::PowerAbility::Storm:
		activateStorm(board, player, opponent);
		break;
	case eter::ElementalPowerCards::PowerAbility::Tide:
		activateTide(board);
		break;
	case eter::ElementalPowerCards::PowerAbility::Mist:
		activateMist(player, board);
		break;
	case eter::ElementalPowerCards::PowerAbility::Wave:
		activateWave(board, player);
		break;
	case eter::ElementalPowerCards::PowerAbility::Whirlpool:
		activateWhirlpool(board, player);
		break;
	case eter::ElementalPowerCards::PowerAbility::Blizzard:
		break;
	case eter::ElementalPowerCards::PowerAbility::Waterfall:
		activateWaterfall(board);
		break;
	case eter::ElementalPowerCards::PowerAbility::Support:
		break;
	case eter::ElementalPowerCards::PowerAbility::EarthQuake:
		activateEarthQuake(player, opponent, board);
		break;
	case eter::ElementalPowerCards::PowerAbility::Crumble:
		break;
	case eter::ElementalPowerCards::PowerAbility::Border:
		break;
	case eter::ElementalPowerCards::PowerAbility::Avalanche:
		break;
	case eter::ElementalPowerCards::PowerAbility::Rock:
		break;
	default:
		throw std::invalid_argument("Unknown power!\n!");
		break;
	}
	m_used = true;
}

void ElementalPowerCards::activateDestruction(Player& player, Player& opponent, Board& board)
{
	const auto& opponentPlayedCards = opponent.GetPlayedCards();
	if (opponentPlayedCards.empty()) {
		throw std::invalid_argument("The opponent has not played any cards!\n");
	}
	Card lastCardPlayed = opponentPlayedCards.back();
	auto& grid = board.GetGrid();
	for (size_t i = 0; i < board.GetRows(); ++i)
	{
		for (size_t j = 0; j < board.GetCols(); ++j)
		{
			auto& stackOpt = grid[i][j]; 
			if (stackOpt.has_value())
			{
				std::stack<Card> cardStack = stackOpt.value();
				if (!cardStack.empty() && cardStack.top() == lastCardPlayed)
				{
					cardStack.pop();
					std::cout << "The card with value " << lastCardPlayed.GetValue()
						<< " and color " << lastCardPlayed.GetColor()
						<< " has been removed from the game!\n";
					return; 
				}
			}
		}
	}
	throw std::invalid_argument("The card was not found on the board!");
}

void ElementalPowerCards::activateSquall(Player& opponent)
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

void ElementalPowerCards::activateFire(Player& player, Player& opponent, Board& board)
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

void ElementalPowerCards::activateASH(Player& player, Board& board)
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

void ElementalPowerCards::activateSpark(Player& player, Board& board)
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

void ElementalPowerCards::activateEarthQuake(Player& player, Player& opponent, Board& board)
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

void ElementalPowerCards::activateMist(Player& player, Board& board)
{
	Card illusion;
	// player.useIllusion(board, illusion);
}

void ElementalPowerCards::activateGale(Player& player, Player& opponent, Board& board)
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
void ElementalPowerCards::activateGust(Board& board)
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

void ElementalPowerCards::activateTide(Board& board)
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

void ElementalPowerCards::activateWave(Board& board, Player& player)
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

void ElementalPowerCards::activateStorm(Board& board, Player& player, Player& opponent)
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

void ElementalPowerCards::activateWaterfall(Board& board)
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

void ElementalPowerCards::activateWhirlpool(Board& board, Player& player)
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

void eter::ElementalPowerCards::activateFlame(Player& player,Player& opponent, Board& board)
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

void eter::ElementalPowerCards::activateHurricane(Player& player, Player& opponent,Board& board)
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

void eter::ElementalPowerCards::activateMirage(Board& board, Player& player)
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
					player.useIllusion(static_cast<int>(row), static_cast<int>(col), board, newIllusion);
					return;
				}
			}
		}
	}

	std::cout << "No illusion found on the board to replace.\n";
}




