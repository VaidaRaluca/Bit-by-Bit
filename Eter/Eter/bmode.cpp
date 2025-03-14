#include "BMode.h"
using namespace eter;
#include <random>

uint8_t eter::BMode::GetRoundsForWin() const
{
    return 3;
}

uint8_t eter::BMode::GetRounds() const
{
    return 5;
}

BMode::BMode(Game* game):
    AMode{game}
{}

void BMode::applyModeRules()
{
    m_game->GetBoardRef().SetDimMax(4);
    generateMage();
    AMode::applyModeRules();
}

Mage eter::BMode::GetMageForPlayer1() const
{
    return m_magePlayer1;
}

Mage eter::BMode::GetMageForPlayer2() const
{
    return m_magePlayer2;
}

void BMode::assignCardsInHand()
{
    std::vector<Card>cardsForPlayer1{
    Card{1,"red",true},
    Card{1,"red",true},
    Card{2,"red",true},
    Card{2,"red",true},
    Card{2,"red",true},
    Card{3,"red",true},
    Card{3,"red",true},
    Card{3,"red",true},
    Card{4,"red",true},
    Card{5,"red",true}  //valoare=5 ->  Carte eter
    };
    std::vector<Card>cardsForPlayer2{
    Card{1,"blue",true},
    Card{1,"blue",true},
    Card{2,"blue",true},
    Card{2,"blue",true},
    Card{2,"blue",true},
    Card{3,"blue",true},
    Card{3,"blue",true},
    Card{3,"blue",true},
    Card{4,"blue",true},
    Card{5,"blue",true}  //valoare=5 ->  Carte eter
    };

    if (m_game)
    {
        m_game->GetPlayer1Ref().SetCardsInHand(cardsForPlayer1);
        m_game->GetPlayer2Ref().SetCardsInHand(cardsForPlayer2);
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
    AMode::startMatch();
}

void BMode::startRound()
{
    AMode::startRound();
}

void BMode::handleOption()
{
    enum  Option
    {
        OPTION_1 = 1,
        OPTION_2,
        OPTION_3,
    };
 
    std::cout << m_game->GetBoard();

    if (m_game->GetIsPlayerTurn())
        std::cout << "It's " << m_game->GetPlayer1().GetName() << "'s turn\n";
    else
        std::cout << "It's " << m_game->GetPlayer2().GetName() << "'s turn\n";

    int key;
    std::cout << "Choose an option: \n";
    std::cout << "Press 1 to place a card on the board \n";
    std::cout << "Press 2 to activate an illusion \n";
    std::cout << "Press 3 to activate your mage \n";
    std::cin >> key;
    Option option = static_cast<Option>(key);

    switch (option) {
    case OPTION_1:
        m_game->playTurn();
        break;
    case OPTION_2:
        m_game->playIllusion();
        break;
    case OPTION_3:
        if (m_game->GetIsPlayerTurn())
        {
            m_magePlayer1.activate(m_game->GetPlayer1Ref(), m_game->GetPlayer2Ref(), m_game->GetBoardRef());
            m_game->SetIsPlayerTurn();
        }
        else
        {
            m_magePlayer2.activate(m_game->GetPlayer2Ref(), m_game->GetPlayer1Ref(), m_game->GetBoardRef());
            m_game->SetIsPlayerTurn();
        }
        break;
    default:
        std::cout << "Invalid option.\n";
        break;
    }
  
}
