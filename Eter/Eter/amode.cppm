#include<cstdint>
export module amode;
import game;
import <memory>;

namespace eter {
	export class AMode {
	protected:

		Game* m_game;
	
 
	public:
		AMode() = default;
		virtual uint8_t getRoundsForWin() const;
		virtual uint8_t getRounds() const;
		AMode(Game* game);
		virtual void assignCardsInHand();
		virtual void startMatch();
		virtual void handleOption();  // afiseaza optiunile utilizatorului
		virtual void startRound();  //porneste runda
		virtual void applyModeRules(); // aplica toate regulile jocului

 		virtual ~AMode() = default;
		
	};
	
} 
