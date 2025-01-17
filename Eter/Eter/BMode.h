#pragma once
#include<cstdint>
#include <vector>;
#include "Game.h"
#include "AMode.h"
import mage;

namespace eter {
	 class BMode : virtual public AMode {
	private:
		std::vector<Mage> m_mages{ Mage{Mage::MagicAbility::removeOpponentCard},
		Mage{Mage::MagicAbility::removeEntireLine},
		Mage{Mage::MagicAbility::coverOpponentCard},
		Mage{Mage::MagicAbility::createPit},
		Mage{Mage::MagicAbility::moveOwnStack},
		Mage{Mage::MagicAbility::extraEterCard},
		Mage{Mage::MagicAbility::moveOpponentStack},
		Mage{Mage::MagicAbility::shiftEdge} };

		Mage m_magePlayer1;
		Mage m_magePlayer2;

	public:
		BMode() = default;
		explicit BMode(Game* game);
		uint8_t GetRoundsForWin() const override;
		uint8_t GetRounds() const override;
		void assignCardsInHand() override; 
		void generateMage(); 
		void startMatch() override;  
		void startRound() override;  
		void handleOption() override;  
		void applyModeRules() override;


		virtual ~BMode() = default;

		Mage GetMageForPlayer1() const;
		Mage GetMageForPlayer2() const;

	};

}