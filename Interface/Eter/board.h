#ifndef BOARD_H
#define BOARD_H

#include"card.h"
#include<vector>
#include<optional>
#include<stack>
#include<utility>
#include<algorithm>
namespace eter {
class Board {
private:
    std::vector<std::vector<std::optional<std::stack<Card>>>>m_grid;
    size_t m_rows = { 7 }, m_cols = { 7 };   // ar trebui sterse deoarece le tine locul indexMax
    size_t m_indexMax;
    size_t m_dimMax;
    size_t m_indexLineMin, m_indexColMin, m_indexLineMax, m_indexColMax;
public:
    //Rule of 5
    Board();
    Board(const Board& other);
    Board& operator=(const Board& other);
    Board(Board&& other) noexcept;
    Board& operator=(Board&& other) noexcept;
    ~Board() = default;

    //Getters
    const size_t& GetRows() const;
    const size_t& GetCols() const;
    const std::vector<std::vector<std::optional<std::stack<Card>>>>& GetGrid() const;
    //std::vector<std::vector<std::optional<std::stack<Card>>>>& GetGrid();
    const size_t& GetDimMax() const;
    const size_t& GetIndexMax() const;
    const size_t& GetIndexLineMin() const;
    const size_t& GetIndexColMin() const;
    const size_t& GetIndexLineMax() const;
    const size_t& GetIndexColMax() const;
    std::optional<std::stack<Card>>& operator[](std::pair<int, int> pos);
    const std::optional<std::stack<Card>>& operator[](std::pair<int, int> pos) const;

    //Setters
    void SetDimMax(const size_t& dim);


    bool IsValidPosition(const size_t& x, const size_t& y) const;
    bool IsAdjacentToOccupiedSpace(const size_t& x, const size_t& y)const;
    bool ExistNonAdjacentCards(const size_t& x, const size_t& y) const;
    bool CanPlaceCard(const size_t& x, const size_t& y, const Card& card);
    bool PlaceCard(const size_t& x, const size_t& y, const Card& card);
    void UpdateAfterRemoval();
    void RemoveCard(const size_t& x, const size_t& y);

    bool IsVerticalLine(const std::string& lineColor) const;
    bool IsPrimaryDiagonalLine(const std::string& lineColor) const;
    bool IsSecondaryDiagonalLine(const std::string& lineColor) const;
    bool IsHorizontalLine(const std::string& lineColor) const;


    std::string FindWinner();
    std::string FindWinnerByScore();

    bool IsEmptyCell(const size_t& x, const size_t& y);

    bool IsBoardFull();
    bool IsTwoLineComplete();


    bool IsValidRow(const size_t& row) const;
    bool IsValidColumn(const size_t& column) const;
    bool IsEdgeRow(const size_t& row) const;
    bool IsEdgeColumn(const size_t& column) const;
    void MoveRow(const size_t& fromRow, const size_t& toRow);
    void MoveColumn(const size_t& fromCol, const size_t& toCol);


    size_t CountOccupiedCellsOnRow(const size_t& row);
    bool ContainsOwnCardOnRow(const size_t& row, const std::string& playerColor);
    void EliminateCardsOnRow(const size_t& row);
    size_t CountOccupiedCellsOnColumn(const size_t& col);
    bool ContainsOwnCardOnColumn(const size_t& col, const std::string& playerColor);
    void EliminateCardsOnColumn(const size_t& col);

    void CreateHole(const size_t& row, const size_t& col);

    void Clear();

    void swap(Board& other) noexcept;
    friend std::ostream& operator<<(std::ostream& os, const Board& board);
    friend void swap(Board& first, Board& second) noexcept;

};
}

#endif // BOARD_H
