export module bmode;

import game;
import gamemods;
import mage;
import player;
import board;
import card;
import<vector>;

namespace eter {
	export class BMode : public GameMods {
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
	public:
		BMode();
		void applyModeRules(); // override 
		void assignCardsInHand(); //artibuie cate un set de carti pentru fiecare player
		void generateMage();  // genereaza cate un vrajitor pentru fiecare player

	};
}