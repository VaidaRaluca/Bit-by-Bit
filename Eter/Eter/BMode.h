#pragma once
#include<cstdint>
#include <vector>;
#include "Game.h"
#include "AMode.h"
import mage;

namespace eter {
	 class BMode : virtual public AMode {
	private:
		std::vector<Mage> m_mages{ /*Mage{Mage::MagicAbility::removeOpponentCard},
		Mage{Mage::MagicAbility::removeEntireLine},
		Mage{Mage::MagicAbility::coverOpponentCard},
		Mage{Mage::MagicAbility::createPit},
		Mage{Mage::MagicAbility::moveOwnStack},
		Mage{Mage::MagicAbility::extraEterCard},*/
		Mage{Mage::MagicAbility::moveOpponentStack},
		Mage{Mage::MagicAbility::shiftEdge} };

		//Game* m_game;
		Mage m_magePlayer1;
		Mage m_magePlayer2;

	public:
		BMode() = default;
		explicit BMode(Game* game);
		uint8_t getRoundsForWin() const override;
		uint8_t getRounds() const override;
		void assignCardsInHand() override; //artibuie cate un set de carti pentru fiecare player
		void generateMage();  // genereaza cate un vrajitor pentru fiecare player
		void startMatch() override;   // porneste meciul
		void startRound() override;  //porneste runda
		void handleOption() override;  // afiseaza optiunile utilizatorului
		void applyModeRules() override; // aplica toate regulile jocului

		//Made them public just for testing, i will make getters for them later

		virtual ~BMode() = default;

		Mage GetMageForPlayer1() const;
		Mage GetMageForPlayer2() const;

	};

}