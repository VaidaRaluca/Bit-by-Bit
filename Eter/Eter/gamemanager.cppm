export module gamemanager;

import <memory>;
import game;
import board;
import bmode;
import amode;
import cmode;


namespace eter
{
	export class GameManager
	{
	private:
		Game m_game;
		std::unique_ptr<AMode> m_amode;
		std::unique_ptr<BMode> m_bmode;
		std::unique_ptr<CMode> m_cmode;
	public:
		GameManager() = default;
		GameManager(const Game& game);

		const Game& GetGame()const;
		void SetGame(Game game);
		void StartNewGame(Player player1, Player player2, const std::string& gameMode);
		void LoadGame();   // Metoda pentru incarcarea unui joc anterior
		void SaveGame();   // Metoda pentru salvarea unui joc
	};
}