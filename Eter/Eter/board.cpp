﻿#include "Board.h"
using namespace eter;
const std::string_view kEmpyBoardCell{ "____" };
#include <iostream>
#include <algorithm>
#include <ranges>
Board::Board()
	: m_dimMax{ 3 }, m_indexMax{ 7 },
	m_indexLineMin{ 10 }, m_indexLineMax{ 10 },
	m_indexColMin{ 10 }, m_indexColMax{ 10 }
{
	m_grid.resize(m_indexMax, std::vector<std::optional<std::stack<Card>>>(m_indexMax));
}

Board::Board(const Board& other)
	: m_grid{ other.m_grid }
	, m_indexMax{ other.m_indexMax }
	, m_indexLineMin{ other.m_indexLineMin }
	, m_indexLineMax{ other.m_indexLineMax }
	, m_indexColMin{ other.m_indexColMin }
	, m_indexColMax{ other.m_indexColMax }
	, m_dimMax{ other.m_dimMax }
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

const size_t& Board::GetIndexMax() const
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

const std::pair<size_t, char>& eter::Board::getBlockedLine() const {
	return m_blockedLine;
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

void eter::Board::SetDimMax(const size_t& dim)
{
	m_dimMax = dim;
}

void eter::Board::setBlockedLine(size_t number, char character) {
	m_blockedLine.first = number;
	m_blockedLine.second = character;
}

bool Board::isValidPosition(size_t x, size_t y) const
{
	if (x < 0 || y < 0 || x >= m_indexMax || y >= m_indexMax) {
		return false;
	}

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

	return std::ranges::any_of(directions, [&](const auto& dir) {
		int nx = x + dir.first, ny = y + dir.second;
		return isValidPosition(nx, ny) && m_grid[nx][ny].has_value() && !m_grid[nx][ny]->empty();
		});
}

bool eter::Board::existNonAdjacentCards(size_t x, size_t y)
{
	static const std::vector<std::pair<int, int>> directions = {
		{-1, -1}, {-1, 0}, {-1, 1},
		{0, -1},          {0, 1},
		{1, -1}, {1, 0}, {1, 1}
	};

	for (const auto& [dx, dy] : directions) {
		int nx = x + dx;
		int ny = y + dy;
		if (m_grid[nx][ny].has_value() && !m_grid[nx][ny].value().empty()) {
			return true; 
		}
	}
	return false; 
}


bool eter::Board::canPlaceCard(size_t x, size_t y, const Card& card)
{
	if (!isValidPosition(x, y))
	{
		return false;
	}

	if (m_blockedLine.first != 10 && m_blockedLine.second != '\0') {
		if (m_blockedLine.second == 'R')
		{
			if (x == m_blockedLine.first)
			{
				return false;
			}
		}
		if (m_blockedLine.second == 'C')
		{
			if (y == m_blockedLine.first)
			{
				return false;
			}
		}
	}

	if (m_grid[x][y].has_value())
	{
		const auto& stack = m_grid[x][y].value();
		if ((!stack.empty() && stack.top().GetValue() == 5) || (!stack.empty() && card.GetValue() == 5)) return false; 
		if (!stack.empty() && card.GetColor() == stack.top().GetColor() && !stack.top().GetPosition()) { 
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

	m_indexLineMin = std::min(m_indexLineMin, x);
	m_indexLineMax = std::max(m_indexLineMax, x);
	m_indexColMin = std::min(m_indexColMin, y);
	m_indexColMax = std::max(m_indexColMax, y);

	if (m_blockedLine.first != 10 && m_blockedLine.second != '\0')
	{
		m_blockedLine.first = 10;
		m_blockedLine.second = '\0';
	}

	std::cout << "The card with value " << static_cast<int>(card.GetValue())
		<< " has been placed at (" << x << ", " << y << ").\n";
	return true;
}

void Board::updateAfterRemoval()
{
	size_t newLineMin = m_indexMax; 
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
		m_indexLineMin = 10;
		m_indexLineMax = 10;
		m_indexColMin = 10;
		m_indexColMax = 10;
	}
}


void eter::Board::removeCard(size_t x, size_t y)
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

bool eter::Board::isBoardFull()
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

bool eter::Board::isTwoLineComplete()
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
	return (linesOcupate == 2 || columnOcupate == 2
		|| (linesOcupate == 1 && columnOcupate == 1));
}

void eter::Board::clear()
{
	for (auto& row : m_grid) {
		for (auto& cell : row) {
			cell.reset();
		}
	}
}

void eter::Board::swap(Board& other) noexcept
{
	using std::swap;
	swap(m_grid, other.m_grid);
}

bool Board::isValidRow(size_t row) const
{
	return row >= m_indexLineMin && row <= m_indexLineMax;
}

void Board::eliminateCardsOnRow(size_t row)
{
	for (size_t col = m_indexColMin; col <= m_indexColMax; ++col)
		if (m_grid[row][col].has_value()) {
			if (m_grid[row][col].value().top().GetValue() == 5)
				continue;
			if (m_grid[row][col].value().top().GetValue() == '/')
				continue;
			m_grid[row][col].reset();
			std::cout << "Stack removed at (" << row << ", " << col << ").\n";
		}
}

size_t Board::countOccupiedCellsOnRow(size_t row)
{
	return std::ranges::count_if(m_grid[row] | std::views::drop(m_indexColMin) | std::views::take(m_indexColMax - m_indexColMin + 1),
		[](const auto& cell) { return cell.has_value(); });
}

bool Board::containsOwnCardOnRow(size_t row, const std::string& playerColor)
{
	return std::ranges::any_of(
		m_grid[row] | std::views::drop(m_indexColMin) | std::views::take(m_indexColMax - m_indexColMin + 1),
		[&](const auto& cell) {
			return cell.has_value() && cell->top().GetColor() == playerColor;
		}
	);
}

void Board::eliminateCardsOnColumn(size_t col)
{
	for (size_t row = m_indexLineMin; row <= m_indexLineMax; ++row)
		if (m_grid[row][col].has_value()) {
			if (m_grid[row][col].value().top().GetValue() == 5)
				continue;
			if (m_grid[row][col].value().top().GetValue() == '/')
				continue;
			m_grid[row][col].reset();
			std::cout << "Stack removed at (" << row << ", " << col << ").\n";
		}
}


void eter::Board::createHole(size_t row, size_t col)
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

std::vector<std::vector<std::optional<std::stack<Card>>>>& Board::GetGridForModeA()
{
	return m_grid;
}


size_t Board::countOccupiedCellsOnColumn(size_t col)
{
	return static_cast<size_t>(std::ranges::count_if(
		std::views::iota(static_cast<ptrdiff_t>(m_indexLineMin), static_cast<ptrdiff_t>(m_indexLineMax + 1)),
		[&](ptrdiff_t row) {
			return m_grid[static_cast<size_t>(row)][col].has_value();
		}
	));
}

bool Board::containsOwnCardOnColumn(size_t col, const std::string& playerColor)
{
	return std::ranges::any_of(
		std::views::iota(m_indexLineMin, m_indexLineMax + 1),
		[&](size_t row) {
			if (m_grid[row][col].has_value()) {
				const Card& topCard = m_grid[row][col].value().top();
				return topCard.GetColor() == playerColor;
			}
			return false;
		}
	);
}


bool Board::isValidColumn(size_t column) const
{
	return column >= m_indexColMin && column <= m_indexColMax;
}

bool eter::Board::isEdgeRow(size_t row) const
{
	return row == m_indexLineMin || row == m_indexLineMax;

}

bool eter::Board::isEdgeColumn(size_t column) const
{
	return column == m_indexColMin || column == m_indexColMax;

}

std::vector<Card> Board::shiftRowForward(size_t row) {
	std::vector<Card> returnedCards;
	auto temp = std::move(m_grid[row][m_indexColMax]);

	if (temp.has_value() && !temp->empty()) {
		while (!temp->empty()) {
			returnedCards.push_back(temp->top());
			temp->pop();
		}
	}

	for (size_t col = m_indexColMax; col > m_indexColMin; --col) {
		m_grid[row][col] = std::move(m_grid[row][col - 1]);
	}

	m_grid[row][m_indexColMin].reset();

	return returnedCards;
}


std::vector<Card> Board::shiftRowBackward(size_t row) {
	std::vector<Card> returnedCards;
	auto temp = std::move(m_grid[row][m_indexColMin]);

	if (temp.has_value() && !temp->empty()) {
		while (!temp->empty()) {
			returnedCards.push_back(temp->top());
			temp->pop();
		}
	}

	for (size_t col = m_indexColMin; col < m_indexColMax; ++col) {
		m_grid[row][col] = std::move(m_grid[row][col + 1]);
	}
	m_grid[row][m_indexColMax].reset();

	return returnedCards;
}


std::vector<Card> Board::shiftColumnForward(size_t col) {
	std::vector<Card> returnedCards;
	auto temp = std::move(m_grid[m_indexLineMax][col]);

	if (temp.has_value() && !temp->empty()) {
		while (!temp->empty()) {
			returnedCards.push_back(temp->top());
			temp->pop();
		}
	}

	for (size_t row = m_indexLineMax; row > m_indexLineMin; --row) {
		m_grid[row][col] = std::move(m_grid[row - 1][col]);
	}

	m_grid[m_indexLineMin][col].reset();

	return returnedCards;
}

std::vector<Card> Board::shiftColumnBackward(size_t col) {
	std::vector<Card> returnedCards;
	auto temp = std::move(m_grid[m_indexLineMin][col]);

	if (temp.has_value() && !temp->empty()) {
		while (!temp->empty()) {
			returnedCards.push_back(temp->top());
			temp->pop();
		}
	}

	for (size_t row = m_indexLineMin; row < m_indexLineMax; ++row) {
		m_grid[row][col] = std::move(m_grid[row + 1][col]);
	}

	m_grid[m_indexLineMax][col].reset();

	return returnedCards;
}



void eter::Board::moveColumn(size_t fromCol, size_t toCol) {
	std::ranges::for_each(
		std::views::iota(m_indexLineMin, m_indexLineMax + 1),
		[&](size_t row) {
			m_grid[row][toCol] = std::move(m_grid[row][fromCol]);
			m_grid[row][fromCol].reset();
		}
	);
}

void eter::Board::moveRow(size_t fromRow, size_t toRow) {
	std::ranges::for_each(
		std::views::iota(m_indexColMin, m_indexColMax + 1),
		[&](size_t col) {
			m_grid[toRow][col] = std::move(m_grid[fromRow][col]);
			m_grid[fromRow][col].reset();
		}
	);
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
	for (uint8_t line = 0; line < board.GetIndexMax(); ++line)
	{
		for (uint8_t column = 0; column < board.GetIndexMax(); ++column)
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
