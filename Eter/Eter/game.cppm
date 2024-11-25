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

		//Functii ajutatoare
		void handlePlayerTurn(Player& player);
		void handlePlayerTurnWithIllusion(Player& player);
		void getInputCoordinates(int& x, int& y, int& cardIndex);

	public:
		Game() = default;
		Game(Player player1, Player player2, Board board, std::string gameMode);

		Player GetPlayer1() const;
		Player GetPlayer2() const;
		Board GetBoard() const;

		//Getter ce returneaza &
		Player& GetPlayer1Ref();
		Player& GetPlayer2Ref();
		Board& GetBoardRef();

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

		void playTurn();
		void playIllusion();

		char VerifyGameOver();
		void resetBoard();
		void ReassignCardsToPlayers();
		void handleCardCover(Player& currentPlayer, Player& opponent, int x, int y, int cardIndex);

	};

}

