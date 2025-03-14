﻿#include "CMode.h"
using namespace eter;
#include <random>
#include <iostream>
#include <string>
#include<ostream>

CMode::CMode(Game* game) : AMode{ game }
{
}

uint8_t eter::CMode::GetRoundsForWin() const
{
    return 3;
}

uint8_t eter::CMode::GetRounds() const
{
    return 5;
}

void CMode::applyModeRules()
{
    m_game->GetBoardRef().SetDimMax((uint8_t)4);
    generatePower();
    AMode::applyModeRules();
}

void eter::CMode::generatePower() {
    if (m_power.size() < 2) {
        std::cerr << "Error: Not enough powers available to generate two unique powers.\n";
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, m_power.size() - 1);

     int indexPower1 = dist(gen);
    int indexPower2;
    do {
        indexPower2 = dist(gen);
    } while (indexPower2 == indexPower1);

     m_power1 = m_power[indexPower1];
    m_power2 = m_power[indexPower2];

 
    if (indexPower1 > indexPower2) {
        std::swap(indexPower1, indexPower2); 
    }
    m_power.erase(m_power.begin() + indexPower2);
    m_power.erase(m_power.begin() + indexPower1);

    std::cout << std::endl;
    std::cout << "New powers generated for this round:\n";
    
     
}

void CMode::assignCardsInHand()
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
   Card{5,"red",true}, //eter
    };
    std::vector<Card>cardsForPlayer2{
    Card{1,"blue",true },
    Card{1,"blue",true },
    Card{2,"blue",true },
    Card{2,"blue",true},
    Card{2,"blue",true},
    Card{3,"blue",true},
    Card{3,"blue",true},
    Card{3,"blue",true},
    Card{4,"blue",true},
    Card{5,"blue",true},
    };
    if (m_game)
    {
        m_game->GetPlayer1Ref().SetCardsInHand(cardsForPlayer1);
        m_game->GetPlayer2Ref().SetCardsInHand(cardsForPlayer2);
    }
}

void CMode::startRound()
{
    generatePower();
    AMode::startRound();
  
}
void CMode::startMatch()
{
    AMode::startMatch();
  
}

void eter::CMode::handleOption()
{
    enum  Option
    {
        OPTION_1 = 1,
        OPTION_2,
        OPTION_3
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
    std::cout << "Press 3 to activate the elemental power \n";
    std::cin >> key;
    Option option = static_cast<Option>(key);
    static bool activatedPower1 = 0;

    switch (option) {
    case OPTION_1:
        m_game->playTurn();
        break;
    case OPTION_2:
        m_game->playIllusion();
        break;
    case OPTION_3: {
        std::cout << "Select an elemental power:\n";
        std::cout << "1 "<< "\n";
        std::cout << "2 "   << "\n";

        int powerChoice;
        std::cin >> powerChoice;

        if (powerChoice != 1 && powerChoice != 2) {
            std::cout << "Invalid power selection.\n";
            break;
        }

        eter::elementalPowerCards selectedPower = (powerChoice == 1) ? m_power1 : m_power2;

        if (selectedPower.GetUsed()) {
            std::cout << "This power has already been used.\n";
            break;
        }

        if (m_game->GetIsPlayerTurn()) {
            selectedPower.activate(m_game, m_game->GetPlayer1Ref(), m_game->GetPlayer2Ref(), m_game->GetBoardRef());
        }
        else {
            selectedPower.activate(m_game, m_game->GetPlayer2Ref(), m_game->GetPlayer1Ref(), m_game->GetBoardRef());
        }

        selectedPower.SetUsed(true);
        m_game->SetIsPlayerTurn();
        break;
    }
    default:
        std::cout << "Invalid option.\n";
        break;
    }
}