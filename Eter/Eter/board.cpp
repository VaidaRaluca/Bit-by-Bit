module board;
using eter::Card;
using eter::Board;
const std::string_view kEmpyBoardCell{ "____" };

Board::Board(std::vector<std::vector<std::optional<std::stack<Card>>>>grid, uint8_t rows, uint8_t cols)
	: m_grid{std::move(grid)}
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

std::optional<std::stack<Card>>& Board::operator[](std::pair<int, int> pos) {
	int x = pos.first;
	int y = pos.second;
	if (isValidPosition(x, y)) {
		return m_grid[x][y];
	}
	throw std::out_of_range("Invalid position");
}

const std::optional<std::stack<Card>>& Board::operator[](std::pair<int, int> pos) const {
	int x = pos.first;
	int y = pos.second;
	if (isValidPosition(x, y)) {
		return m_grid[x][y];
	}
	throw std::out_of_range("Invalid position");
}

bool Board::isValidPosition(int x, int y) const
{
	return x >= 0 && x < m_rows && y >= 0 && y < m_cols;
}

bool eter::Board::isAdjacentToOccupiedSpace(int x, int y)const
{
	static const std::vector<std::pair<int, int>> directions = {
		{-1, -1}, {-1, 0}, {-1, 1},
		{0, -1},          {0, 1},
		{1, -1}, {1, 0}, {1, 1}
	};

	for (const auto& [dx, dy] : directions) {
		int nx = x + dx;
		int ny = y + dy;
		if (isValidPosition(nx, ny) && m_grid[nx][ny].has_value() && !m_grid[nx][ny]->empty()) {
			return true; // cel putin  un spadiacent este ocupat
		}
	}
	return false; // niciun sp adiacent nu este ocupat
}


bool eter::Board::canPlaceCard(int x, int y, const Card& card) const
{
	if (!isValidPosition(x, y)) 
	{
		return false;
	}

	if (m_grid[x][y].has_value()) 
	{
		const auto& stack = m_grid[x][y].value();
		if (!stack.empty() && card.m_value > stack.top().m_value) {
			return true; 
		}
		return false;
	}
	return isAdjacentToOccupiedSpace(x, y);
}

void eter::Board::placeCard(int x, int y, const Card& card)
{
	if (!canPlaceCard(x, y, card)) 
	
	{
		std::cout << "Plasarea nu este permisa la (" << x << ", " << y << ").\n";
		return;
	}

	if (!m_grid[x][y].has_value()) 
	{
		m_grid[x][y] = std::stack<Card>();
	}

	m_grid[x][y]->push(card);
	std::cout << "Cartea cu valoarea " << card.m_value << " a fost plasata la (" << x << ", " << y << ").\n";
}
	

std::ostream& eter::operator<<(std::ostream& os, const Board& board)
{
	for (uint8_t line = 0;line < board.GetRows();++line)
	{
		for (uint8_t column = 0; column < board.GetCols();++column)
		{
			if (board.GetGrid()[line][column].has_value())
				os << board.GetGrid()[line][column].value().top() << " ";
			else
				os << kEmpyBoardCell << " ";
		}
		os << '\n';
	}
	return os;
}