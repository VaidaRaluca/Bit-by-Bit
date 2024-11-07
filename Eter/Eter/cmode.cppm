export module cmode;
import gamemods;
import elementalpowercards;
import player;
import <vector>;
namespace eter {
	export class CMode : public GameMods {
	private:
		std::vector<ElementalPowerCards>m_power{ ElementalPowerCards(ElementalPowerCards::PowerAbility::ControlledExplosion),
		ElementalPowerCards(ElementalPowerCards::PowerAbility::Destruction),
		ElementalPowerCards(ElementalPowerCards::PowerAbility::Flame),
		ElementalPowerCards(ElementalPowerCards::PowerAbility::Fire),
		ElementalPowerCards(ElementalPowerCards::PowerAbility::ASH),
		ElementalPowerCards(ElementalPowerCards::PowerAbility::Spark),
		ElementalPowerCards(ElementalPowerCards::PowerAbility::Squall),
		ElementalPowerCards(ElementalPowerCards::PowerAbility::Gale),
		ElementalPowerCards(ElementalPowerCards::PowerAbility::Hurricane),
		ElementalPowerCards(ElementalPowerCards::PowerAbility::Gust),
		ElementalPowerCards(ElementalPowerCards::PowerAbility::Mirage),
		ElementalPowerCards(ElementalPowerCards::PowerAbility::Storm),
		ElementalPowerCards(ElementalPowerCards::PowerAbility::Tide),
		ElementalPowerCards(ElementalPowerCards::PowerAbility::Mist),
		ElementalPowerCards(ElementalPowerCards::PowerAbility::Wave),
		ElementalPowerCards(ElementalPowerCards::PowerAbility::Whirlpool),
		ElementalPowerCards(ElementalPowerCards::PowerAbility::Blizzard),
		ElementalPowerCards(ElementalPowerCards::PowerAbility::Waterfall),
		ElementalPowerCards(ElementalPowerCards::PowerAbility::Support),
		ElementalPowerCards(ElementalPowerCards::PowerAbility::EarthQuake),
		ElementalPowerCards(ElementalPowerCards::PowerAbility::Crumble),
		ElementalPowerCards(ElementalPowerCards::PowerAbility::Border),
		ElementalPowerCards(ElementalPowerCards::PowerAbility::Avalanche),
		ElementalPowerCards(ElementalPowerCards::PowerAbility::Rock)};
		ElementalPowerCards m_power1Player1,m_power2Player1;
		ElementalPowerCards m_power1Player2,m_power2Player2;
	public:
		CMode();
		void applyModeRules();
		void generatePower();
		~CMode() = default;
	};
}