module player;
using namespace eter;
constexpr std::pair<uint8_t, uint8_t> kInvalidPosition = { 255, 255 };
Player::Player(const std::string& name, const std::string& color)
	: m_name{ name }
	, m_score{0}
	, m_color{ color }
	, m_hasUsedIllusion{false}
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

bool Player::GetHasUsedIllusion() const //returns false if the illusion has not yet been used
{
	return m_hasUsedIllusion;
}

 std::vector<Card>& eter::Player::GetPlayedCards() 
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
		{
			auto& stack = board[{rows, cols}];
			if (board.isValidPosition(rows, cols) && !stack)
				return { rows,cols };
		}
	return kInvalidPosition;
}

void eter::Player::AddCardToHand(const Card& card)
{
	m_cardsInHand.push_back(card);
}

bool eter::Player::placeCard(int x, int y, const Card& card, Board& board)
{

	auto it = std::find(m_cardsInHand.begin(), m_cardsInHand.end(), card);//chair are ce vrea sa puna in mana??
	if (it == m_cardsInHand.end()) {
		std::cout << "Cartea nu este in mana jucatorului.\n";
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

void Player::useIllusion(Board& board, Card& illusion)
{
	if (GetHasUsedIllusion()) {
		std::cout << "Illusion has already been used\n";
		m_hasUsedIllusion = true;
		return;
	}
	std::pair<uint8_t, uint8_t> position = findEmptyCell(board);
	if (position == kInvalidPosition) {
		std::cout << "No empty cell has been found on the board\n";
		return;
	}
	auto& [line, column] = position;
	illusion.SetPosition(false);
	placeCard(line, column, illusion, board);
}

