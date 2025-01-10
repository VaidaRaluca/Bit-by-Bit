#include "CMode.h"
using namespace eter;
//import card;
//import player;
//import game;
//import gamemanager;
#include <random>
#include <iostream>
#include <string>
#include<ostream>

CMode::CMode(Game* game) : AMode{ game }
{
}

uint8_t eter::CMode::getRoundsForWin() const
{
    return 3;
}

uint8_t eter::CMode::getRounds() const
{
    return 5;
}

void CMode::applyModeRules()
{
    m_game->GetBoardRef().SetDimMax((uint8_t)4);
    generatePower();
    AMode::applyModeRules();
}

void eter::CMode::generatePower()
{
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
    AMode::startRound();
    /*char gameStatus = '0';
    while (gameStatus == '0')
    {
        handleOption();
        gameStatus = m_game->VerifyGameOver();
        std::cout << "Game status: " << gameStatus << "\n";
    }
    std::cout << gameStatus << "\n";
    if (gameStatus == '2' || gameStatus == '3')
    {
        std::string choice;
        std::cout << "Do you want to continue the game with a single move? (YES or NO) \n";
        std::cin >> choice;
        if (choice == "YES")
            handleOption();
        if (m_game->GetPlayer1().GetColor() == m_game->GetBoard().findWinnerByScore())
        {
            std::cout << "Player " << m_game->GetPlayer1().GetName() << " wins this round!" << std::endl;
            m_game->IncrementPlayer1Wins();
        }
        else
            if (m_game->GetPlayer2().GetColor() == m_game->GetBoard().findWinnerByScore())
            {
                std::cout << "Player " << m_game->GetPlayer2().GetName() << " wins this round!" << std::endl;
                m_game->IncrementPlayer2Wins();
            }
            else
                std::cout << "DRAW \n";
    }
    std::cout << m_game->GetBoard();*/
}
void CMode::startMatch()
{
    AMode::startMatch();
    /*size_t countRound = 1;
    std::cout << "The game in C mode has started \n";
    while (m_game->GetPlayer2Wins() < knrRoundsForWin && m_game->GetPlayer1Wins() < knrRoundsForWin)
    {
        std::cout << "Round " << countRound << " of 5 \n";
        startRound();
        countRound++;
        std::cout << "The round has ended. \n";
        std::cout << m_game->GetPlayer1().GetName() << " wins: " << static_cast<int> (m_game->GetPlayer1Wins()) << "\n";
        std::cout << m_game->GetPlayer2().GetName() << " wins: " << static_cast<int> (m_game->GetPlayer2Wins()) << "\n";
        assignCardsInHand();
        m_game->resetBoard();
    }
    if (m_game->GetPlayer1Wins() > m_game->GetPlayer2Wins())
        std::cout << "Player " << m_game->GetPlayer1().GetName() << " wins this game!" << std::endl;
    else
        std::cout << "Player " << m_game->GetPlayer2().GetName() << " wins this game!" << std::endl;

    std::cout << "GAME OVER \n";*/
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
    case OPTION_3:
       {
        // Selectarea unei puteri elementale
        std::cout << "Select an elemental power:\n";
        int abilityIndex = 0;
        for (int i = 0; i <= static_cast<int>(eter::elementalPowerCards::powerAbility::rock); ++i) {
            std::cout << i << " - " << static_cast<eter::elementalPowerCards::powerAbility>(i) << "\n";
        }
        std::cin >> abilityIndex;

        if (abilityIndex < 0 || abilityIndex > static_cast<int>(eter::elementalPowerCards::powerAbility::rock)) {
            std::cout << "Invalid ability selection.\n";
            break;
        }

        eter::elementalPowerCards::powerAbility selectedAbility =
            static_cast<eter::elementalPowerCards::powerAbility>(abilityIndex);

        eter::elementalPowerCards elementalPower(selectedAbility);

        // Verificăm dacă puterea a fost utilizată
        if (elementalPower.getUsed()) {
            std::cout << "This power has already been used.\n";
        }
        else {
            if (m_game->GetIsPlayerTurn()) {
                elementalPower.activate(m_game,m_game->GetPlayer1Ref(), m_game->GetPlayer2Ref(), m_game->GetBoardRef());
            }
            else {
                elementalPower.activate(m_game,m_game->GetPlayer2Ref(), m_game->GetPlayer1Ref(), m_game->GetBoardRef());
            }
            elementalPower.setUsed(true);
            m_game->SetIsPlayerTurn();
        }
        break;
    }
    default:
        std::cout << "Invalid option.\n";
        break;
    }
}