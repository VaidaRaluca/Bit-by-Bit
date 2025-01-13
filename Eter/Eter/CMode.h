#pragma once
#include <string>
#include <vector>
#include "ElementalPowerCards.h"
#include "Player.h"
#include "Card.h"
#include "AMode.h"
#include "Game.h"

namespace eter {
	 class CMode : virtual public AMode {
	private:
		std::vector<elementalPowerCards>m_power{ elementalPowerCards{elementalPowerCards::powerAbility::controlledExplosion},
		elementalPowerCards{elementalPowerCards::powerAbility::destruction},
		elementalPowerCards{elementalPowerCards::powerAbility::flame},
		elementalPowerCards{elementalPowerCards::powerAbility::fire},
		elementalPowerCards{elementalPowerCards::powerAbility::ash},
		elementalPowerCards{elementalPowerCards::powerAbility::spark},
		elementalPowerCards{elementalPowerCards::powerAbility::squall},
		elementalPowerCards{elementalPowerCards::powerAbility::gale},
		elementalPowerCards{elementalPowerCards::powerAbility::hurricane},
		elementalPowerCards{elementalPowerCards::powerAbility::gust},
		elementalPowerCards{elementalPowerCards::powerAbility::mirage},
		elementalPowerCards{elementalPowerCards::powerAbility::storm},
		elementalPowerCards{elementalPowerCards::powerAbility::tide},
		elementalPowerCards{elementalPowerCards::powerAbility::mist},
		elementalPowerCards{elementalPowerCards::powerAbility::wave},
		elementalPowerCards{elementalPowerCards::powerAbility::whirlpool},
		elementalPowerCards{elementalPowerCards::powerAbility::blizzard},
		elementalPowerCards{elementalPowerCards::powerAbility::waterfall},
		elementalPowerCards{elementalPowerCards::powerAbility::support},
		elementalPowerCards{elementalPowerCards::powerAbility::earthQuake},
		elementalPowerCards{elementalPowerCards::powerAbility::crumble},
		elementalPowerCards{elementalPowerCards::powerAbility::border},
		elementalPowerCards{elementalPowerCards::powerAbility::avalanche},
		elementalPowerCards{elementalPowerCards::powerAbility::rock} };
		elementalPowerCards m_power1, m_power2;
		/*Game* m_game;
		Player m_player;*/

	public:
		CMode() = default;
		explicit CMode(Game* game);
		uint8_t GetRoundsForWin() const override;
		uint8_t GetRounds() const override;
		void applyModeRules() override;
		void generatePower();
		void assignCardsInHand() override;
		void startRound() override;
		void startMatch() override;
		void handleOption() override;
		virtual ~CMode() = default;
	};
}