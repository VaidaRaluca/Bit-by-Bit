module bmode;
using namespace eter;
import game;
import player;
import card;
import gamemanager;
import <random>;
import<iostream>;
import <string>;

BMode::BMode(Game* game):
    m_game{game}
{
}

void BMode::applyModeRules()
{
    assignCardsInHand();
    generateMage();
    startMatch();
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
    Card(5,"red",true),  //valoare=5 ->  Carte eter
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
    Card(5,"blue",true),  //valoare=5 ->  Carte eter
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
    size_t countRound = 1;
    std::cout << "The game in B mode has started \n";
    while(m_game->GetPlayer2Wins() < knrRoundsForWin && m_game->GetPlayer1Wins() < knrRoundsForWin)
    {
        std::cout << "Round " << countRound << " of 5 \n";
        startRound(); 
        countRound++;
        std::cout << "The round has ended. \n";
        std::cout << "Wins player 1: " <<static_cast<int> (m_game->GetPlayer1Wins())<<"\n";
        std::cout << "Wins player 2: " << static_cast<int> (m_game->GetPlayer2Wins() )<< "\n";
        assignCardsInHand();
        m_game->resetBoard();
    }
    if (m_game->GetPlayer1Wins() > m_game->GetPlayer2Wins())
        std::cout << "Player " << m_game->GetPlayer1().GetName() << " wins this game!" << std::endl;
    else
        std::cout << "Player " << m_game->GetPlayer2().GetName() << " wins this game!" << std::endl;

    std::cout << "GAME OVER \n";
}

void BMode::startRound()
{
    char gameStatus = '0';
    while (gameStatus == '0')
    {
        handleOption();
        gameStatus = m_game->VerifyGameOver();
        std::cout <<"Game status: "<< gameStatus << "\n";
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
            std::cout << "Player " << m_game->GetPlayer1().GetName() << " wins this round!" << std::endl;
        else
            if (m_game->GetPlayer2().GetColor() == m_game->GetBoard().findWinnerByScore())
                std::cout << "Player " << m_game->GetPlayer2().GetName() << " wins this round!" << std::endl;
            else
                std::cout << "DRAW \n";
    }
    std::cout << m_game->GetBoard();
}

void BMode::handleOption()
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
    std::cout << "Press 4 to activate the mage \n";
    std::cin >> key;
    Option option = static_cast<Option>(key);

    switch (option) {
    case OPTION_1:
        m_game->playTurn();
        break;
    case OPTION_2:
        //activare iluzie
        m_game->playIllusion();
        break;
    case OPTION_3:
        //activare explozie
        break;
    case OPTION_4:
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
