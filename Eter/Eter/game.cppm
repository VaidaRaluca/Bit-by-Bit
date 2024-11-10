#include<cstdint>
export module game;
import card;
import player;
import <string>;
import board;
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
		uint8_t m_player1Wins;
		uint8_t m_player2Wins;
		uint8_t m_nrRound;   // numarul rundei in care ne aflam

	public:
		Game() = default;
		Game(Player player1, Player player2, Board board, std::string gameMode);

		Player GetPlayer1();
		Player GetPlayer2();
		Board GetBoard();
		std::string GetGameMods();
		bool GetIsPlayerTurn();
		uint8_t GetPlayer1Wins();
		uint8_t GetPlayer2Wins();
		uint8_t GetNrRound();


		void SetBoard(Board board);
		void SetGameMods(std::string gameMode);
		void SetIsPlayerTurn();
		void IncrementPlayer1Wins();
		void IncrementPlayer2Wins();
		void IncrementNrRound();

		bool playTurn(int x, int y, const Card& card);
		void nextTurn();
		void startGame();

	};

}

