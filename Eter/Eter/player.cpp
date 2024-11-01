module player;
using namespace eter;
Player::Player(const std::string& name, uint32_t score, const std::string& color, const std::vector<Card>& cards)
	: m_name{ name }
	, m_score{ score }
	, m_color{ color }
	, m_cardsInHand{ cards }
{}

const std::string& Player::GetName() const
{
	return m_name;
}

uint32_t Player::GetScore() const
{
	return m_score;
}

const std::string& Player::GetColor() const
{
	return m_color;
}

const std::vector<Card>& Player::GetCardsInHand() const
{
	return m_cardsInHand;
}

void Player::SetName(const std::string& name)
{
	m_name = name;
}

void Player::SetScore(uint32_t score)
{
	m_score = score;
}

void Player::SetColor(const std::string& color)
{
	m_color = color;
}

void Player::SetCardsInHand(const std::vector<Card>& cards)
{
	m_cardsInHand = cards;
}
