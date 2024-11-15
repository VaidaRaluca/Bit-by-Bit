module game;
using namespace eter;
import card;
import player;
import <string>;
import <iostream>;
import amode;
import bmode;

Game::Game(Player player1, Player player2, Board board, std::string gameMode):
	m_player1{player1},m_player2{player2},m_board{board},m_gameMode{gameMode}, m_isPlayerTurn{true},
    m_player1Wins{0},m_player2Wins{0},m_nrRound{0}
{}

Player Game::GetPlayer1()
{
	return m_player1;
}

Player Game::GetPlayer2() 
{
	return m_player2; 
}

Board Game::GetBoard()
{
	return m_board;
}

std::string Game::GetGameMods()
{
	return m_gameMode;
}

bool Game::GetIsPlayerTurn()
{
    return m_isPlayerTurn;
}

uint8_t Game::GetPlayer1Wins()
{
    return m_player1Wins;
}

uint8_t Game::GetPlayer2Wins()
{
    return m_player2Wins;
}

uint8_t Game::GetNrRound()
{
    return m_nrRound;
}


void Game::SetBoard(Board board)
{
	m_board = board;
}

void Game::SetGameMods(std::string gameMode)
{
	m_gameMode = gameMode;
}

void Game::SetIsPlayerTurn()
{
    m_isPlayerTurn = !m_isPlayerTurn;
}

void Game::IncrementPlayer1Wins()
{
    ++m_player1Wins;
}

void Game::IncrementPlayer2Wins()
{
    ++m_player2Wins;
}

void Game::IncrementNrRound()
{
    ++m_nrRound;
}

void Game::playTurn()
{
    if (m_isPlayerTurn) 
    {    
        m_player1.PrintCardsInHand();
        std::cout << m_player1.GetName() << " introdu coordonatele pozitiei de pe tabla (x si y) si indexul cartii pe care doresti sa o plasezi ";
        int x, y;
        int cardIndex; //indexul din vectorul CardsInHand
        std::cout << "x= ";std::cin >> x;
        std::cout << "y= ";std::cin >> y;
        std::cout << "CardIndex= ";std::cin >> cardIndex;
        bool ok = m_player1.placeCard(x, y, m_player1.GetCardsInHand().at(cardIndex), m_board);
        while (!ok)
        {
            std::cout << m_player1.GetName() << " introdu coordonatele pozitiei de pe tabla (x si y) si indexul cartii pe care doresti sa o plasezi ";
            std::cout << "x= ";std::cin >> x;
            std::cout << "y= ";std::cin >> y;
            std::cout << "CardIndex= ";std::cin >> cardIndex;
            ok = m_player1.placeCard(x, y, m_player1.GetCardsInHand().at(cardIndex), m_board);
        }
        SetIsPlayerTurn();
    }
    else
    {
        m_player2.PrintCardsInHand();
        std::cout << m_player2.GetName() << " introdu coordonatele pozitiei de pe tabla (x si y) si indexul cartii pe care doresti sa o plasezi ";
        int x, y;
        int cardIndex; //indexul din vectorul CardsInHand
        std::cout << "x= ";std::cin >> x;
        std::cout << "y= ";std::cin >> y;
        std::cout << "CardIndex= ";std::cin >> cardIndex;
        bool ok = m_player2.placeCard(x, y, m_player2.GetCardsInHand().at(cardIndex), m_board);
        while (!ok)
        {
            std::cout << m_player2.GetName() << " introdu coordonatele pozitiei de pe tabla (x si y) si indexul cartii pe care doresti sa o plasezi ";
            std::cout << "x= ";std::cin >> x;
            std::cout << "y= ";std::cin >> y;
            std::cout << "CardIndex= ";std::cin >> cardIndex;
            ok = m_player1.placeCard(x, y, m_player1.GetCardsInHand().at(cardIndex), m_board);
        }
        SetIsPlayerTurn();
    }	
}

void Game::startGame()
{
    if (m_gameMode == "AMode") 
    {
        AMode mode(m_player1, m_player2, m_board);
        mode.startMatch();   
    }
    else
        if (m_gameMode == "BMode")
        {  
             


        }
        else {
         
            std::cout << "Modul de joc necunoscut!" << std::endl;
         }
}

uint8_t Game::VerifyGameOver()
{
    const std::string winnerColor = m_board.findWinner();
    if (GetIsPlayerTurn())
    {
        if (winnerColor == m_player1.GetColor())
        {
            IncrementPlayer1Wins();
            return 1;
        }
        if (m_player1.GetCardsInHand().empty())
            return 2;
    }
    else
    {
        if (winnerColor == m_player2.GetColor())
        {
            IncrementPlayer2Wins();
            return 1;
        }
        if (m_player2.GetCardsInHand().empty())
            return 2;
    }
    if (m_board.isBoardFull())
        return 3;

    return 0;
}



