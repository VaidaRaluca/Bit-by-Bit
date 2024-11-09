export module elementalpowercards;
import board;
import player;

namespace eter {

	export class ElementalPowerCards {
	public:
		enum class PowerAbility {
			ControlledExplosion,
			Destruction,
			Flame,
			Fire,
			ASH,
			Spark,
			Squall,
			Gale,
			Hurricane,
			Gust,
			Mirage,
			Storm,
			Tide,
			Mist,
			Wave,
			Whirlpool,
			Blizzard,
			Waterfall,
			Support,
			EarthQuake,
			Crumble,
			Border,
			Avalanche,
			Rock
	};
	private:
		PowerAbility m_power;
		bool m_used;

	public:
		ElementalPowerCards()=default;
		ElementalPowerCards(PowerAbility power);
		void setUsed(bool used);
		bool getUsed() const;
		void setAbility(PowerAbility power);
		PowerAbility getAbility() const;
		void activate(Player& player, Player& opponent, Board& board);
		~ElementalPowerCards()=default;

	private:
		void activateDestruction(Player& player, Player& opponent, Board& board);
		void activateSquall(Player& opponent);
	};
}