module board;
using namespace eter;
std::string_view kEmpyBoardCell{ "____" };

Board::Board(std::vector<std::vector<std::optional<std::stack<Card>>>>grid, uint8_t rows, uint8_t cols)
	: m_grid{ rows, std::vector<std::optional<std::stack<Card>>>(cols, std::nullopt) }
	, m_rows{ rows }
	, m_cols{ cols }
{}
Board::Board(const Board& other)
	: m_grid{ other.m_grid }
	, m_rows{ other.m_rows }
	, m_cols{ other.m_cols }
{}

Board& Board::operator=(const Board& other) {
	if (this != &other) {
		m_grid = other.m_grid;
		m_rows = other.m_rows;
		m_cols = other.m_cols;
	}
	return *this;
}

uint8_t Board::GetRows() const
{
	return m_rows;
}

uint8_t Board::GetCols() const
{
	return m_cols;
}

const std::vector<std::vector<std::optional<std::stack<Card>>>>& Board::GetGrid() const
{
	return m_grid;
}

bool Board::isValidPosition(int x, int y) const
{

	return x >= 0 && x < m_rows && y >= 0 && y < m_cols;
}

//std::ostream& operator<<(std::ostream& os, const Board& baord)
//{
//	
//}