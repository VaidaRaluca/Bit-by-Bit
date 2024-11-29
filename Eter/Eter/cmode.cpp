module cmode;
using namespace eter;
import card;
import player;
import game;
import gamemanager;
import <random>;
import <iostream>;
import <string>;

CMode::CMode(Game* game): m_game{game}
{}

void CMode::applyModeRules()
{
    generatePower();
    assignCardsInHand();
    startMatch();
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
   Card(5,"red",true), //eter
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
    Card(5,"blue",true), 
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
    size_t countRound = 1;
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

    std::cout << "GAME OVER \n";
}

void eter::CMode::handleOption()
{
    enum  Option
    {
        OPTION_1 = 1,
        OPTION_2,
        OPTION_3,
        OPTION_4
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
    std::cout << "Press 3 to activate an explosion \n";
    std::cout << "Press 4 to activate the elemental power \n";
    std::cin >> key;
    Option option = static_cast<Option>(key);
    bool activatedPower1 = 0;

    switch (option) {
    case OPTION_1:
        m_game->playTurn();
        break;
    case OPTION_2:
        m_game->playIllusion();
        break;
    case OPTION_3:
        break;
    case OPTION_4:
        if (!activatedPower1)
        {
            if (m_game->GetIsPlayerTurn())
            {
                m_power1Player1.activate(m_game->GetPlayer1Ref(), m_game->GetPlayer2Ref(), m_game->GetBoardRef());
                m_game->SetIsPlayerTurn();
            }
            else
            {
                m_power1Player2.activate(m_game->GetPlayer2Ref(), m_game->GetPlayer1Ref(), m_game->GetBoardRef());
                m_game->SetIsPlayerTurn();
            }
            activatedPower1 = 1;
        }
        else {
            if (m_game->GetIsPlayerTurn())
            {
                m_power2Player1.activate(m_game->GetPlayer1Ref(), m_game->GetPlayer2Ref(), m_game->GetBoardRef());
                m_game->SetIsPlayerTurn();
            }
            else
            {
                m_power2Player2.activate(m_game->GetPlayer2Ref(), m_game->GetPlayer1Ref(), m_game->GetBoardRef());
                m_game->SetIsPlayerTurn();
            }
        }
        break;
    default:
        std::cout << "Invalid option.\n";
        break;
    }
}
