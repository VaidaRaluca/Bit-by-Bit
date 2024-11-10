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
	{
	}
	 
	void AMode::startMatch() 
	{
		const int WINNING_ROUNDS = 2;
		std::cout << "Incepe meciul in modul AMode!" << std::endl;
		while (m_player1Wins < WINNING_ROUNDS && m_player2Wins < WINNING_ROUNDS) 
			if(m_isPlayerTurn)
			{
			// Jucatorul 1
			std::cout << "Este randul jucatorului 1 (" << m_player1.GetName() << ").\n";
			// Logica pentru player 1
			 
		      }
          else 
			 {
	 
	 std::cout << "Este randul jucatorului 2 (" << m_player2.GetName() << ").\n";
	 // Logica pentru pl 2
		 }
	}

 
	void AMode::applyModeRules() 
	{
	 
	}

	 
}  
