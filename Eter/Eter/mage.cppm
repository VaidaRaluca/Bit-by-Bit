//mage.cppm
#include "Board.h";
#include "Player.h";
export module mage;
import <optional>;
import <stack>;
import <unordered_map>;

namespace eter {
	export class Mage {
	public:
		enum class MagicAbility {
			removeOpponentCard,
			removeEntireLine,
			coverOpponentCard,
			createPit,
			moveOwnStack,
			extraEterCard,
			moveOpponentStack,
			shiftEdge
		};

	private:
		MagicAbility m_ability;
		bool m_used;

		static std::unordered_map<MagicAbility, int> abilityUsage;
		static std::string abilityToString(MagicAbility ability);

	public:
		Mage() = default;
		Mage(MagicAbility ability);

		//Rule of Five
		Mage(const Mage& other);             
		Mage& operator=(const Mage& other);   
		Mage(Mage&& other) noexcept;        
		Mage& operator=(Mage&& other) noexcept;		
		~Mage(); 
		void swap(Mage& other) noexcept;

		bool isUsed();
		MagicAbility GetAbility() const;


		void activate(Player& player, Player& opponent, Board& board);

		static void displayAbilityUsage();

	private:

		static void removeOpponentCard(Player& player, Player& opponent, Board& board);
		static void removeEntireRow(Player& player, Board& board);
		static void removeEntireColumn(Player& player, Board& board);
		static void removeEntireLine(Player& player, Board& board);
		static void coverOpponentCard(Player& player, Player& opponent, Board& board);
		static void createPit(Board& board);
		static void addExtraEterCard(Player& player, Board& board);
		static void moveOwnStack(Player& player, Board& board);
		static void moveOpponentStack(Player& opponent, Board& board);
		static void shiftEdge(Board& board);
		static void shiftRowToEdge(Board& board);
		static void shiftColumnToEdge(Board& board);

		bool isAbilityUsed() const;
		void displayAbilityDescription() const;
		bool confirmAbilityActivation() const;
		void cancelAbilityActivation() const;
		bool executeAbility(Player& player, Player& opponent, Board& board);
		void updateAbilityUsage();
		void notifyAbilityActivated() const;

	};
}
