module gamemanager;
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

void GameManager::StartNewGame(Player player1, Player player2, const std::string& gameMode)
{
		m_game = Game(player1, player2, gameMode);
		if (gameMode == "AMode")
		{
			m_amode= std::make_unique<AMode>(&m_game);
			std::cout << "Starting A mode game\n";
			m_amode->applyModeRulesModeA();
		}
		if (gameMode == "BMode")
		{
			m_bmode = std::make_unique<BMode>(&m_game); 
			m_bmode->applyModeRules(); 
		}
		if (gameMode == "CMode")
		{
			m_cmode = std::make_unique<CMode>(&m_game);
			m_cmode->applyModeRules();
		}
}