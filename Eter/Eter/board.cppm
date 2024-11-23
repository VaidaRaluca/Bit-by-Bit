#include <cstdint>
export module board;
export import card; 
import <vector>;
import <optional>;
import <stack>;
import <utility>;
import <string>;
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

		//Getters
		uint8_t GetRows() const;
		uint8_t GetCols() const;
		const std::vector<std::vector<std::optional<std::stack<Card>>>>& GetGrid() const;

		std::optional<std::stack<Card>>& operator[](std::pair<int, int> pos);
		const std::optional<std::stack<Card>>& operator[](std::pair<int, int> pos) const;

		bool isValidPosition(int x, int y) const;
		bool isAdjacentToOccupiedSpace(int x, int y)const;
		bool canPlaceCard(int x, int y, const Card& card)const;
		bool placeCard(int x, int y, const Card& card);

		bool isVerticalLine(const std::string& lineColor) const;
		bool isPrimaryDiagonalLine(const std::string& lineColor) const;
		bool isSecondaryDiagonalLine(const std::string& lineColor) const;
		bool isHorizontalLine(const std::string& lineColor) const;

		bool isEmptyCell(int x, int y);
		std::string findWinner();
		const std::string& findWinnerByScore();
		bool isBoardFull();
		void clear();
		~Board()=default;
	};
	export std::ostream& operator<<(std::ostream& os, const Board& board);
}