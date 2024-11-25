module player;
using namespace eter;
constexpr std::pair<uint8_t, uint8_t> kInvalidPosition = { 255, 255 };
Player::Player(const std::string& name, const std::string& color)
	: m_name{ name }
	, m_score{ 0 }
	, m_color{ color }
	//, m_hasUsedIllusion{ false }
{}

Player::Player(const Player& other)
	: m_name(other.m_name), m_score(other.m_score), m_color(other.m_color),
	m_cardsInHand(other.m_cardsInHand), m_hasUsedIllusion(other.m_hasUsedIllusion),
	m_playedCards(other.m_playedCards), m_eliminatedCards(other.m_eliminatedCards) 
{
}

Player& eter::Player::operator=(const Player& rhs)
{
	if (this == &rhs) return *this;
	m_name = rhs.m_name;
	m_score = rhs.m_score;
	m_color = rhs.m_color;
	m_cardsInHand = rhs.m_cardsInHand;
	m_hasUsedIllusion = rhs.m_hasUsedIllusion;
	m_playedCards = rhs.m_playedCards;
	m_eliminatedCards = rhs.m_eliminatedCards;
	return *this;
}

Player::Player(Player&& other) noexcept
	: m_name(std::move(other.m_name)), m_score(other.m_score), m_color(std::move(other.m_color)),
	m_cardsInHand(std::move(other.m_cardsInHand)), m_hasUsedIllusion(other.m_hasUsedIllusion),
	m_playedCards(std::move(other.m_playedCards)), m_eliminatedCards(std::move(other.m_eliminatedCards)) {
}

Player& eter::Player::operator=(Player&& rhs) noexcept
{
	if (this == &rhs) return *this;
	m_name = std::move(rhs.m_name);
	m_score = rhs.m_score;
	m_color = std::move(rhs.m_color);
	m_cardsInHand = std::move(rhs.m_cardsInHand);
	m_hasUsedIllusion = rhs.m_hasUsedIllusion;
	m_playedCards = std::move(rhs.m_playedCards);
	m_eliminatedCards = std::move(rhs.m_eliminatedCards);
	return *this;
}

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

std::vector<Card>& Player::GetCardsInHand() 
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

std::vector<Card>& Player::GetEliminatedCards() 
{
	return m_eliminatedCards;
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

void Player::PrintCardsInHand()
{
	for (const auto& it : m_cardsInHand)
	{
		std::cout << it << "\n";
	}
}

void Player::AddToEliminatedCards(const Card& card)
{
	m_eliminatedCards.push_back(card);
}

void Player::AddPlayedCard(const Card& card)
{
	m_playedCards.push_back(card);
}

void eter::Player::AddCardToHand(const Card& card)
{
	m_cardsInHand.push_back(card);
}


bool Player::placeCard(int x, int y, const Card& card, Board& board)
{

	auto it = std::find(m_cardsInHand.begin(), m_cardsInHand.end(), card);

	if (it == m_cardsInHand.end()) {
		std::cout << "The card is not in your hand.\n";
		return false;
	}
	if (board.placeCard(x, y, card))
	{
		m_cardsInHand.erase(it);
		m_playedCards.push_back(card);
		return true;
	}
	else
	{
		return false;
	}
}

void eter::Player::swap(Player& other) noexcept
{
	using std::swap;
	swap(m_name, other.m_name);
	swap(m_score, other.m_score);
	swap(m_color, other.m_color);
	swap(m_cardsInHand, other.m_cardsInHand);
	swap(m_hasUsedIllusion, other.m_hasUsedIllusion);
	swap(m_playedCards, other.m_playedCards);
	swap(m_eliminatedCards, other.m_eliminatedCards);
}

std::pair<uint8_t, uint8_t> Player::findEmptyCell(Board& board) // this function could be moved somewhere else perhaps
{
	for (uint8_t rows = 0; rows < board.GetRows(); rows++)
		for (uint8_t cols = 0; cols < board.GetCols(); cols++)
			if (board.isValidPosition(rows, cols) && board.GetGrid()[rows][cols] == std::nullopt)
				return { rows,cols };
}

void Player::useIllusion(int x, int y, Board& board, Card& illusion)
{
	bool ok = board.isEmptyCell(x, y);
	if (!ok) 
	{
		std::cout << "No empty cell has been found on the board\n";
		return;
	}
	illusion.SetPosition(false);
	placeCard(x, y, illusion, board);
	m_hasUsedIllusion = true;
}

void eter::swap(Player& first, Player& second) noexcept
{
	first.swap(second);
}