module board;
using eter::Card;
using eter::Board;
const std::string_view kEmpyBoardCell{ "____" };
import <iostream>;

eter::Board::Board()
	: m_dimMax{3},m_indexMax{7},
	m_indexLineMin{ 10 }, m_indexLineMax{ 10 },
	m_indexColMin{ 10 }, m_indexColMax{ 10 }
{
	// Inițializează grila
	m_grid.resize(m_indexMax, std::vector<std::optional<std::stack<Card>>>(m_indexMax));
}

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

Board::Board(Board&& other) noexcept
	: m_grid{std::move(other.m_grid)}, m_rows{ other.m_rows }, m_cols{ other.m_cols }
{
	other.m_rows = 0;
	other.m_cols = 0;
}

Board& Board::operator=(Board&& other) noexcept
{
	if (this == &other) return *this; 
	m_grid = std::move(other.m_grid);
	m_rows = other.m_rows;
	m_cols = other.m_cols;

	other.m_rows = 0;
	other.m_cols = 0;
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

const uint8_t eter::Board::GetDimMax() const
{
	return m_dimMax;
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

void eter::Board::SetDimMax(uint8_t dim)
{
	m_dimMax = dim;
}

bool Board::isValidPosition(size_t x, size_t y) const
{
	if (x < 0 || y < 0 || x >= m_rows || y >= m_cols) {
		return false;
	}

	// Dacă tabla este goală, orice poziție este validă
	if (m_indexLineMin == 10 && m_indexLineMax == 10 && m_indexColMin == 10 && m_indexColMax == 10) {
		return true;
	}

	size_t newLineMin = std::min(m_indexLineMin, x);
	size_t newLineMax = std::max(m_indexLineMax, x);
	size_t newColMin = std::min(m_indexColMin, y);
	size_t newColMax = std::max(m_indexColMax, y);

	return (newLineMax - newLineMin < m_dimMax) && (newColMax - newColMin < m_dimMax);

}

bool eter::Board::isAdjacentToOccupiedSpace(size_t x, size_t y)const
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


bool eter::Board::canPlaceCard(size_t x, size_t y, const Card& card)
{
	if (!isValidPosition(x, y))
	{
		return false;
	}

	if (m_grid[x][y].has_value())
	{
		const auto& stack = m_grid[x][y].value();
		if (!stack.empty() && card.GetColor() == stack.top().GetColor() && !stack.top().GetPosition()){ // cannot put card over your own illusion
			return false;
		}
		if (stack.top().GetValue() == static_cast<int>('/')) //pentru gropi///create pit in board
		{
			return false;
		}
		if (!stack.empty() && card.GetValue() > stack.top().GetValue()) {
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
	if (isBoardEmpty) {
		// Daca tabla este goala, initializeaza limitele
		m_indexLineMin = x;
		m_indexLineMax = x;
		m_indexColMin = y;
		m_indexColMax = y;
	}

	return isBoardEmpty || isAdjacentToOccupiedSpace(x, y);
}


bool eter::Board::placeCard(size_t x, size_t y, const Card& card)
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

	// Daca s-a inserat o carte actualizez indecsi
	m_indexLineMin = std::min(m_indexLineMin, x);
	m_indexLineMax = std::max(m_indexLineMax, x);
	m_indexColMin = std::min(m_indexColMin, y);
	m_indexColMax = std::max(m_indexColMax, y);

	std::cout << "The card with value " << static_cast<int>(card.GetValue())
		<< " has been placed at (" << x << ", " << y << ").\n";
	return true;
}

bool eter::Board::isVerticalLine(const std::string& lineColor) const {
	for (size_t col = m_indexColMin; col <= m_indexColMax; ++col) {
		size_t consecutiveCount = 0;
		for (size_t row = m_indexLineMin; row <= m_indexLineMax; ++row) {
			if (m_grid[row][col].has_value() && m_grid[row][col]->top().GetColor() == lineColor) {
				++consecutiveCount;
			}
			else {
				consecutiveCount = 0;
			}
			if (consecutiveCount >= m_dimMax) {
				return true;
			}
		}
	}
	return false;
}

bool eter::Board::isPrimaryDiagonalLine(const std::string& lineColor) const {
	if ((m_indexLineMax - m_indexLineMin) != (m_indexColMax - m_indexColMin)) {
		return false;
	}

	size_t consecutiveCount = 0;
	for (size_t i = 0; i <= m_indexLineMax - m_indexLineMin; ++i) {
		size_t row = m_indexLineMin + i;
		size_t col = m_indexColMin + i;

		if (m_grid[row][col].has_value() && m_grid[row][col]->top().GetColor() == lineColor) {
			++consecutiveCount;
		}
		else {
			consecutiveCount = 0;
		}
		if (consecutiveCount >= m_dimMax) {
			return true;
		}
	}
	return false;
}

bool eter::Board::isSecondaryDiagonalLine(const std::string& lineColor) const {
	if ((m_indexLineMax - m_indexLineMin) != (m_indexColMax - m_indexColMin)) {
		return false;
	}

	size_t consecutiveCount = 0;
	for (size_t i = 0; i <= m_indexLineMax - m_indexLineMin; ++i) {
		size_t row = m_indexLineMin + i;
		size_t col = m_indexColMax - i;

		if (m_grid[row][col].has_value() && m_grid[row][col]->top().GetColor() == lineColor) {
			++consecutiveCount;
		}
		else {
			consecutiveCount = 0;
		}
		if (consecutiveCount >= m_dimMax) {
			return true;
		}
	}
	return false;
}

bool eter::Board::isHorizontalLine(const std::string& lineColor) const {
	for (size_t row = m_indexLineMin; row <= m_indexLineMax; ++row) {
		size_t consecutiveCount = 0;
		for (size_t col = m_indexColMin; col <= m_indexColMax; ++col) {
			if (m_grid[row][col].has_value() && m_grid[row][col]->top().GetColor() == lineColor) {
				++consecutiveCount;
			}
			else {
				consecutiveCount = 0;
			}
			if (consecutiveCount >= m_dimMax) {
				return true;
			}
		}
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

std::string eter::Board::findWinnerByScore()
{
	uint16_t score1{ 0 };
	uint16_t score2{ 0 };
	for (size_t line = 0; line < m_grid.size(); ++line) {
		for (size_t col = 0; col < m_grid[line].size(); ++col) {
			if (m_grid[line][col].has_value()) {
				if (m_grid[line][col].value().top().GetColor() == "blue")
					if (m_grid[line][col].value().top().GetPosition() == true)
						score1 += m_grid[line][col].value().top().GetValue();
					else
						score1 += 1;
				if (m_grid[line][col].value().top().GetColor() == "red")
					if (m_grid[line][col].value().top().GetPosition() == true)
						score2 += m_grid[line][col].value().top().GetValue();
					else
						score2 += 1;
			}
		}
	}
	if (score1 > score2)
		return "blue";
	if (score2 > score1)
		return "red";
	return " ";
}

bool eter::Board::isBoardFull()
{
	size_t occupiedSpaces = 0;
	for (size_t row = m_indexLineMin; row <= m_indexLineMax; ++row){
		for (size_t col = m_indexColMin; col <= m_indexColMax; ++col){
			if (m_grid[row][col].has_value())
				occupiedSpaces++;
		}
	}
	return (occupiedSpaces == m_dimMax * m_dimMax);
}

void eter::Board::clear()
{
	for (auto& row : m_grid) {
		for (auto& cell : row) {
			cell.reset();  // `reset` resetează fiecare celulă la starea inițială
		}
	}
}

void eter::Board::swap(Board& other) noexcept
{
	using std::swap;
	swap(m_grid, other.m_grid);
	swap(m_rows, other.m_rows);
	swap(m_cols, other.m_cols);
}

bool Board::isValidRow(size_t row)
{
	return row >= m_indexLineMin && row <= m_indexLineMax;
}

void Board::eliminateCardsOnRow(size_t row)
{
	for (size_t col = m_indexColMin; col <= m_indexColMax; ++col) 
		 if (m_grid[row][col].has_value()){
			m_grid[row][col].reset(); // Elimina intregul teanc
			std::cout << "Stack removed at (" << row << ", " << col << ").\n";
		}
}

size_t Board::countOccupiedCellsOnRow(size_t row)
{
	size_t occupiedCount = 0;
	for (size_t col = m_indexColMin; col <= m_indexColMax ; ++col) {
		if (m_grid[row][col].has_value())
			++occupiedCount;
	}
	return occupiedCount;
}

bool Board::containsOwnCardOnRow(size_t row,const std::string& playerColor)
{
	for (size_t col = m_indexColMin; col <= m_indexColMax; ++col) {
		if (m_grid[row][col].has_value()) {
			const Card& topCard = m_grid[row][col].value().top();
			if (topCard.GetColor() == playerColor) 
				return true;
		}
	}
	return false;
}

void Board::eliminateCardsOnColumn(size_t col)
{
	for (size_t row = m_indexLineMin; col <= m_indexLineMax; ++row)
		if (m_grid[row][col].has_value()) {
			m_grid[row][col].reset(); // Elimina intregul teanc
			std::cout << "Stack removed at (" << row << ", " << col << ").\n";
		}
}

size_t Board::countOccupiedCellsOnColumn(size_t col)
{
	size_t occupiedCount = 0;
	for (size_t row = m_indexLineMin; col <= m_indexLineMax; ++row) {
		if (m_grid[row][col].has_value())
			++occupiedCount;
	}
	return occupiedCount;
}

bool Board::containsOwnCardOnColumn(size_t col, const std::string& playerColor)
{
	for (size_t row = m_indexLineMin; col <= m_indexLineMax; ++row) {
		if (m_grid[row][col].has_value()) {
			const Card& topCard = m_grid[row][col].value().top();
			if (topCard.GetColor() == playerColor)
				return true;
		}
	}
	return false;
}


bool Board::isValidColumn(size_t column)
{
	return column >= m_indexColMin && column <= m_indexColMax;
}

bool Board::isEmptyCell(size_t x, size_t y)
{
	if (!isValidPosition(x, y)) {
		return false;
	}
	return !m_grid[x][y].has_value();
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
				os<<"  ";
		}
		os << '\n';
	}
	return os;
}

void eter::swap(Board& first, Board& second) noexcept {
	first.swap(second);
}