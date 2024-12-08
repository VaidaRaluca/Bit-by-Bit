export module elementalpowercards;
import board;
import player;
import std;
import <ostream>;

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
		void activateFire(Player& player, Player& opponent, Board& board);
		void activateASH(Player& player, Board& board);
		void activateSpark(Player& player, Board& board);
		void activateEarthQuake(Player& player, Player& opponent, Board& board);
		void activateMist(Player& player, Board& board);
		void activateGale(Player& player, Player& opponent, Board& board);
		void activateGust(Board& board);
		void activateTide(Board& board);
		void activateWave(Board& board, Player& player);
		void activateStorm(Board& board, Player& player, Player& opponent);
		void activateWaterfall(Board& board);
		void activateWhirlpool(Board& board, Player& player);
		void activateFlame(Player& player, Player& opponent, Board& board);
		void activateHurricane(Player& player, Player& opponent, Board& board);
		void activateMirage(Board& board, Player& player);
		void activateBlizzard(Board& board, Player& player, Player& opponent);
		void activateSupport(Board& board, Player& player);
		void activateCrumble(Board& board, Player& player);
		void activateRock(Board& board, Player& player);
		void activateAvalanche(Board& board);
 	};
	export std::ostream& operator<<(std::ostream& os, ElementalPowerCards::PowerAbility ability);
}