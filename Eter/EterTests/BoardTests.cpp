#include "stdafx.h"
#include "CppUnitTest.h"
#include "Board.h"
#include "Player.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace eter;
namespace EterTests
{
	TEST_CLASS(BoardTests)
	{
	public:

		TEST_METHOD(TestPlaceCardAndIsEmptyCell)
		{
			Board board;
			Card testCard{ 3, "red", true };
			size_t x = 3, y = 3;
			bool placementResult = board.placeCard(x, y, testCard);
			Assert::IsTrue(placementResult, L"Card should be placed successfully.");
			Assert::IsFalse(board.isEmptyCell(x, y), L"The cell should no longer be empty after placing the card.");
		}

		TEST_METHOD(TestFindWinnerHorizontalLine)
		{
			Board board;
			Card redCard{ 1, "red", true };
			size_t winningRow = 2;
			for (size_t col = 0; col < board.GetDimMax(); ++col) {
				board.placeCard(winningRow, col, redCard);
			}

			std::string winner = board.findWinner();
			Assert::AreEqual(std::string("red"), winner, L"The winner should be 'red' due to a horizontal line.");
		}

		TEST_METHOD(TestRemoveCard)
		{
			Board board;
			Card testCard{ 3, "blue", true };
			size_t x = 2, y = 2;
			board.placeCard(x, y, testCard);
			Assert::IsFalse(board.isEmptyCell(x, y), L"The cell should not be empty after placing a card.");
			board.removeCard(x, y);
			Assert::IsTrue(board.isEmptyCell(x, y), L"The cell should be empty after removing the card.");
		}

		TEST_METHOD(TestEliminateCardsOnRow)
		{
			Board board;
			Card testCard1{ 1, "red", true }, testCard2{ 1, "blue", true }, testCard3{ 2,"red",true };
			size_t x = 0, y = 0;
			board.placeCard(x, y, testCard1);
			y = 1;
			board.placeCard(x, y, testCard2);
			y = 2;
			board.placeCard(x, y, testCard3);
			Assert::IsFalse(board.isEmptyCell(x, 0), L"Cell (0, 0) should not be empty after placing a card.");
			Assert::IsFalse(board.isEmptyCell(x, 1), L"Cell (0, 1) should not be empty after placing a card.");
			Assert::IsFalse(board.isEmptyCell(x, 2), L"Cell (0, 2) should not be empty after placing a card.");
			board.eliminateCardsOnRow(x);
			Assert::IsTrue(board.isEmptyCell(x, 0), L"Cell (0, 0) should be empty after eliminating cards on the row.");
			Assert::IsTrue(board.isEmptyCell(x, 1), L"Cell (0, 1) should be empty after eliminating cards on the row.");
			Assert::IsTrue(board.isEmptyCell(x, 2), L"Cell (0, 2) should be empty after eliminating cards on the row.");
		}

		TEST_METHOD(TestIsAdjacentToOccupiedSpace)
		{
			Board board;
			Card testCard{ 1, "red", true };
			size_t x = 3, y = 3;
			size_t adjacentX = 3, adjacentY = 4;
			board.placeCard(adjacentX, adjacentY, testCard);
			bool isAdjacent = board.isAdjacentToOccupiedSpace(x, y);
			Assert::IsTrue(isAdjacent, L"Position (3, 3) should be adjacent to an occupied space at (3, 4).");
			size_t isolatedX = 5, isolatedY = 5;
			isAdjacent = board.isAdjacentToOccupiedSpace(isolatedX, isolatedY);
			Assert::IsFalse(isAdjacent, L"Position (5, 5) should not be adjacent to any currently occupied space.");
		}

		TEST_METHOD(TestFindWinnerByScore)
		{
			Board board;
			Player testPlayer1{ "Player1","blue" };
			Player testPlayer2{ "Player2", "red" };
			Card testCard1{ 4,"red", true };
			Card testCard2{ 3,"blue", true };
			size_t x1 = 0, y1 = 2, x2 = 0, y2 = 3;
			board.placeCard(x1, y1, testCard1);
			board.placeCard(x2, y2, testCard2);
			std::string winner = board.findWinnerByScore();
			Assert::AreEqual(std::string("red"), winner, L"The winner is red.");

		}

		TEST_METHOD(TestIsValidPosition)
		{
			Board board;
			Assert::IsTrue(board.isValidPosition(0, 0), L"Position (0, 0) should be valid.");
			Assert::IsTrue(board.isValidPosition(board.GetIndexMax() - 1, board.GetIndexMax() - 1),
				L"Position at the bottom-right corner should be valid.");
			Assert::IsFalse(board.isValidPosition(board.GetIndexMax(), 0), L"Position (board.GetIndexMax(), 0) should be invalid.");
			Assert::IsFalse(board.isValidPosition(0, board.GetIndexMax()), L"Position (0, board.GetIndexMax()) should be invalid.");
			Assert::IsFalse(board.isValidPosition(-1, 0), L"Position (-1, 0) should be invalid.");
			Assert::IsFalse(board.isValidPosition(0, -1), L"Position (0, -1) should be invalid.");
			Assert::IsTrue(board.isValidPosition(3, 3), L"Position (3, 3) should be valid on an empty board.");
			size_t x = 3, y = 3;
			board.placeCard(x, y, Card{ 5, "red", true });
			Assert::IsTrue(board.isValidPosition(2, 3), L"Position (2, 3) should be valid within the restricted range.");
			Assert::IsFalse(board.isValidPosition(0, 0), L"Position (0, 0) should be invalid outside the restricted range.");
		}

		TEST_METHOD(TestContainsOwnCardOnRow)
		{
			Board board;
			Player testPlayer{ "Player1", "red" };
			size_t x = 0, y = 0;
			Card testCard{ 1,"blue", true };
			board.placeCard(x, y, testCard);
			Card ownCard{ 1,"red", true };
			board.placeCard(x,y+1,ownCard);
			bool containsOwnCard = board.containsOwnCardOnRow(x, "red");
			Assert::IsTrue(containsOwnCard, L"The row 0 contains at least one red (own) card.");
		}

		TEST_METHOD(TestCreateHole)
		{
			Board board;
			Card testCard{ 3, "red", true };
			size_t x = 1, y = 1;
			board.placeCard(x, y, testCard);
			board.createHole(x, y);
			Assert::IsFalse(board.isEmptyCell(x, y), L"The cell should not be empty after creating a hole.");
			Assert::AreEqual(static_cast<int>('/'), static_cast<int>(board.GetGrid()[x][y]->top().GetValue()),
				L"The cell should contain a hole.");

		}


		TEST_METHOD(TestIsTwoLineComplete)
		{
			Board board;
			board.placeCard(0, 0, { 1,"red",true });
			board.placeCard(0, 1, { 2,"red",true });
			board.placeCard(0, 2, { 3,"red",true });
			board.placeCard(0, 3, { 4,"red",true });
			board.placeCard(1, 0, { 1,"blue",true });
			board.placeCard(1, 1, { 2,"blue",true });
			board.placeCard(1, 2, { 3,"blue",true });
			board.placeCard(1, 3, { 4,"blue",true });
			bool isComplete = board.isTwoLineComplete();
			Assert::IsTrue(isComplete, L"Two lines have been completed.");
		}

		TEST_METHOD(TestBoardConstructor)
		{
			Board board;
			Assert::AreEqual(size_t(3), board.GetDimMax(), L"Default m_dimMax should be 3.");
			Assert::AreEqual(size_t(7), board.GetIndexMax(), L"Default m_indexMax should be 7.");
			Assert::AreEqual(size_t(10), board.GetIndexLineMin(), L"Default m_indexLineMin should be 10.");
			Assert::AreEqual(size_t(10), board.GetIndexLineMax(), L"Default m_indexLineMax should be 10.");
			Assert::AreEqual(size_t(10), board.GetIndexColMin(), L"Default m_indexColMin should be 10.");
			Assert::AreEqual(size_t(10), board.GetIndexColMax(), L"Default m_indexColMax should be 10.");
			const auto& grid = board.GetGrid();
			Assert::AreEqual(size_t(7), grid.size(), L"Grid should have 7 rows.");
			for (const auto& row : grid)
			{
				Assert::AreEqual(size_t(7), row.size(), L"Each row in the grid should have 7 columns.");
				for (const auto& cell : row)
				{
					Assert::IsFalse(cell.has_value(), L"Each cell in the grid should be initialized to nullopt.");
				}
			}
		}

		TEST_METHOD(TestUpdateAfterRemoval)
		{
			Board board;
			Card card1{ 2, "red", true };
			Card card2{ 3, "blue", true };
			board.placeCard(1, 1, card1); 
			board.placeCard(2, 2, card2); 

			Assert::AreEqual(size_t(1), board.GetIndexLineMin(), L"Initial m_indexLineMin should be 1.");
			Assert::AreEqual(size_t(2), board.GetIndexLineMax(), L"Initial m_indexLineMax should be 3.");
			Assert::AreEqual(size_t(1), board.GetIndexColMin(), L"Initial m_indexColMin should be 1.");
			Assert::AreEqual(size_t(2), board.GetIndexColMax(), L"Initial m_indexColMax should be 4.");

			board.removeCard(2, 2); 
			board.updateAfterRemoval();

			Assert::AreEqual(size_t(1), board.GetIndexLineMin(), L"m_indexLineMin should remain 1 after update.");
			Assert::AreEqual(size_t(1), board.GetIndexLineMax(), L"m_indexLineMax should be updated to 1 after update.");
			Assert::AreEqual(size_t(1), board.GetIndexColMin(), L"m_indexColMin should remain 1 after update.");
			Assert::AreEqual(size_t(1), board.GetIndexColMax(), L"m_indexColMax should be updated to 1 after update.");

			board.removeCard(1, 1); 
			board.updateAfterRemoval();

			Assert::AreEqual(size_t(10), board.GetIndexLineMin(), L"m_indexLineMin should reset to 10 when the board is empty.");
			Assert::AreEqual(size_t(10), board.GetIndexLineMax(), L"m_indexLineMax should reset to 10 when the board is empty.");
			Assert::AreEqual(size_t(10), board.GetIndexColMin(), L"m_indexColMin should reset to 10 when the board is empty.");
			Assert::AreEqual(size_t(10), board.GetIndexColMax(), L"m_indexColMax should reset to 10 when the board is empty.");
		}

		TEST_METHOD(TestIsVerticalLine)
		{
			Board board;
			board.placeCard(1, 0, { 1,"blue", true });
			board.placeCard(2, 0, { 2,"blue", true });
			board.placeCard(3, 0, { 3,"blue", true });
			board.placeCard(4, 0, { 4,"blue", true });
			bool isVerticalLine = board.isVerticalLine("blue");
			Assert::IsTrue(isVerticalLine, L"Vertical line in the colour blue exists.");
		}

		TEST_METHOD(TestBoardSwap)
		{
			Board board1;
			Board board2;

			Card card1{ 5, "red", true };
			Card card2{ 3, "blue", true };
			board1.placeCard(0, 0, card1);
			board1.placeCard(1, 1, card2);

			Card card3{ 7, "red", true };
			Card card4{ 9, "blue", true };
			board2.placeCard(2, 2, card3);
			board2.placeCard(3, 3, card4);

			board1.swap(board2);

			Assert::IsTrue(board1.GetGrid()[2][2].has_value(), L"board1 should now have a card at (2, 2) after swap.");
			Assert::AreEqual(static_cast<int>(7), static_cast<int>(board1.GetGrid()[2][2]->top().GetValue()), L"The card at (2, 2) in board1 should have value 7.");
			Assert::IsTrue(board1.GetGrid()[3][3].has_value(), L"board1 should now have a card at (3, 3) after swap.");
			Assert::AreEqual(static_cast<int>(9), static_cast<int>(board1.GetGrid()[3][3]->top().GetValue()), L"The card at (3, 3) in board1 should have value 9.");
			Assert::IsTrue(board2.GetGrid()[0][0].has_value(), L"board2 should now have a card at (0, 0) after swap.");
			Assert::AreEqual(static_cast<int>(5), static_cast<int>(board2.GetGrid()[0][0]->top().GetValue()), L"The card at (0, 0) in board2 should have value 5.");
			Assert::IsTrue(board2.GetGrid()[1][1].has_value(), L"board2 should now have a card at (1, 1) after swap.");
			Assert::AreEqual(static_cast<int>(3), static_cast<int>(board2.GetGrid()[1][1]->top().GetValue()), L"The card at (1, 1) in board2 should have value 3.");
		}

		TEST_METHOD(TestMoveColumn)
		{
			Board board;
			Card card1{ 4, "red", true };
			Card card2{ 3, "blue", true };

			size_t fromCol = 0;
			size_t toCol = 2;

			board.placeCard(0, fromCol, card1); 
			board.placeCard(1, fromCol, card2); 

			Assert::IsFalse(board.isEmptyCell(0, fromCol), L"Cell (0, 0) should not be empty before moving the column.");
			Assert::IsFalse(board.isEmptyCell(1, fromCol), L"Cell (1, 0) should not be empty before moving the column.");
			Assert::IsTrue(board.isEmptyCell(0, toCol), L"Cell (0, 2) should be empty before moving the column.");
			Assert::IsTrue(board.isEmptyCell(1, toCol), L"Cell (1, 2) should be empty before moving the column.");

			board.moveColumn(fromCol, toCol);

			Assert::IsFalse(board.isEmptyCell(0, toCol), L"Cell (0, 2) should not be empty after moving the column.");
			Assert::IsFalse(board.isEmptyCell(1, toCol), L"Cell (1, 2) should not be empty after moving the column.");
			Assert::AreEqual(static_cast<int>(5), static_cast<int>(board.GetGrid()[0][toCol]->top().GetValue()), L"The card at (0, 2) should have value 5.");
			Assert::AreEqual(static_cast<int>(3), static_cast<int>(board.GetGrid()[1][toCol]->top().GetValue()), L"The card at (1, 2) should have value 3.");

			Assert::IsTrue(board.isEmptyCell(0, fromCol), L"Cell (0, 0) should be empty after moving the column.");
			Assert::IsTrue(board.isEmptyCell(1, fromCol), L"Cell (1, 0) should be empty after moving the column.");
		}

	};
}
