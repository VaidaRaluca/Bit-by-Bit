module elementalpowercards;
import board;
import player;
import card;
import <stdexcept>;

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
		throw std::runtime_error("Puterea elementului a fost deja folosita!");
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
		break;
	case eter::ElementalPowerCards::PowerAbility::ASH:
		break;
	case eter::ElementalPowerCards::PowerAbility::Spark:
		break;
	case eter::ElementalPowerCards::PowerAbility::Squall:
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
		throw std::invalid_argument("Putere necunoscuta!");
		break;
	}
	m_used = true;
}

void ElementalPowerCards::activateDestruction(Player& player, Player& opponent, Board& board)
{
	const auto& opponentPlayedCards = opponent.GetPlayedCards();
	if (opponentPlayedCards.empty()) {
		throw std::invalid_argument("Adversarul nu are cãr?i jucate!\n");
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
					std::cout << "Cartea cu valoarea " << lastCardPlayed.GetValue()
						<< " ?i culoarea " << lastCardPlayed.GetColor()
						<< " a fost eliminatã din joc!" << std::endl;
					return; 
				}
			}
		}
	}
	throw std::invalid_argument("Cartea nu a fost gãsitã pe tablã!");
}
