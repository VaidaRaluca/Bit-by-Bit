//mage.cppm
export module mage;
import board;
import player;

namespace eter {
	export class Mage {
	public:
		//abilitati magice pentru vrajitori
		enum class MagicAbility {
			removeOponnentCard,
			removeEntireRow,
			coverOponnetCard,
			createPit,
			moveOwnStack,
			extraEterCard,
			moveOponnentStack,
			shiftRowToEdge
		};

	private:
		MagicAbility m_ability;
		bool m_used;

	public:
		Mage() = default;
		Mage(MagicAbility ability);

		// daca abilitatea respectiva a mai fost folosita
		bool isUsed();
		MagicAbility GetAbility() const;

		// activare abilitate
		void activate(Player& player, Player& oponnent, Board& board);

	private:
		//metodele pentru activarea fiecarei abilitati
		void removeOponnentCard(Player& player, Player& oponnent, Board& board);
		void removeEntireRow(Player& player, Board& board);
		void coverOponnentCard(Player& player, Player& oponnent, Board& board);
		void createPit(Board& board);
		void addExtraEterCard(Player& player);
		void moveOwnStack(Player& player, Board& board);
		void moveOponnentStack(Player& oponnent, Board& board);
		void shiftRowToEdge(Board& board);
	};
}
