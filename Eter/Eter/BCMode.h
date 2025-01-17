#pragma once
#include <cstdint>
#include <iostream>
#include <vector>
#include "Game.h"
#include "BMode.h"
#include "CMode.h"

import mage;


namespace eter {
	 class BCMode : public BMode, public CMode {
	private:
	public:
		BCMode() = default;
		explicit BCMode(Game* game);
		uint8_t GetRoundsForWin() const override;
		uint8_t GetRounds() const override;
		void assignCardsInHand() override; 
		void generateMageAndPower();  
		void startMatch() override; 
		void startRound() override; 
		void handleOption() override; 
		void applyModeRules() override; 

		virtual ~BCMode() = default;

	};

}