#include<cstdint>
export module amode;
import game;
import <memory>;

namespace eter {
	export class AMode {
	private:

		Game* m_game;
		const uint8_t knrRoundsForWin = 2; 		
 
	public:
		AMode() = default;
		 
		AMode(Game* game);
		void assignCardsInHandModeA();
		void startMatchModeA();
		void handleOptionModeA();  // afiseaza optiunile utilizatorului
		void startRoundModeA();  //porneste runda
		void applyModeRulesModeA(); // aplica toate regulile jocului
		void handleActivateExplosionModeA();

 		~AMode() = default;
		
	};
	
} 
