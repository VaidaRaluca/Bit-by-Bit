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
    std::cout << "Jocul in modul B a inceput \n";
    while(m_game->GetPlayer2Wins() < knrRoundsForWin && m_game->GetPlayer1Wins() < knrRoundsForWin)
    {
        std::cout << "Runda " << countRound << " din 5 \n";
        startRound(); 
        countRound++;
    }
}

void BMode::startRound()
{
    uint8_t gameStatus = 0;
    while (gameStatus == 0) 
    {
        handleOption();
        gameStatus = m_game->VerifyGameOver();
    }
    if (gameStatus == 2 || gameStatus == 3)
    {
        char choice;
        std::cout << "Vrei sa mai continui jocul cu o singura mutare? (DA sau NU) \n";
        std::cin >> choice;
        if (choice == 'DA')
            handleOption();
        if (m_game->GetPlayer1().GetColor() == m_game->GetBoard().findWinnerByScore())
            std::cout << "Felicitari " << m_game->GetPlayer1().GetName() << " ai castigat! \n ";
        else
            if (m_game->GetPlayer2().GetColor() == m_game->GetBoard().findWinnerByScore())
                std::cout << "Felicitari " << m_game->GetPlayer2().GetName() << " ai castigat! \n ";
            else
                std::cout << "REMIZA \n";
    }
    else
    {
        std::cout << "Jocul s-a terminat \n";
        if (m_game->GetIsPlayerTurn())
            std::cout << "Felicitari " << m_game->GetPlayer1().GetName() << " ai castigat! \n ";
        else
            std::cout << "Felicitari " << m_game->GetPlayer2().GetName() << " ai castigat! \n ";
    }
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
        std::cout << "Este randul jucatorului " << m_game->GetPlayer1().GetName()<<"\n";
    else
        std::cout << "Este randul jucatorului " << m_game->GetPlayer2().GetName()<<"\n";

    int key;
    std::cout << "Alege o optiune: \n";
    std::cout << "Apasa tasta 1 pentru a plasa o carte pe tabla \n";
    std::cout << "Apasa tasta 2 pentru a activa o iluzie \n";
    std::cout << "Apasa tasta 3 pentru a activa o explozie \n";
    std::cout << "Apasa tasta 4 pentru a activa vrajitorul \n";
    std::cin >> key;
    Option option = static_cast<Option>(key);

    switch (option) {
    case OPTION_1:
        m_game->playTurn();
        break;
    case OPTION_2:
        //activare iluzie
        break;
    case OPTION_3:
        //activare explozie
        break;
    case OPTION_4:
        if (m_game->GetIsPlayerTurn())
            m_magePlayer1.activate(m_game->GetPlayer1Ref(), m_game->GetPlayer2Ref(),m_game->GetBoardRef());
        else
            m_magePlayer2.activate(m_game->GetPlayer2Ref(),m_game->GetPlayer1Ref(),m_game->GetBoardRef());
        break;
    default:
        std::cout << "Optiune invalida.\n";
        break;
    }
  
}
