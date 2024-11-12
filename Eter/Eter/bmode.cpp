module bmode;
using namespace eter;
import game;
import player;
import card;
import gamemanager;
import <random>;
import<iostream>;

BMode::BMode(Game* game):
    m_game{game}
{
}

void BMode::applyModeRules()
{
    assignCardsInHand();
    generateMage();
}

void BMode::assignCardsInHand()
{
    std::vector<Card>cardsForPlayer1{
    Card(1,"red",true),
    Card(1,"red",true),
    Card(2,"red",true),
    Card(2,"red",true),
    Card(2,"red",true),
    Card(3,"red",true),
    Card(3,"red",true),
    Card(3,"red",true),
    Card(4,"red",true),
    Card(0,"red",true),  //valoare=0 ->  Carte eter
    };
    std::vector<Card>cardsForPlayer2{
    Card(1,"blue",true),
    Card(1,"blue",true),
    Card(2,"blue",true),
    Card(2,"blue",true),
    Card(2,"blue",true),
    Card(3,"blue",true),
    Card(3,"blue",true),
    Card(3,"blue",true),
    Card(4,"blue",true),
    Card(0,"blue",true),  //valoare=0 ->  Carte eter
    };

    if (m_game)
    {
        m_game->GetPlayer1().SetCardsInHand(cardsForPlayer1);
        m_game->GetPlayer2().SetCardsInHand(cardsForPlayer2);
    }
}
void BMode::generateMage()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, m_mages.size() - 1);

    int index1 = dist(gen);
    int index2 = dist(gen);
    while (index1 == index2) {
        index2 = dist(gen);
    }
     
    m_magePlayer1 = m_mages[index1];
    m_magePlayer2 = m_mages[index2];
    
}

void BMode::startMatch()
{   
    for (int round = 1; round <= 5; ++round) 
    {
        std::cout << "Round " << round << " from 5" << std::endl;
        startRound(); 
    }
    std::cout << "Game over. \n";    
}

void BMode::startRound()
{
   
}
