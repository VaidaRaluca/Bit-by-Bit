#include "stdafx.h"
#include "CppUnitTest.h"
#include "Board.h"
#include "Card.h"
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



	};
}
