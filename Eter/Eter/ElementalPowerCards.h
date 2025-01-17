#pragma once
#include <ostream>
#include "Board.h"
#include "Player.h"
#include "Game.h"
#include "Explosion.h"

namespace eter {

	 class elementalPowerCards {
	public:
		enum class powerAbility {
			controlledExplosion,
			destruction,
			flame,
			fire,
			ash,
			spark,
			squall,
			gale,
			hurricane,
			gust,
			mirage,
			storm,
			tide,
			mist,
			wave,
			whirlpool,
			blizzard,
			waterfall,
			support,
			earthQuake,
			crumble,
			border,
			avalanche,
			rock
		};

	private:
		powerAbility m_power = powerAbility::controlledExplosion;
		bool m_used = false;

	public:
		elementalPowerCards() = default;

		elementalPowerCards(powerAbility power) ;

		elementalPowerCards(const elementalPowerCards& other)
			: m_power(other.m_power), m_used(other.m_used) {
		}

		elementalPowerCards& operator=(const elementalPowerCards& other) {
			if (this != &other) {
				m_power = other.m_power;
				m_used = other.m_used;
			}
			return *this;
		}

		elementalPowerCards(elementalPowerCards&& other) noexcept
			: m_power(std::move(other.m_power)), m_used(std::move(other.m_used)) {

		}

		elementalPowerCards& operator=(elementalPowerCards&& other) noexcept {
			if (this != &other) {
				m_power = std::move(other.m_power);
				m_used = std::move(other.m_used);
			}
			return *this;
		}

		~elementalPowerCards() = default;

		void SetUsed(bool used);
		bool GetUsed() const;
		void SetAbility(powerAbility power);
		powerAbility GetAbility() const;
		void activate(Game* game, Player& player, Player& opponent, Board& board);

	private:
		void activateExplosion(Game* game);
		void activateDestruction(Player& player, Player& opponent, Board& board);
		void activateSquall(Player& opponent, Player& player, Board& board);
		void activateFire(Player& player, Player& opponent, Board& board);
		void activateASH(Player& player, Board& board);
		void activateSpark(Player& player, Player& opponent, Board& board);
		void activateEarthQuake(Player& player, Player& opponent, Board& board);
		void activateMist(Player& player, Board& board);
		void activateGale(Player& player, Player& opponent, Board& board);
		void activateGust(Board& board, Player& player, Player& opponent);
		void activateTide(Player& player, Player& opponent, Board& board);
		void activateWave(Board& board, Player& player,Player& opponent);
		void activateStorm(Board& board, Player& player, Player& opponent);
		void activateWaterfall(Board& board);
		void activateWhirlpool(Board& board, Player& player, Player& opponent);
		void activateFlame(Player& player, Player& opponent, Board& board);
		void activateHurricane(Player& player, Player& opponent, Board& board);
		void activateMirage(Board& board, Player& player);
		void activateBlizzard(Board& board, Player& player, Player& opponent);
		void activateSupport(Board& board, Player& player);
		void activateCrumble(Board& board, Player& player, Player& opponent);
		void activateRock(Board& board, Player& player);
		void activateAvalanche(Board& board, Player& player, Player& opponent);
		void activateBorder(Board& board, Player& player);
	    friend void swap(elementalPowerCards& first, elementalPowerCards& second) noexcept;
		friend std::ostream& operator<<(std::ostream& os, elementalPowerCards::powerAbility ability);
	};

}
