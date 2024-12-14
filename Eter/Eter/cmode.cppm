export module cmode;
import <string>;
import elementalpowercards;
import player;
import game;
import card;
import amode;
import <vector>;
namespace eter {
	export class CMode : virtual public AMode {
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
		uint8_t getRoundsForWin() const override;
		uint8_t getRounds() const override;
		void applyModeRules() override;
		void generatePower();
		void assignCardsInHand() override;
		void startRound() override;
		void startMatch() override;
		void handleOption() override;
		virtual ~CMode() = default;
	};
}