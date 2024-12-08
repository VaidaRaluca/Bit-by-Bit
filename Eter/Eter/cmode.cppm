export module cmode;
import <string>;
import elementalpowercards;
import player;
import game;
import card;
import <vector>;
namespace eter {
	export class CMode  {
	private:
		std::vector<elementalPowerCards>m_power{ elementalPowerCards(elementalPowerCards::powerAbility::controlledExplosion),
		elementalPowerCards(elementalPowerCards::powerAbility::destruction),
		elementalPowerCards(elementalPowerCards::powerAbility::flame),
		elementalPowerCards(elementalPowerCards::powerAbility::fire),
		elementalPowerCards(elementalPowerCards::powerAbility::ash),
		elementalPowerCards(elementalPowerCards::powerAbility::spark),
		elementalPowerCards(elementalPowerCards::powerAbility::squall),
		elementalPowerCards(elementalPowerCards::powerAbility::gale),
		elementalPowerCards(elementalPowerCards::powerAbility::hurricane),
		elementalPowerCards(elementalPowerCards::powerAbility::gust),
		elementalPowerCards(elementalPowerCards::powerAbility::mirage),
		elementalPowerCards(elementalPowerCards::powerAbility::storm),
		elementalPowerCards(elementalPowerCards::powerAbility::tide),
		elementalPowerCards(elementalPowerCards::powerAbility::mist),
		elementalPowerCards(elementalPowerCards::powerAbility::wave),
		elementalPowerCards(elementalPowerCards::powerAbility::whirlpool),
		elementalPowerCards(elementalPowerCards::powerAbility::blizzard),
		elementalPowerCards(elementalPowerCards::powerAbility::waterfall),
		elementalPowerCards(elementalPowerCards::powerAbility::support),
		elementalPowerCards(elementalPowerCards::powerAbility::earthQuake),
		elementalPowerCards(elementalPowerCards::powerAbility::crumble),
		elementalPowerCards(elementalPowerCards::powerAbility::border),
		elementalPowerCards(elementalPowerCards::powerAbility::avalanche),
		elementalPowerCards(elementalPowerCards::powerAbility::rock)};
		elementalPowerCards m_power1Player1,m_power2Player1;
		elementalPowerCards m_power1Player2,m_power2Player2;
		Game* m_game;
		Player m_player;
		const uint8_t knrRoundsForWin = 3;
	public:
		CMode() =default;
		CMode(Game* game);
		void applyModeRules();
		void generatePower();
		void assignCardsInHand();
		void startRound();
		void startMatch();
		void handleOption();
		~CMode() = default;
	};
}