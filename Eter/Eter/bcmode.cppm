#include<cstdint>;
export module bcmode;
import <iostream>;
import game;
import mage;
import bmode;
import cmode;
import<vector>;

namespace eter {
	export class BCMode : public BMode, public CMode {
	private:
	//	std::vector<Mage> m_mages{ Mage{Mage::MagicAbility::removeOpponentCard},
	//	Mage{Mage::MagicAbility::removeEntireLine},
	//	Mage{Mage::MagicAbility::coverOpponentCard},
	//	Mage{Mage::MagicAbility::createPit},
	//	Mage{Mage::MagicAbility::moveOwnStack},
	//	Mage{Mage::MagicAbility::extraEterCard},
	//	Mage{Mage::MagicAbility::moveOpponentStack},
	//	Mage{Mage::MagicAbility::shiftEdge} };
	//	Mage m_magePlayer1;
	//	Mage m_magePlayer2;
	//	//Game* m_game;
	public:
		BCMode() = default;
		explicit BCMode(Game* game);
		uint8_t getRoundsForWin() const override;
		uint8_t getRounds() const override;
		void assignCardsInHand() override; //artibuie cate un set de carti pentru fiecare player
		void generateMageAndPower();  // genereaza cate un vrajitor pentru fiecare player
		void startMatch() override;   // porneste meciul
		void startRound() override;  //porneste runda
		void handleOption() override;  // afiseaza optiunile utilizatorului
		void applyModeRules() override; // aplica toate regulile jocului

		virtual ~BCMode() = default;

	};

}