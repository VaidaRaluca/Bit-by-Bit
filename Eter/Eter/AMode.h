#pragma once
#include <cstdint>
#include <memory>
#include "Game.h"


namespace eter {
	class AMode {
	protected:
		Game* m_game;
	public:
		AMode() = default;
		virtual uint8_t GetRoundsForWin() const;
		virtual uint8_t GetRounds() const;
		AMode(Game* game);
		virtual void assignCardsInHand();
		virtual void startMatch();
		virtual void handleOption();  
		virtual void startRound(); 
		virtual void applyModeRules();

		virtual ~AMode() = default;

	};

}
