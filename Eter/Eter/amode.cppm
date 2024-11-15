export module amode;
import player;
import board;
import game;
import card;
import <iostream>;
import <string>;
import <memory>;

namespace eter {
	enum class Action : uint8_t {
		PlaceCard = 1,
		ActivateIllusion,
		ActivateExplosion,
 		Invalid  // For invalid input handling
	};
	export class AMode {
	private:
		Player m_player1;
		Player m_player2;
		Board m_board;
		bool m_isPlayerTurn;//true pentru Player 1, false pentru Player 2
		int m_player1Wins;
		int m_player2Wins;
		std::unique_ptr<Game> m_game;
		bool isCardPlaceable(const Card& card);
		bool checkWinningCondition();

		//Functii ajutatoare
		void handlePlaceCard();
		void handleActivateIllusion();
		void handleActivateExplosion();
		void handleGameOverCheck();

	public:
		AMode(Player player1, Player player2, const Board& board);
		AMode(Game* game);
		void startMatch();
		void applyModeRules();
		void AssignCardsInHandModeA();
		Action promptPlayerAction();
		~AMode() = default;
		
	};
} // namespace eter
