module gamemanager;
import game;
import player;
import board;
import bmode;
using namespace eter;

GameManager::GameManager(const Game& game):
	m_game{game}
{
}

const Game& GameManager::GetGame() const
{
	return m_game;
}

void GameManager::SetGame(Game game)
{
	m_game=Game( game) ;
}

void GameManager::StartNewGame(Player player1, Player player2, Board board, const std::string& gameMode)
{
		m_game = Game(player1, player2, board, gameMode);
		if (gameMode == "BMode")
		{
			BMode bmode(&m_game); // Se trece referința la joc
			bmode.applyModeRules(); // Aplică regulile pentru acest mod
		}
		m_game.startGame(); 
}