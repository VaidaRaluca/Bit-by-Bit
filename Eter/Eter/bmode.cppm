#include<cstdint>
export module bmode;

import game;
import <string>;
import mage;
import player;
import board;
import card;
import<vector>;

namespace eter {
	export class BMode {
	private:
		std::vector<Mage> m_mages{ Mage(Mage::MagicAbility::removeOponnentCard),
		Mage(Mage::MagicAbility::removeEntireRow),
		Mage(Mage::MagicAbility::coverOponnetCard),
		Mage(Mage::MagicAbility::createPit),
		Mage(Mage::MagicAbility::moveOwnStack),
		Mage(Mage::MagicAbility::extraEterCard),
		Mage(Mage::MagicAbility::moveOponnentStack),
		Mage(Mage::MagicAbility::shiftRowToEdge) };
		Mage m_magePlayer1;
		Mage m_magePlayer2;
		Game* m_game;
		const uint8_t knrRoundsForWin=3;
	public:
		BMode()=default;
		BMode(Game* game);
		void assignCardsInHand(); //artibuie cate un set de carti pentru fiecare player
		void generateMage();  // genereaza cate un vrajitor pentru fiecare player
		void startMatch();   // porneste meciul
		void startRound();  //porneste runda
		void handleOption();  // afiseaza optiunile utilizatorului
		void applyModeRules(); // aplica toate regulile jocului

	};

}