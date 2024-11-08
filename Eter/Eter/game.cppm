export module game;
import card;
import player;
import <string>;
import board;
import<string>;
namespace eter
{
	export class Game
	{
	private:
		Player m_player1;
		Player m_player2;
		Board m_board;
		std::string m_gameMode;
		bool m_isPlayerTurn;  // true pentru p1,false pentru p2

	public:
		Game() = default;
		Game(Player player1, Player player2, Board board, std::string gameMode);

		Player GetPlayer1();
		Player GetPlayer2();
		Board GetBoard();
		std::string GetGameMOds();


		void SetBoard(Board board);
		void SetGameMods(std::string gameMode);
		bool playTurn(int x, int y, const Card& card);
		void nextTurn();
		void startGame();

	};

}

