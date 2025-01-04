#include "board.h"
using namespace eter;
eter::Board::Board()
    : m_dimMax{ 3 }, m_indexMax{ 7 },
    m_indexLineMin{ 10 }, m_indexLineMax{ 10 },
    m_indexColMin{ 10 }, m_indexColMax{ 10 }
{
    // Inițializează grila
    m_grid.resize(m_indexMax, std::vector<std::optional<std::stack<Card>>>(m_indexMax));
}

Board::Board(const Board& other)
    : m_grid{ other.m_grid }
    , m_indexMax{other.m_indexMax}
    , m_indexLineMin{ other.m_indexLineMin }
    , m_indexLineMax{ other.m_indexLineMax }
    , m_indexColMin{ other.m_indexColMin }
    , m_indexColMax{ other.m_indexColMax }
    , m_dimMax{other.m_dimMax}
{
}

Board& Board::operator=(const Board& other) {
    if (this != &other) {
        m_grid = other.m_grid;
        m_indexMax = other.m_indexMax;
        m_dimMax = other.m_dimMax;
        m_indexLineMin = other.m_indexLineMin;
        m_indexColMin = other.m_indexColMin;
        m_indexLineMax = other.m_indexLineMax;
        m_indexColMax = other.m_indexColMax;
    }
    return *this;
}

Board::Board(Board&& other) noexcept
    : m_grid{ std::move(other.m_grid) },
    m_indexMax{ other.m_indexMax },
    m_indexLineMin{ other.m_indexLineMin },
    m_indexLineMax{ other.m_indexLineMax },
    m_indexColMin{ other.m_indexColMin },
    m_indexColMax{ other.m_indexColMax },
    m_dimMax{ other.m_dimMax }
{
    other.m_dimMax = 3;
    other.m_indexMax = 7;
    other.m_indexLineMin = 10;
    other.m_indexLineMax = 10;
    other.m_indexColMin = 10;
    other.m_indexColMax = 10;
}

Board& Board::operator=(Board&& other) noexcept
{
    if (this == &other) return *this;
    m_grid = std::move(other.m_grid);
    m_indexMax = other.m_indexMax;
    m_indexLineMin = other.m_indexLineMin;
    m_indexLineMax = other.m_indexLineMax;
    m_indexColMin = other.m_indexColMin;
    m_indexColMax = other.m_indexColMax;
    m_dimMax = other.m_dimMax;


    other.m_dimMax = 3;
    other.m_indexMax = 7;
    other.m_indexLineMin = 10;
    other.m_indexLineMax = 10;
    other.m_indexColMin = 10;
    other.m_indexColMax = 10;

    return *this;
}

const std::vector<std::vector<std::optional<std::stack<Card>>>>& Board::GetGrid() const
{
    return m_grid;
}

const size_t& eter::Board::GetDimMax() const
{
    return m_dimMax;
}

const size_t &Board::GetIndexMax() const
{
    return m_indexMax;
}

const size_t& eter::Board::GetIndexLineMin() const
{
    return m_indexLineMin;
}

const size_t& eter::Board::GetIndexColMin() const
{
    return m_indexColMin;
}

const size_t& eter::Board::GetIndexLineMax() const
{
    return m_indexLineMax;
}

const size_t& eter::Board::GetIndexColMax() const
{
    return m_indexColMax;
}

std::optional<std::stack<Card>>& Board::operator[](std::pair<int, int> pos) {
    int x = pos.first;
    int y = pos.second;
    if (IsValidPosition(x, y)) {
        return m_grid[x][y];
    }
    throw std::out_of_range("Invalid position");
}

const std::optional<std::stack<Card>>& Board::operator[](std::pair<int, int> pos) const {
    int x = pos.first;
    int y = pos.second;
    if (IsValidPosition(x, y)) {
        return m_grid[x][y];
    }
    throw std::out_of_range("Invalid position");
}

void eter::Board::SetDimMax(const size_t& dim)
{
    m_dimMax = dim;
}

bool Board::IsValidPosition(const size_t& x, const size_t& y) const
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

bool eter::Board::IsAdjacentToOccupiedSpace(const size_t& x, const size_t& y)const
{
    static const std::vector<std::pair<int, int>> directions = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},          {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    for (const auto& [dx, dy] : directions) {
        int nx = x + dx;
        int ny = y + dy;
        if ( IsValidPosition(nx,ny) && m_grid[nx][ny].has_value() && !m_grid[nx][ny].value().empty()) {
            return true; // cel putin  un spadiacent este ocupat
        }
    }
    return false; // niciun sp adiacent nu este ocupat
}

bool eter::Board::ExistNonAdjacentCards(const size_t& x, const size_t& y) const
{
    static const std::vector<std::pair<int, int>> directions = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},          {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    for (const auto& [dx, dy] : directions) {
        int nx = x + dx;
        int ny = y + dy;
        if ( m_grid[nx][ny].has_value() && !m_grid[nx][ny].value().empty()) {
            return true; // cel putin  un spadiacent este ocupat
        }
    }
    return false; // niciun sp adiacent nu este ocupat
}


bool eter::Board::CanPlaceCard(const size_t& x, const size_t& y, const Card& card)
{
    if (!IsValidPosition(x, y))
    {
        return false;
    }
    if (m_grid[x][y].has_value())
    {
        const auto& stack = m_grid[x][y].value();
        if ((!stack.empty() && stack.top().GetValue() == 5) || (!stack.empty() && card.GetValue() == 5)) return false; // cannot place anything over eter card
        if (!stack.empty() && card.GetColor() == stack.top().GetColor() && !stack.top().GetPosition()) { // cannot put card over your own illusion
            return false;
        }
        if (!stack.empty() && card.GetValue() > stack.top().GetValue()) {
            return true;
        }
        return false;
    }
    bool IsBoardEmpty = true;
    for (const auto& row : m_grid) {
        for (const auto& cell : row) {
            if (cell.has_value()) {
                IsBoardEmpty = false;
                break;
            }
        }
    }
    if (IsBoardEmpty) {
        // Daca tabla este goala, initializeaza limitele
        m_indexLineMin = x;
        m_indexLineMax = x;
        m_indexColMin = y;
        m_indexColMax = y;
    }

    return IsBoardEmpty || IsAdjacentToOccupiedSpace(x, y);
}


bool eter::Board::PlaceCard(const size_t& x, const size_t& y, const Card& card)
{
    if (!CanPlaceCard(x, y, card))

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

void Board::UpdateAfterRemoval()
{
    size_t newLineMin = m_indexMax; // Setează inițial la valori maxime
    size_t newLineMax = 0;
    size_t newColMin = m_indexMax;
    size_t newColMax = 0;
    bool hasCards = false;

    for (size_t i = 0; i < m_indexMax; ++i) {
        for (size_t j = 0; j < m_indexMax; ++j) {
            if (m_grid[i][j].has_value() && !m_grid[i][j]->empty()) {
                hasCards = true;
                newLineMin = std::min(newLineMin, i);
                newLineMax = std::max(newLineMax, i);
                newColMin = std::min(newColMin, j);
                newColMax = std::max(newColMax, j);
            }
        }
    }

    if (hasCards) {
        m_indexLineMin = newLineMin;
        m_indexLineMax = newLineMax;
        m_indexColMin = newColMin;
        m_indexColMax = newColMax;
    }
    else {
        // Tabla este goală, resetează limitele la valori implicite
        m_indexLineMin = 10;
        m_indexLineMax = 10;
        m_indexColMin = 10;
        m_indexColMax = 10;
    }
}


void eter::Board::RemoveCard(const size_t& x, const size_t& y)
{
    if (m_grid[x][y].has_value() && !m_grid[x][y].value().empty())
    {
        m_grid[x][y].value().pop();
        if (m_grid[x][y]->empty())
        {
            m_grid[x][y].reset();
        }

    }
}

bool eter::Board::IsVerticalLine(const std::string& lineColor) const {
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

bool eter::Board::IsPrimaryDiagonalLine(const std::string& lineColor) const {
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

bool eter::Board::IsSecondaryDiagonalLine(const std::string& lineColor) const {
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

bool eter::Board::IsHorizontalLine(const std::string& lineColor) const {

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


std::string eter::Board::FindWinner()
{
    if (IsHorizontalLine("red") || IsVerticalLine("red") || IsPrimaryDiagonalLine("red") || IsSecondaryDiagonalLine("red"))
        return "red";
    else if (IsHorizontalLine("blue") || IsVerticalLine("blue") || IsPrimaryDiagonalLine("blue") || IsSecondaryDiagonalLine("blue"))
        return "blue";
    return std::string{ "No winner yet" };
}

std::string eter::Board::FindWinnerByScore()
{
    uint16_t score1{ 0 };
    uint16_t score2{ 0 };
    for (size_t line = m_indexLineMin; line <= m_indexLineMax; ++line) {
        for (size_t col = m_indexColMin; col <= m_indexColMax; ++col) {
            if (m_grid[line][col].has_value()) {
                if (m_grid[line][col].value().top().GetValue() == '/')
                    continue;
                if (m_grid[line][col].value().top().GetColor() == "blue")
                    if (m_grid[line][col].value().top().GetPosition() == true && m_grid[line][col].value().top().GetValue() != 5)
                        score1 += m_grid[line][col].value().top().GetValue();
                    else
                        score1 += 1;
                if (m_grid[line][col].value().top().GetColor() == "red")
                    if (m_grid[line][col].value().top().GetPosition() == true && m_grid[line][col].value().top().GetValue() != 5)
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

bool eter::Board::IsBoardFull()
{
    size_t occupiedSpaces = 0;
    for (size_t row = m_indexLineMin; row <= m_indexLineMax; ++row) {
        for (size_t col = m_indexColMin; col <= m_indexColMax; ++col) {
            if (m_grid[row][col].has_value())
                occupiedSpaces++;
        }
    }
    return (occupiedSpaces == m_dimMax * m_dimMax);
}

bool eter::Board::IsTwoLineComplete()
{
    size_t linesOcupate, columnOcupate;
    linesOcupate = columnOcupate = 0;
    for (size_t row = m_indexLineMin; row <= m_indexLineMax; ++row)
    {
        size_t occupiedSpaces = 0;
        for (size_t col = m_indexColMin; col <= m_indexColMax; ++col)
        {
            if (m_grid[row][col].has_value())
                occupiedSpaces++;
        }
        if (occupiedSpaces == m_dimMax)
            linesOcupate++;
    }

    for (size_t col = m_indexColMin; col <= m_indexColMax; ++col)
    {
        size_t occupiedSpaces = 0;
        for (size_t row = m_indexLineMin; row <= m_indexLineMax; ++row)
        {
            if (m_grid[row][col].has_value())
                occupiedSpaces++;
        }
        if (occupiedSpaces == m_dimMax)
            columnOcupate++;
    }
    return (linesOcupate==2 || columnOcupate==2
            ||(linesOcupate == 1 && columnOcupate == 1));
}

void eter::Board::Clear()
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
    swap(m_indexColMin,other.m_indexColMin);
    swap(m_indexColMax,other.m_indexColMax);
    swap(m_indexLineMax,other.m_indexLineMax);
    swap(m_indexLineMin,other.m_indexLineMin);
    swap(m_dimMax,other.m_dimMax);
    swap(m_indexMax,other.m_indexMax);

}

bool Board::IsValidRow(const size_t& row) const
{
    return row >= m_indexLineMin && row <= m_indexLineMax;
}

void Board::EliminateCardsOnRow(const size_t& row)
{
    for (size_t col = m_indexColMin; col <= m_indexColMax; ++col)
        if (m_grid[row][col].has_value()) {
            if (m_grid[row][col].value().top().GetValue() == 5)
                continue;
            if (m_grid[row][col].value().top().GetValue() == '/')
                continue;
            m_grid[row][col].reset(); // Elimina intregul teanc
            std::cout << "Stack removed at (" << row << ", " << col << ").\n";
        }
}

size_t Board::CountOccupiedCellsOnRow(const size_t& row)
{
    size_t occupiedCount = 0;
    for (size_t col = m_indexColMin; col <= m_indexColMax; ++col) {
        if (m_grid[row][col].has_value())
            ++occupiedCount;
    }
    return occupiedCount;
}

bool Board::ContainsOwnCardOnRow(const size_t& row, const std::string& playerColor)
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

void Board::EliminateCardsOnColumn(const size_t& col)
{
    for (size_t row = m_indexLineMin; row <= m_indexLineMax; ++row)
        if (m_grid[row][col].has_value()) {
            if (m_grid[row][col].value().top().GetValue() == 5)
                continue;
            if (m_grid[row][col].value().top().GetValue() == '/')
                continue;
            m_grid[row][col].reset(); // Elimina intregul teanc
            std::cout << "Stack removed at (" << row << ", " << col << ").\n";
        }
}


void eter::Board::CreateHole(const size_t& row, const size_t& col)
{
    if (m_grid[row][col].has_value())
    {
        if (m_grid[row][col].value().top().GetValue() == 5)
            return;
        m_grid[row][col].reset();
    }
    m_grid[row][col] = std::stack<Card>();
    m_grid[row][col]->push(Card{ '/', "\033[0m" , true });

}


size_t Board::CountOccupiedCellsOnColumn(const size_t& col)
{
    size_t occupiedCount = 0;
    for (size_t row = m_indexLineMin; row <= m_indexLineMax; ++row) {
        if (m_grid[row][col].has_value())
            ++occupiedCount;
    }
    return occupiedCount;
}

bool Board::ContainsOwnCardOnColumn(const size_t& col, const std::string& playerColor)
{
    for (size_t row = m_indexLineMin; row <= m_indexLineMax; ++row) {
        if (m_grid[row][col].has_value()) {
            const Card& topCard = m_grid[row][col].value().top();
            if (topCard.GetColor() == playerColor)
                return true;
        }
    }
    return false;
}


bool Board::IsValidColumn(const size_t& column) const
{
    return column >= m_indexColMin && column <= m_indexColMax;
}

bool eter::Board::IsEdgeRow(const size_t& row) const
{
    return row == m_indexLineMin || row == m_indexLineMax;

}

bool eter::Board::IsEdgeColumn(const size_t& column) const
{
    return column == m_indexColMin || column == m_indexColMax;

}

void eter::Board::MoveRow(const size_t& fromRow, const size_t& toRow) {

    std::transform(
        m_grid[fromRow].begin() + m_indexColMin,
        m_grid[fromRow].begin() + m_indexColMax + 1,
        m_grid[toRow].begin() + m_indexColMin,
        [](std::optional<std::stack<Card>>& source) {
            return std::move(source);
        }
        );
    std::for_each(m_grid[fromRow].begin() + m_indexColMin,
                  m_grid[fromRow].begin() + m_indexColMax + 1,
                  [](std::optional<std::stack<Card>>& cell) {
                      cell.reset();
                  });
}


void eter::Board::MoveColumn(const size_t& fromCol, const size_t& toCol) {
    std::transform(
        m_grid[fromCol].begin() + m_indexLineMin,
        m_grid[fromCol].begin() + m_indexLineMax + 1,
        m_grid[toCol].begin() + m_indexLineMin,
        [](std::optional<std::stack<Card>>& source) {
            return std::move(source);
        }
        );
    std::for_each(m_grid[fromCol].begin() + m_indexLineMin,
                  m_grid[fromCol].begin() + m_indexLineMax + 1,
                  [](std::optional<std::stack<Card>>& cell) {
                      cell.reset();
                  });
}

bool Board::IsEmptyCell(const size_t& x, const size_t& y)
{
    if (!IsValidPosition(x, y)) {
        return false;
    }
    return !m_grid[x][y].has_value();
}


std::ostream& eter::operator<<(std::ostream& os, const Board& board)
{
    for (size_t line = 0; line < board.GetIndexMax(); ++line)
    {
        for (size_t column = 0; column < board.GetIndexMax(); ++column)
        {
            if (board.GetGrid()[line][column].has_value())
                os << board.GetGrid()[line][column].value().top() << " ";
            else
                os << "  ";
        }
        os << '\n';
    }

    return os;
}

void eter::swap(Board& first, Board& second) noexcept {
    first.swap(second);
}
