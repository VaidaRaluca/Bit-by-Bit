module elementalpowercards;
import board;
import player;
import card;
import <stdexcept>;
import <unordered_map>;

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
		break;
	case eter::ElementalPowerCards::PowerAbility::Gust:
		activateGust(board);
		break;
	case eter::ElementalPowerCards::PowerAbility::Mirage:
		break;
	case eter::ElementalPowerCards::PowerAbility::Storm:
		break;
	case eter::ElementalPowerCards::PowerAbility::Tide:
		activateTide(board);
		break;
	case eter::ElementalPowerCards::PowerAbility::Mist:
		activateMist(player, board);
		break;
	case eter::ElementalPowerCards::PowerAbility::Wave:
		break;
	case eter::ElementalPowerCards::PowerAbility::Whirlpool:
		break;
	case eter::ElementalPowerCards::PowerAbility::Blizzard:
		break;
	case eter::ElementalPowerCards::PowerAbility::Waterfall:
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
	for (size_t row = 0; row < board.GetRows(); ++row)
	{
		for (size_t col = 0; col < board.GetCols(); ++col) 
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
	player.useIllusion(board, illusion);
}

void ElementalPowerCards::activateGale(Player& player, Player& opponent, Board& board)
{
	for (size_t row = 0; row < board.GetRows(); ++row)
	{
		for (size_t col = 0; col < board.GetCols(); ++col)
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




