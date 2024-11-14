module board;
using eter::Card;
using eter::Board;
const std::string_view kEmpyBoardCell{ "____" };

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

bool eter::Board::isVerticalLine(std::optional<std::string>& lineColor) const
{
	auto areCellsIdentical = [this](size_t row1, size_t row2, size_t col) {
		return m_grid[row1][col].has_value() && m_grid[row2][col].has_value() &&
			m_grid[row1][col].value().top() == m_grid[row2][col].value().top();
		};
	for (size_t col = 0; col < m_cols; ++col) {
		std::optional<std::string> currentColor;
		bool isLine = true;
		for (size_t row = 1; row < m_rows; ++row) {
			if (!areCellsIdentical(row, row - 1, col)) {
				isLine = false;
				break;
			}
			if (!currentColor && m_grid[row][col].has_value())
				currentColor = m_grid[row][col].value().top().GetColor();
			else if (m_grid[row][col].value().top().GetColor() != currentColor) {
				isLine = false;
				break;
			}
		}
		if (isLine && currentColor) {
			lineColor = currentColor;
			return true;
		}
	}
	return false;
}


bool eter::Board::isPrimaryDiagonalLine(std::optional<std::string>& lineColor) const {
	auto areCellsIdentical = [this](size_t row1, size_t row2) {
		return m_grid[row1][row1].has_value() && m_grid[row2][row2].has_value() &&
			m_grid[row1][row1].value().top() == m_grid[row2][row2].value().top();
		};
	std::optional<std::string> primaryDiagonalColor;
	bool isLine = true;
	for (size_t row = 1; row < m_rows; ++row) {
		if (!areCellsIdentical(row, row - 1)) {
			isLine = false;
			break;
		}
		if (!primaryDiagonalColor && m_grid[row][row].has_value())
			primaryDiagonalColor = m_grid[row][row].value().top().GetColor();
		else if (m_grid[row][row].value().top().GetColor() != primaryDiagonalColor) {
			isLine = false;
			break;
		}
	}
	if (isLine && primaryDiagonalColor) {
		lineColor = primaryDiagonalColor;
		return true;
	}
	return false;
}


bool eter::Board::isSecondaryDiagonalLine(std::optional<std::string>& lineColor) const {
	auto areCellsIdentical = [this](size_t row1, size_t row2) {
		return m_grid[row1][m_cols - row1 - 1].has_value() && m_grid[row2][m_cols - row2 - 1].has_value() &&
			m_grid[row1][m_cols - row1 - 1].value().top() == m_grid[row2][m_cols - row2 - 1].value().top();
		};
	std::optional<std::string> secondaryDiagonalColor;
	bool isLine = true;
	for (size_t row = 1; row < m_rows; ++row) {
		if (!areCellsIdentical(row, row - 1)) {
			isLine = false;
			break;
		}
		if (!secondaryDiagonalColor && m_grid[row][m_cols - row - 1].has_value())
			secondaryDiagonalColor = m_grid[row][m_cols - row - 1].value().top().GetColor();
		else if (m_grid[row][m_cols - row - 1].value().top().GetColor() != secondaryDiagonalColor) {
			isLine = false;
			break;
		}
	}
	if (isLine && secondaryDiagonalColor) {
		lineColor = secondaryDiagonalColor;
		return true;
	}
	return false;
}

bool eter::Board::isHorizontalLine(std::optional<std::string>& lineColor) const
{
	auto areCellsIdentical = [this](size_t col1, size_t col2, size_t row) {
		return m_grid[row][col1].has_value() && m_grid[row][col2].has_value() &&
			m_grid[row][col1].value().top() == m_grid[row][col2].value().top();
		};
	for (size_t row = 0; row < m_rows; ++row) {
		std::optional<std::string> currentColor;
		bool isLine = true;
		for (size_t col = 1; col < m_cols; ++col) {
			if (!areCellsIdentical(col, col - 1, row)) {
				isLine = false;
				break;
			}
			if (!currentColor && m_grid[row][col].has_value())
				currentColor = m_grid[row][col].value().top().GetColor();
			else if (m_grid[row][col].value().top().GetColor() != currentColor) {
				isLine = false;
				break;
			}
		}
		if (isLine && currentColor) {
			lineColor = currentColor;
			return true;
		}
	}
	return false;
}

const std::string& eter::Board::findWinner()
{
	std::optional<std::string> winnerColor;
	if (isHorizontalLine(winnerColor))
	{
		return winnerColor.value();
	}
	if (isVerticalLine(winnerColor))
	{
		return winnerColor.value();
	}
	if (isPrimaryDiagonalLine(winnerColor))
	{
		return winnerColor.value();
	}
	if (isSecondaryDiagonalLine(winnerColor))
	{
		return winnerColor.value();
	}
	return "";
}

bool eter::Board::isBoardFull()
{
	for (uint8_t row = 0; row < m_rows; ++row) 
		for(uint8_t col=0;col<m_cols;++col)
			if (!m_grid[row][col].has_value())
				return false;
	return true;
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