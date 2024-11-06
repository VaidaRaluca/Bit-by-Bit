module player;
using namespace eter;
Player::Player(const std::string& name, uint32_t score, const std::string& color, const std::vector<Card>& cards, bool hasUsedIllusion)
	: m_name{ name }
	, m_score{ score }
	, m_color{ color }
	, m_cardsInHand{ cards }
	, m_hasUsedIllusion{ hasUsedIllusion }
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

bool Player::GetHasUsedIllusion() const
{
	return m_hasUsedIllusion;
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

std::pair<uint8_t, uint8_t> Player::findEmptyCell(Board& board)
{
	for (uint8_t rows = 0; rows < board.GetRows(); rows++)
		for (uint8_t cols = 0; cols < board.GetCols(); cols++)
			if (board.isValidPosition(rows, cols) && board.GetGrid()[rows][cols] == std::nullopt)
				return { rows,cols };
}

void Player::useIllusion(Board& board)
{
	if (GetHasUsedIllusion()==false)
		m_hasUsedIllusion = true;
	std::pair<uint8_t, uint8_t> position = findEmptyCell(board);

}

