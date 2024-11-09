export module gamemanager;

import card;
import player;
import game;
import board;

namespace eter
{
	export class GameManager
	{
	private:
		Game m_game;
	public:
		GameManager() = default;
		GameManager(const Game& game);

		const Game& GetGame()const;
		void SetGame(Game game);
		void StartNewGame(Player player1, Player player2, Board board, const std::string& gameMode);
		void LoadGame();   // Metoda pentru incarcarea unui joc anterior 
	};
}