export module game;
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
		Game()=default;
		Game(Player player1, Player player2, Board board, GameMods gameMode); 

		Player GetPlayer1();
		Player GetPlayer2();
		Board GetBoard();
		GameMods GetGameMOds();

		
		void SetBoard(Board board); 
		void SetGameMods(GameMods gameMode);

	};

}

