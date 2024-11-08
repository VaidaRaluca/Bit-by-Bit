module game;
using namespace eter;
import card;
import player;
import <string>;
import <iostream>;
import amode;

Game::Game(Player player1, Player player2, Board board, std::string gameMode):
	m_player1{player1},m_player2{player2},m_board{board},m_gameMode{gameMode}, m_isPlayerTurn{true}
{
}

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

std::string Game::GetGameMOds()
{
	return m_gameMode;
}


void eter::Game::SetBoard(Board board)
{
	m_board = board;
}

void Game::SetGameMods(std::string gameMode)
{
	m_gameMode = gameMode;
}

bool eter::Game::playTurn(int x, int y, const Card& card)
{
    if (m_isPlayerTurn) {
        if (m_player1.placeCard(x, y, card, m_board))
        {
            std::cout << m_player1.GetName() << " a plasat o carte pe (" << x << ", " << y << ").\n";
        }
        else {
            std::cout << "Plasarea cartii de catre " << m_player1.GetName() << " a esuat.\n";
            return false;  
        }
    }
    else {
        if (m_player2.placeCard(x, y, card, m_board)) 
        {
            std::cout << m_player2.GetName() << " a plasat o carte pe (" << x << ", " << y << ").\n";
        }
        else {
            std::cout << "Plasarea cartii de catre " << m_player2.GetName() << " a esuat.\n";
            return false;  //  false daca nu se poate plasa cartea
        }
    }

    // Dupa ce mutarea este validă, schimbăm tura
    nextTurn();
    return true;
	
}

void eter::Game::nextTurn()
{
    m_isPlayerTurn = !m_isPlayerTurn;
}

void eter::Game::startGame()
{
    if (m_gameMode == "AMode") 
    {
         AMode mode(m_player1, m_player2, m_board);
        mode.startMatch();   
    }
    else {
         
        std::cout << "Modul de joc necunoscut!" << std::endl;
    }
}



