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
		Game* m_game;
		const uint8_t knrRoundsForWin = 2;


		//Functii ajutatoare
 		
 
	public:
		AMode() = default;
		AMode(Game* game);
		void assignCardsInHandModeA();
		void startMatchModeA();
		void handleOptionModeA();  // afiseaza optiunile utilizatorului
		void startRoundModeA();  //porneste runda
		void applyModeRulesModeA(); // aplica toate regulile jocului
		void handleActivateIllusionModeA();
		void handleActivateExplosionModeA();


 		~AMode() = default;
		
	};
	
} // namespace eter
