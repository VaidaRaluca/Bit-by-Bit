module game;
using namespace eter;
import card;
import player;
import gamemods;
import board;

Game::Game(Player player1, Player player2, Board board, GameMods gameMode):
	m_player1{player1},m_player2{player2},m_board{board},m_gameMode{gameMode}
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

GameMods Game::GetGameMOds()
{
	return m_gameMode;
}


void eter::Game::SetBoard(Board board)
{
	m_board = board;
}

void Game::SetGameMods(GameMods gameMode)
{
	m_gameMode = gameMode;
}


