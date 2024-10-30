#include <cstdint>
export module board;
import <vector>;
import <optional>;
import card; 
namespace eter {
	export class Board{
	private:
		std::vector<std::vector<std::optional<Card>>>m_grid;
		uint8_t m_rows, m_cols;
	public:
		void drawBoard();//afisam grid
		Board();
		Board(std::vector<std::vector<std::optional<Card>>>grid, uint8_t rows, uint8_t cols);
		~Board();
	};
}