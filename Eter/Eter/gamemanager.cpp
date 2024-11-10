module gamemanager;
import game;
import player;
import board;
import bmode;
import cmode;
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
		if (gameMode == "AMode")
		{
			AMode amode(&m_game);
			amode.applyModeRules();
		}
		if (gameMode == "BMode")
		{
			m_bmode = std::make_unique<BMode>(&m_game); 
			m_bmode->applyModeRules(); 
		}
		if (gameMode == "CMode")
		{
			CMode cmode(&m_game);
			cmode.applyModeRules();
		}
		m_game.startGame(); 
}