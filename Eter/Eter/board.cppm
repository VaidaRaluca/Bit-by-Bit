#include <cstdint>
export module board;
import <vector>;
import <optional>;
import card; 
namespace eter {
	export class Board {
	private:
		std::vector<std::vector<std::optional<Card>>>m_grid;
		uint8_t m_rows=7, m_cols=7;
	public:
		Board()=default;
		Board(std::vector<std::vector<std::optional<Card>>>grid, uint8_t rows, uint8_t cols);
		Board(const Board& other); //constructor de copiere
		Board& operator=(const Board& other);

		bool isValidPosition(int x, int y) const;
		~Board()=default;

		void drawBoard();//afisam grid
	};
}