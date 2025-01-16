#include "Player.h"
using namespace eter;
constexpr std::pair<uint8_t, uint8_t> kInvalidPosition = { 255, 255 };
Player::Player(const std::string& name, const std::string& color)
	: m_name{ name }
	, m_score{ 0 }
	, m_color{ color }
	, m_hasUsedIllusion{ false }
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

const std::vector<Card>& Player::GetPlayedCards() const {
	return m_playedCards;
}

const std::vector<Card>& Player::GetEliminatedCards() const {
	return m_eliminatedCards;
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

void Player::printCardsInHand()
{
	int index = 0;
	for (const auto& it : m_cardsInHand)
	{
		std::cout <<"at "<< index << " is card " << it << "\n";
		index++;
	}
}

void Player::addToEliminatedCards(const Card& card)
{
	m_eliminatedCards.push_back(card);
}

void Player::addPlayedCard(const Card& card)
{
	m_playedCards.push_back(card);
}

void eter::Player::addCardToHand(const Card& card)
{
	m_cardsInHand.push_back(card);
}


bool Player::placeCard(size_t x, size_t y, const Card& card, Board& board)
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
		addPlayedCardForPower(card, x, y);
		return true;
	}
	else
	{
		return false;
	}
}

void eter::Player::addPlayedCardForPower(const Card& card, size_t x, size_t y)//functia cu vectorul pentru puteri care obtine si pozitia ultimei carti
{
	m_playedCardsP.emplace_back(card, std::make_pair(x, y));
}

std::vector<std::pair<Card, std::pair<size_t, size_t>>>& eter::Player::GetPlayedCardsForPower()
{
	return m_playedCardsP;
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
	for (uint8_t rows = 0; rows < board.GetIndexMax(); rows++)
		for (uint8_t cols = 0; cols < board.GetIndexMax(); cols++)
			if (board.isValidPosition(rows, cols) && board.GetGrid()[rows][cols] == std::nullopt)
				return { rows,cols };
}

void Player::useIllusion(size_t x, size_t y, Board& board, Card& illusion)
{
	if (!board.isValidPosition(x, y)) {
		std::cout << "The position (" << x << ", " << y << ") is not valid on the board.\n";
		return;
	}
	if (!board.isEmptyCell(x, y)) {
		std::cout << "Illusions can only be placed on empty cells. Position (" << x << ", " << y << ") is occupied.\n";
		return;
	}
	illusion.SetPosition(false);
	if (placeCard(x, y, illusion, board)) {
		m_hasUsedIllusion = true;
		std::cout << GetName() << " has placed an illusion at (" << x << ", " << y << ").\n";
	}
	else 
		std::cout << "Failed to place the illusion at (" << x << ", " << y << ").\n";
}

void eter::swap(Player& first, Player& second) noexcept
{
	first.swap(second);
}

const std::vector<Card>& Player::GetCardsInHand() const {
	return m_cardsInHand;
}

void Player::removePlayedCard(const Card& card)
{
	auto it = std::find(m_playedCards.begin(),m_playedCards.end(), card);
	if (it != m_playedCards.end())
	{
		m_playedCards.erase(it);
		std::cout << "Card removed from playedCards.\n";
	}
}

void Player::removePlayedCardForPower(const Card& card, size_t row, size_t col)
{
	auto it = std::find_if(m_playedCardsP.begin(), m_playedCardsP.end(),
		[&card, row, col](const auto& playedCardInfo) {
			const Card& storedCard = playedCardInfo.first;
			size_t storedRow = playedCardInfo.second.first;
			size_t storedCol = playedCardInfo.second.second;
			return storedCard == card && storedRow == row && storedCol == col;
		});

	if (it != m_playedCardsP.end())
	{
		m_playedCardsP.erase(it);
	}
}



//std::string eter::Player::validateName()
//{
//	std::string name;
//	const std::regex nameRegex("^[A-Z]+[a-z]*$");
//	std::cout << "Player introduce your name (only letters): ";
//	std::cin >> name;
//	if (std::regex_match(name, nameRegex) == false)
//	{
//		while (std::regex_match(name, nameRegex) == false)
//		{
//			std::cout << "Player introduce a valid name: ";
//			std::cin >> name;
//		}
//	}
//	std::cout << "Name processed successfully!\n";
//	return name;
//}


std::string eter::Player::validateName() {
	const std::regex nameRegex("^[A-Z]+[a-z]*$");
	return validateInput<std::string>(
		"Player introduce your name (only letters): ",
		nameRegex,
		"Invalid name! Please introduce a valid name: "
	);
}
