module amode;
import player;
import board;
import <iostream>;
import <string>;

namespace eter {

 	AMode::AMode(Player player1, Player player2, const Board& board)
		: m_player1{ player1 }, m_player2{ player2 }, m_board{ board }, m_player1Wins{ 0 }, m_player2Wins{ 0 }
	{}

	AMode::AMode(Game * game):
	  m_game{game}
	{}
	 
	void AMode::startMatch() 
	{
		size_t kWINNING_ROUNDS = 2;
		std::cout << "Incepe meciul in modul AMode!" << std::endl;
		while (m_player1Wins < kWINNING_ROUNDS && m_player2Wins < kWINNING_ROUNDS) 
		{
			if (m_isPlayerTurn)
			{
				// Jucatorul 1
				std::cout << "Este randul jucatorului 1 (" << m_player1.GetName() << ").\n";


			}
			else
			{
				std::cout << "Este randul jucatorului 2 (" << m_player2.GetName() << ").\n";
				// Logica pentru pl 2
			}
			const std::string winnerColor = m_board.findWinner();
			if (winnerColor == m_player1.GetColor())
				m_game->IncrementPlayer1Wins();
			else if(winnerColor==m_player2.GetColor())
				m_game->IncrementPlayer2Wins();
			if (m_board.isBoardFull())
				break;
		}
	}

 
	void AMode::applyModeRules() 
	{
	 
	}

	 
}  
