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


	};
}
