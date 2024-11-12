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
		break;
	case eter::ElementalPowerCards::PowerAbility::Hurricane:
		break;
	case eter::ElementalPowerCards::PowerAbility::Gust:
		break;
	case eter::ElementalPowerCards::PowerAbility::Mirage:
		break;
	case eter::ElementalPowerCards::PowerAbility::Storm:
		break;
	case eter::ElementalPowerCards::PowerAbility::Tide:
		break;
	case eter::ElementalPowerCards::PowerAbility::Mist:
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
	for (size_t row = 0; row < board.GetRows(); ++row)
	{
		for (size_t col = 0; col < board.GetCols(); ++col) 
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
				if (stack.top().GetOwnerName() != player.GetName())
					continue; 
				if (stack.size() > 1) 
				{ 
					cardFound = true;
					int newRow, newCol;
					std::cout << "Alege o pozitie noua pentru a juca cartea (X Y): ";
					std::cin >> newRow >> newCol;

					if (board.isValidPosition(newRow, newCol) && board.canPlaceCard(newRow, newCol, stack.top()))
					{
						board.placeCard(newRow, newCol, stack.top());
						stack.pop();
						break;
					}
					else 
						std::cout << "Pozitia aleasa nu este valida sau nu se poate plasa cartea acolo.\n";
				}
			}
		}
	}

	// Dacã nu am gãsit nici o carte acoperitã, afi?ãm un mesaj
	if (!cardFound) {
		std::cout << "Nu exista carti proprii acoperite de adversar pe tabla.\n";
	}
}

