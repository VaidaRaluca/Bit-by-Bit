#ifndef PLAYER_H
#define PLAYER_H

#include"card.h"
#include"board.h"
#include<vector>
#include<utility>
#include<QString>
#include<QDebug>

namespace eter {
class Player
{
private:
    QString m_name;
    uint32_t m_score;
    std::string m_color;
    bool m_hasUsedIllusion ;
    std::vector<Card> m_cardsInHand;
    std::vector<Card> m_eliminatedCards;
    std::vector<std::pair<Card, std::pair<size_t, size_t>>> m_playedCards;
public:
    //Rule of 5
    Player() = default;
    Player(const QString& name, const std::string& color);
    ~Player() = default;
    Player(const Player& other);
    Player& operator=(const Player& rhs);
    Player(Player&& other) noexcept;
    Player& operator=(Player&& rhs) noexcept;

    //Getteri
    const QString& GetName() const;
    const uint32_t& GetScore() const;
    const std::string& GetColor() const;
    std::vector<Card>& GetCardsInHand();
    const std::vector<Card>& GetCardsInHand() const;  //De ce avem nevoie de 2 getteri?
    const bool& GetHasUsedIllusion() const;
    std::vector<Card>& GetEliminatedCards();
    std::vector<std::pair<Card, std::pair<size_t, size_t>>>& GetPlayedCards();

    //Setteri
    void SetName(const QString& name);
    void SetScore(const uint32_t& score);
    void SetColor(const std::string& color);
    void SetCardsInHand(const std::vector<Card>& cards);

    void AddToEliminatedCards(const Card& card);
    void AddToCardsInHand(const Card& card);
    void AddToPlayedCards(const Card& card, size_t x, size_t y);
    void RemoveFromPlayedCards(const Card& card, size_t row, size_t col);


    void UseIllusion(size_t x, size_t y, Board& board, Card& illusion);
    bool PlaceCard(size_t x, size_t y, const Card& card, Board& board);
    void PrintCardsInHand();

    void swap(Player& other) noexcept;
    friend void swap(Player& first, Player& second) noexcept;

};


}
#endif // PLAYER_H
