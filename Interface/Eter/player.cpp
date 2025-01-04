#include "player.h"

using namespace eter;

Player::Player(const QString& name, const std::string& color)
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

const QString& Player::GetName() const
{
    return m_name;
}

const uint32_t& Player::GetScore() const
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

const bool& Player::GetHasUsedIllusion() const //returns false if the illusion has not yet been used
{
    return m_hasUsedIllusion;
}

const std::vector<Card>& Player::GetCardsInHand() const {
    return m_cardsInHand;
}


std::vector<Card>& Player::GetEliminatedCards()
{
    return m_eliminatedCards;
}

void Player::SetName(const QString& name)
{
    m_name = name;
}

void Player::SetScore(const uint32_t& score)
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

void Player::AddToEliminatedCards(const Card& card)
{
    m_eliminatedCards.push_back(card);
}

void eter::Player::AddToCardsInHand(const Card& card)
{
    m_cardsInHand.push_back(card);
}


void eter::Player::AddToPlayedCards(const Card& card, size_t x, size_t y)
{
    m_playedCards.emplace_back(card, std::make_pair(x, y));
}


void Player::RemoveFromPlayedCards(const Card& card, size_t row, size_t col)
{
    auto it = std::find_if(m_playedCards.begin(), m_playedCards.end(),
                           [&card, row, col](const auto& playedCardInfo) {
                               const Card& storedCard = playedCardInfo.first;
                               size_t storedRow = playedCardInfo.second.first;
                               size_t storedCol = playedCardInfo.second.second;
                               return storedCard == card && storedRow == row && storedCol == col;
                           });

    if (it != m_playedCards.end())
    {
        m_playedCards.erase(it);
    }
}


bool Player::PlaceCard(size_t x, size_t y, const Card& card, Board& board)
{

    auto it = std::find(m_cardsInHand.begin(), m_cardsInHand.end(), card);

    if (it == m_cardsInHand.end()) {
        qDebug() << "The card is not in your hand.\n";
        return false;
    }
    if (board.PlaceCard(x, y, card))
    {
        m_cardsInHand.erase(it);
        m_playedCards.push_back({card,{x,y}});
        return true;
    }
    else
    {
        return false;
    }
}

void Player::UseIllusion(size_t x, size_t y, Board& board, Card& illusion)
{
    if (!board.IsValidPosition(x, y)) {
        qDebug() << "The position (" << x << ", " << y << ") is not valid on the board.\n";
        return;
    }
    if (!board.IsEmptyCell(x, y)) {
        qDebug() << "Illusions can only be placed on empty cells. Position (" << x << ", " << y << ") is occupied.\n";
        return;
    }
    illusion.SetPosition(false);
    if (PlaceCard(x, y, illusion, board)) {
        m_hasUsedIllusion = true;
        qDebug() << GetName() << " has placed an illusion at (" << x << ", " << y << ").\n";
    }
    else
        qDebug() << "Failed to place the illusion at (" << x << ", " << y << ").\n";
}

void Player::PrintCardsInHand()
{
    int index = 0;
    for (const auto& it : m_cardsInHand)
    {
        //qDebug() <<"at "<< index << " is card " << it << "\n";
        index++;
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

void eter::swap(Player& first, Player& second) noexcept
{
    first.swap(second);
}


