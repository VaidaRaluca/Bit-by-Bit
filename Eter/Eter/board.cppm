#include <cstdint>
export module board;
import <vector>;
import <optional>;
import <stack>;
import card; 
namespace eter {
	export class Board {
	private:
		std::vector<std::vector<std::optional<std::stack<Card>>>>m_grid;
		uint8_t m_rows=7, m_cols=7;
	public:
		Board()=default;
		Board(std::vector<std::vector<std::optional<std::stack<Card>>>>grid, uint8_t rows, uint8_t cols);
		Board(const Board& other); //constructor de copiere
		Board& operator=(const Board& other);

		//Getteri
		uint8_t GetRows() const;
		uint8_t GetCols() const;
		const std::vector<std::vector<std::optional<std::stack<Card>>>>& GetGrid() const;

		bool isValidPosition(int x, int y) const;
		~Board()=default;

	};
	//export std::ostream& operator<<(std::ostream& os, const Board& baord);
}