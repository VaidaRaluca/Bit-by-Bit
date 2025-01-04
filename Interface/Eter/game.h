#ifndef GAME_H
#define GAME_H
#include"player.h"
#include"board.h"
#include"explosion.h"
#include<QDebug>

namespace eter {

class Game
{private:
    Player m_player1;
    Player m_player2;
    Board m_board;
    std::string m_gameMode;
    bool m_isPlayerTurn;  // true pentru p1,false pentru p2
    bool m_isUsedExplosion;
    uint8_t m_player1Wins;
    uint8_t m_player2Wins;
    uint8_t m_nrRound;   // numarul rundei in care ne aflam

    std::vector<Card> m_returnedCards; //vectorul de carti returnate
    uint8_t m_countTurnForReturnedCards=0;

    //Functii ajutatoare
    void handlePlayerTurn(Player& player);
    void handlePlayerTurnWithIllusion(Player& player);
    void handleActivateExplosion();
    void getInputCoordinates(size_t& x, size_t& y, size_t& cardIndex);
    void distributeReturnedCards();
public:
    Game() = default;
    Game(Player player1, Player player2, std::string gameMode);

    Player GetPlayer1() const;
    Player GetPlayer2() const;
    Board GetBoard()  ;

    //Getter ce returneaza &
    Player& GetPlayer1Ref();
    Player& GetPlayer2Ref();
    Board& GetBoardRef();

    std::string GetGameMods();
    bool GetIsPlayerTurn();
    bool GetIsUsedExplosion();
    uint8_t GetPlayer1Wins();
    uint8_t GetPlayer2Wins();
    uint8_t GetNrRound();
    const std::vector<Card>& GetReturnedCards() const;
    uint8_t GetCountTurnForReturnedCards();


    void SetBoard(Board board);
    void SetGameMods(std::string gameMode);
    void SetIsPlayerTurn();
    void SetIsUsedExplosion(bool ok);
    void IncrementPlayer1Wins();
    void IncrementPlayer2Wins();
    void IncrementNrRound();
    void SetReturnedCards(const std::vector<Card>& cards);
    void SetCountTurnForReturnedCards(uint8_t count);


    void playTurn();
    void playIllusion();

    char VerifyGameOver();
    void resetBoard();
    void handleCardCover(Player& currentPlayer, Player& opponent, size_t x, size_t y, size_t cardIndex);
};

}
#endif // GAME_H
