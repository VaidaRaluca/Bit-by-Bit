module cmode;
using namespace eter;
import player;
import game;
import gamemanager;
import <random>;

CMode::CMode(Game* game): m_game{game}
{}

void CMode::applyModeRules()
{
    generatePower();
    assignCardsInHand();
}
void eter::CMode::generatePower()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, m_power.size() - 1);

    int indexPower1Player1 = dist(gen);
    int indexPower2Player1;
    do {
        indexPower2Player1 = dist(gen);
    } while (indexPower2Player1 == indexPower1Player1);

    int indexPower1Player2;
    int indexPower2Player2;
    do {
        indexPower1Player2 = dist(gen);
    } while (indexPower1Player2 == indexPower1Player1 || indexPower1Player2 == indexPower2Player1);

    do {
        indexPower2Player2 = dist(gen);
    } while (indexPower2Player2 == indexPower1Player2 || indexPower2Player2 == indexPower1Player1 || indexPower2Player2 == indexPower2Player1);

    m_power1Player1 = m_power[indexPower1Player1];
    m_power2Player1 = m_power[indexPower2Player1];
    m_power1Player2 = m_power[indexPower1Player2];
    m_power2Player2 = m_power[indexPower2Player2];
}

void CMode::assignCardsInHand()
{
    std::vector<Card>cardsForPlayer1{
   Card(1,"red",true),
   Card(2,"red",true),
   Card(2,"red",true),
   Card(2,"red",true),
   Card(3,"red",true),
   Card(3,"red",true),
   Card(3,"red",true),
   Card(4,"red",true),
   Card(0,"red",true), 
    };
    std::vector<Card>cardsForPlayer2{
    Card(1,"blue",true),
    Card(2,"blue",true),
    Card(2,"blue",true),
    Card(2,"blue",true),
    Card(3,"blue",true),
    Card(3,"blue",true),
    Card(3,"blue",true),
    Card(4,"blue",true),
    Card(0,"blue",true), 
    };
    if (m_game)
    {
        m_game->GetPlayer1().SetCardsInHand(cardsForPlayer1);
        m_game->GetPlayer2().SetCardsInHand(cardsForPlayer2);
    }
}

void CMode::startRound()
{

}
void CMode::startMatch()
{
    for (int round = 1; round <= 5; ++round)
    {
        std::cout << "Round " << round << " from 3" << std::endl;
        startRound();
    }
    std::cout << "Game over. \n";
}
