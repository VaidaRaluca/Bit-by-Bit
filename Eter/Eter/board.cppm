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
		size_t m_rows = { 7 }, m_cols = { 7 }; 
		size_t m_indexMax;
		size_t m_dimMax;
		size_t m_indexLineMin, m_indexColMin, m_indexLineMax, m_indexColMax;
	public:
		//Rule of 5 
		Board();
		Board(std::vector<std::vector<std::optional<std::stack<Card>>>>grid, uint8_t rows, uint8_t cols);
		Board(const Board& other); //constructor de copiere
		Board& operator=(const Board& other);
		Board(Board&& other) noexcept;
		Board& operator=(Board&& other) noexcept;
		~Board() = default;

		//Getters
		uint8_t GetRows() const;
		uint8_t GetCols() const;
		const std::vector<std::vector<std::optional<std::stack<Card>>>>& GetGrid() const;
		const uint8_t GetDimMax() const;
		std::optional<std::stack<Card>>& operator[](std::pair<int, int> pos);
		const std::optional<std::stack<Card>>& operator[](std::pair<int, int> pos) const;

		void SetDimMax(uint8_t dim);

		bool isValidPosition(size_t x, size_t y) const;
		bool isAdjacentToOccupiedSpace(size_t x, size_t y)const;
		bool canPlaceCard(size_t x, size_t y, const Card& card);
		bool placeCard(size_t x, size_t y, const Card& card);

		bool isVerticalLine(const std::string& lineColor) const;
		bool isPrimaryDiagonalLine(const std::string& lineColor) const;
		bool isSecondaryDiagonalLine(const std::string& lineColor) const;
		bool isHorizontalLine(const std::string& lineColor) const;

		bool isEmptyCell(size_t x, size_t y);
		std::string findWinner();
		const std::string& findWinnerByScore();
		bool isBoardFull();
		void clear();
		void swap(Board& other) noexcept;
	};
	export std::ostream& operator<<(std::ostream& os, const Board& board);
	export void swap(Board& first, Board& second) noexcept;
}