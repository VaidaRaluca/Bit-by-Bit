export module amode;
import player;
import board;
import game;
import <iostream>;
import <string>;

namespace eter {
	export class AMode {
	private:
		Player m_player1;
		Player m_player2;
		Board m_board;
		bool m_isPlayerTurn;//true pentru Player 1, false pentru Player 2
		int m_player1Wins;
		int m_player2Wins;
		Game* m_game;
	public:
		AMode(Player player1, Player player2, const Board& board);
		AMode(Game* game);
		void startMatch();
		void applyModeRules();
		 

	};
} // namespace eter
