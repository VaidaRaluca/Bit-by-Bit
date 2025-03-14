#include "amode.h"
using namespace eter;

uint8_t eter::AMode::getRoundsForWin() const
{
    return 2;
}

uint8_t eter::AMode::getRounds() const
{
    return 3;
}

AMode::AMode(Game* game) : m_game{ game } {}

void AMode::assignCardsInHand()
{

    std::vector<Card>cardsForPlayer1A{
                                       Card{1,"red",true},
                                       Card{1,"red",true},
                                       Card{2,"red",true},
                                       Card{2,"red",true},
                                       Card{3,"red",true},
                                       Card{3,"red",true},
                                       Card{4,"red",true},
                                       };
    std::vector<Card>cardsForPlayer2A{
                                       Card{1,"blue",true},
                                       Card{1,"blue",true},
                                       Card{2,"blue",true},
                                       Card{2,"blue",true},
                                       Card{3,"blue",true},
                                       Card{3,"blue",true},
                                       Card{4,"blue",true},
                                       };

    if (m_game)
    {
        m_game->GetPlayer1Ref().SetCardsInHand(cardsForPlayer1A);
        m_game->GetPlayer2Ref().SetCardsInHand(cardsForPlayer2A);
    }
}

void AMode::startMatch()
{
    size_t countRound = 1;
    std::cout << "The game has started \n";
    while (m_game->GetPlayer2Wins() < getRoundsForWin() && m_game->GetPlayer1Wins() < getRoundsForWin())
    {
        std::cout << "Round " << countRound << " of " << static_cast<int>(getRounds());
        startRound();
        countRound++;
        std::cout << "The round has ended. \n";
        qDebug() << m_game->GetPlayer1().GetName() << " wins: " << static_cast<int> (m_game->GetPlayer1Wins()) << "\n";
        qDebug() << m_game->GetPlayer2().GetName() << " wins: " << static_cast<int> (m_game->GetPlayer2Wins()) << "\n";

        // Reset the board and reassign cards
        assignCardsInHand();
        m_game->resetBoard();
        m_game->SetIsUsedExplosion(false);
    }

    if (m_game->GetPlayer1Wins() > m_game->GetPlayer2Wins())
        qDebug() << "Player " << m_game->GetPlayer1().GetName() << " wins this game!";
    else
        qDebug() << "Player " << m_game->GetPlayer2().GetName() << " wins this game!";

    std::cout << "GAME OVER \n";
}


void AMode::handleOption()
{
    enum  Option
    {
        OPTION_1 = 1,
        OPTION_2,
    };

   // std::cout << m_game->GetBoard();


    if (m_game->GetIsPlayerTurn())
        qDebug() << "It's " << m_game->GetPlayer1().GetName() << "'s turn\n";
    else
        qDebug() << "It's " << m_game->GetPlayer2().GetName() << "'s turn\n";

    int key;
    std::cout << "Choose an option: \n";
    std::cout << "Press 1 to place a card on the board \n";
    std::cout << "Press 2 to activate an illusion \n";
    // std::cin >> key;
    // Option option = static_cast<Option>(key);

    // switch (option) {
    // case OPTION_1:
    //     m_game->playTurn();
    //     break;
    // case OPTION_2:
    //     m_game->playIllusion();
    //     break;
    // default:
    //     std::cout << "Invalid option.\n";
    //     break;
    // }
}

void AMode::startRound()
{
    char gameStatus = '0';
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

        if (m_game->GetPlayer1().GetColor() == m_game->GetBoard().FindWinnerByScore())
        {
            qDebug() << "Player " << m_game->GetPlayer1().GetName() << " wins this round!" ;
            m_game->IncrementPlayer1Wins();
        }
        else
            if (m_game->GetPlayer2().GetColor() == m_game->GetBoard().FindWinnerByScore())
            {
                qDebug() << "Player " << m_game->GetPlayer2().GetName() << " wins this round!" ;
                m_game->IncrementPlayer2Wins();
            }
            else
                std::cout << "DRAW \n";
    }
    std::cout << m_game->GetBoard();
}

void AMode::applyModeRules()
{
    assignCardsInHand();
    startMatch();
}
