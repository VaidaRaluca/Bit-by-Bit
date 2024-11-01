export module game;
import <vector>;
import card;
import player;
import gamemods;
import board;
namespace eter
{
	export class Game
	{
	private:
		Player m_player1;
		Player m_player2;
		Board m_board;
		GameMods m_gameMode;
	public:
		Game();
		Game(Player player1, Player player2, Board board, GameMods gameMode);
		void SetPlayer1(Player player);
		Player GetPlayer1();
		void SetPlayer2(Player player);
		Player GetPlayer2();
		void SetBoard();
		Board GetBoard();
		void SetGameMods();
		GameMods GetGameMOds();

	};

}

