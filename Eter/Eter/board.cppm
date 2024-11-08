#include <cstdint>
export module board;
import <vector>;
import <optional>;
import <stack>;
import <utility>;
export import card; 
namespace eter {
	export class Board {
	private:
		std::vector<std::vector<std::optional<std::stack<Card>>>>m_grid;
		size_t m_rows = { 7 }, m_cols = { 7 }; // size_t
	public:
		Board()=default;
		Board(std::vector<std::vector<std::optional<std::stack<Card>>>>grid, uint8_t rows, uint8_t cols);
		Board(const Board& other); //constructor de copiere
		Board& operator=(const Board& other);

		//Getteri
		uint8_t GetRows() const;
		uint8_t GetCols() const;
		const std::vector<std::vector<std::optional<std::stack<Card>>>>& GetGrid() const;

		std::optional<std::stack<Card>>& operator[](std::pair<int, int> pos);
		const std::optional<std::stack<Card>>& operator[](std::pair<int, int> pos) const;

		bool isValidPosition(int x, int y) const;
		bool isAdjacentToOccupiedSpace(int x, int y)const;
		bool canPlaceCard(int x, int y, const Card& card)const;
		void placeCard(int x, int y, const Card& card);

		~Board()=default;

	};
	export std::ostream& operator<<(std::ostream& os, const Board& board);
}