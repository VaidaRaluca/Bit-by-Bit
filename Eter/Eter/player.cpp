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

const std::vector<Card>& eter::Player::GetPlayedCards() const
{
	return m_playedCards;
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

void Player::AddPlayedCard(const Card& card)
{
	m_playedCards.push_back(card);
}

std::pair<uint8_t, uint8_t> Player::findEmptyCell(Board& board)
{
	for (uint8_t rows = 0; rows < board.GetRows(); rows++)
		for (uint8_t cols = 0; cols < board.GetCols(); cols++)
			if (board.isValidPosition(rows, cols) && board.GetGrid()[rows][cols] == std::nullopt)
				return { rows,cols };
}

bool eter::Player::placeCard(int x, int y, const Card& card, Board& board)
{
	
	auto it = std::find(m_cardsInHand.begin(), m_cardsInHand.end(), card);//chair are ce vrea sa puna in mana??
	if (it == m_cardsInHand.end()) {
		std::cout << "Cartea nu este în mana jucatorului.\n";
		return false; // nu are 
	}

	if (!board.canPlaceCard(x, y, card)) {
		std::cout << "Nu poti plasa aceasta carte la pozitia (" << x << ", " << y << ").\n";
		return false; 
	}

	board.placeCard(x, y, card);

	m_cardsInHand.erase(it);

	m_playedCards.push_back(card);

	std::cout << "Cartea cu valoarea " << card.m_value << " a fost plasata de " << m_name << " la (" << x << ", " << y << ").\n";
	return true;
}

void Player::useIllusion(Board& board)
{
	if (GetHasUsedIllusion()==false)
		m_hasUsedIllusion = true;
	std::pair<uint8_t, uint8_t> position = findEmptyCell(board);

}

