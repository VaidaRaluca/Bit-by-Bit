module board;
using eter::Card;
using eter::Board;
const std::string_view kEmpyBoardCell{ "____" };
import <iostream>;

Board::Board(std::vector<std::vector<std::optional<std::stack<Card>>>>grid, uint8_t rows, uint8_t cols)
	: m_grid{ std::move(grid) }
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
	return x >= 0 && x < (int)m_rows && y >= 0 && y < (int)m_cols;
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
	bool isBoardEmpty = true;
	for (const auto& row : m_grid) {
		for (const auto& cell : row) {
			if (cell.has_value()) {
				isBoardEmpty = false;
				break;
			}
		}
	}
	return isBoardEmpty || isAdjacentToOccupiedSpace(x, y);
}


bool eter::Board::placeCard(int x, int y, const Card& card)
{
	if (!canPlaceCard(x, y, card))

	{
		std::cout << "Placement is not allowed at (" << x << ", " << y << "). It's not a valid position.\n";
		return false;
	}

	if (!m_grid[x][y].has_value())
	{
		m_grid[x][y] = std::stack<Card>();
	}

	m_grid[x][y]->push(card);
	std::cout << "The card with value " << static_cast<int>(card.GetValue())
		<< " has been placed at (" << x << ", " << y << ").\n";
	return true;
}

bool eter::Board::isVerticalLine(const std::string& lineColor) const
{
	for (size_t col = 0; col < m_cols; ++col) {
		bool isLine = true;
		for (size_t row = 0; row < m_rows; ++row)
			if (!m_grid[row][col] ||
				m_grid[row][col]->top().GetColor() != lineColor) {
				isLine = false;
				break;
			}

		if (isLine)
			return true;
	}
	return false;
}



bool eter::Board::isPrimaryDiagonalLine(const std::string& lineColor) const {
	if (m_rows != m_cols) 
		return false;
	for (size_t i = 0; i < m_rows; ++i) 
		if (!m_grid[i][i] || m_grid[i][i]->top().GetColor() != lineColor) 
			return false; 
	return true; 
}


bool eter::Board::isSecondaryDiagonalLine(const std::string& lineColor) const {
	if (m_rows != m_cols)
		return false;
	for (size_t i = 0; i < m_rows; ++i)
		if (!m_grid[i][m_rows-1-i] || m_grid[i][m_rows-1-i]->top().GetColor() != lineColor)
			return false;
	return true;
}

bool eter::Board::isHorizontalLine(const std::string& lineColor) const
{
	for (size_t row = 0; row < m_rows; ++row) {
		bool isLine = true;
		for (size_t col = 0; col < m_cols; ++col)
			if (!m_grid[row][col] ||
				m_grid[row][col]->top().GetColor() != lineColor) {
				isLine = false;
				break;
			}

		if (isLine)
			return true;
	}
	return false;
}

std::string eter::Board::findWinner()
{
	if (isHorizontalLine("red") || isVerticalLine("red") || isPrimaryDiagonalLine("red") || isSecondaryDiagonalLine("red")) 
		return "red";
	else if (isHorizontalLine("blue") || isVerticalLine("blue") || isPrimaryDiagonalLine("blue") || isSecondaryDiagonalLine("blue"))
		return "blue";
	return std::string{ "No winner yet" };
}

const std::string& eter::Board::findWinnerByScore()
{
	uint16_t score1{ 0 };
	uint16_t score2{ 0 };
	for (size_t line = 0; line < m_grid.size(); ++line) {
		for (size_t col = 0; col < m_grid[line].size(); ++col) {
			if (m_grid[line][col].has_value()) {
				if (m_grid[line][col].value().top().GetColor() == "blue")
					score1 += m_grid[line][col].value().top().GetValue();
				if (m_grid[line][col].value().top().GetColor() == "red")
					score2 += m_grid[line][col].value().top().GetValue();
			}
		}
	}
	if (score1 > score2)
		return"blue";
	if (score2 > score1)
		return "red";
	return " ";
}

bool eter::Board::isBoardFull()
{
	for (uint8_t row = 0; row < m_rows; ++row)
		for (uint8_t col = 0; col < m_cols; ++col)
			if (!m_grid[row][col].has_value())
				return false;
	return true;
}

void eter::Board::clear()
{
	for (auto& row : m_grid) {
		for (auto& cell : row) {
			cell.reset();  // `reset` resetează fiecare celulă la starea inițială
		}
	}
}

bool Board::isEmptyCell(int x, int y)
{
	for (uint8_t rows = 0; rows < m_rows; rows++)
		for (uint8_t cols = 0; cols < m_cols; cols++)
		{
			if (isValidPosition(rows, cols) && !m_grid[rows][cols].has_value())
				return true;
		}
	return false;
}


std::ostream& eter::operator<<(std::ostream& os, const Board& board)
{
	for (uint8_t line = 0; line < board.GetRows(); ++line)
	{
		for (uint8_t column = 0; column < board.GetCols(); ++column)
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