#include <optional>
#include <stack>
#include <unordered_map>
import board;
import player;
namespace eter {
	class Mage {
	public:
		//abilitati magice pentru vrajitori
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
		Mage(const Mage& other);    //constructor de copiere            
		Mage& operator=(const Mage& other);    // operator de atribuire prin copiere
		Mage(Mage&& other) noexcept;           //constructor de mutare
		Mage& operator=(Mage&& other) noexcept;		//operator de atribuire prin mutare
		~Mage(); //Destructorul
		void swap(Mage& other) noexcept;

		// daca abilitatea respectiva a mai fost folosita
		bool isUsed();
		MagicAbility GetAbility() const;

		// activare abilitate
		void activate(Player& player, Player& opponent, Board& board);

		static void displayAbilityUsage();

	private:
		//metodele pentru activarea fiecarei abilitati
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

		//Cautarea unei carti pe tabla
		std::optional<std::pair<size_t, size_t>> findCardPosition(const Card& card, Board& board);
		void removeCardFromBoard(std::optional<std::stack<Card>>& stack);
		bool isPositionValidForMove(const std::pair<int, int>& from, const std::pair<int, int>& to, Board& board);
		void moveStack(const std::pair<int, int>& from, const std::pair<int, int>& to, Board& board);

		//Functii ajutatoare
		bool isAbilityUsed() const;
		void displayAbilityDescription() const;
		bool confirmAbilityActivation() const;
		void cancelAbilityActivation() const;
		bool executeAbility(Player& player, Player& opponent, Board& board);
		void updateAbilityUsage();
		void notifyAbilityActivated() const;

	};
}
#pragma once
