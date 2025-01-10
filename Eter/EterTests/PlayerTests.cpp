#include "stdafx.h"
#include "CppUnitTest.h"
#include "Player.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace eter;
namespace EterTests
{
    TEST_CLASS(PlayerTests)
    {
    public:
        TEST_METHOD(TestPlayerConstructor)
        {
            std::string name = "TestPlayer";
            std::string color = "red";
            Player player(name, color);
            Assert::AreEqual(name, player.GetName(), L"The player's name should match the name passed to the constructor.");
            Assert::AreEqual(color, player.GetColor(), L"The player's color should match the color passed to the constructor.");
            Assert::AreEqual(uint32_t(0), player.GetScore(), L"The player's initial score should be 0.");
            Assert::IsTrue(player.GetCardsInHand().empty(), L"The player's hand should be empty upon construction.");
            Assert::IsTrue(player.GetPlayedCards().empty(), L"The player's played cards should be empty upon construction.");
            Assert::IsTrue(player.GetEliminatedCards().empty(), L"The player's eliminated cards should be empty upon construction.");
            Assert::IsFalse(player.GetHasUsedIllusion(), L"The player's hasUsedIllusion flag should be false upon construction.");
        }

        TEST_METHOD(TestPlaceCard)
        {
            Board board;
            Player player{ "TestPlayer", "red" };
            Card testCard{ 3, "red", true }; 
            size_t x = 2, y = 2;
            player.AddCardToHand(testCard);
            Assert::IsTrue(std::find(player.GetCardsInHand().begin(), player.GetCardsInHand().end(), testCard) != player.GetCardsInHand().end(),
                L"The card should be in the player's hand before placing it.");
            bool result = player.placeCard(x, y, testCard, board);
            Assert::IsTrue(result, L"The card should be successfully placed on the board.");
            Assert::IsFalse(board.isEmptyCell(x, y), L"The cell (2, 2) should not be empty after placing the card.");
            Assert::IsTrue(std::find(player.GetCardsInHand().begin(), player.GetCardsInHand().end(), testCard) == player.GetCardsInHand().end(),
                L"The card should no longer be in the player's hand after placing it.");
            Assert::IsTrue(std::find(player.GetPlayedCards().begin(), player.GetPlayedCards().end(), testCard) != player.GetPlayedCards().end(),
                L"The card should now be in the player's played cards.");
        }

        TEST_METHOD(TestUseIllusion)
        {
            Board board;
            Player player{ "TestPlayer", "blue" };
            Card illusion{ 3, "blue", true };
            size_t x = 1, y = 1;
            player.AddCardToHand(illusion);
            player.useIllusion(x, y, board, illusion);
            Assert::IsFalse(board.isEmptyCell(x, y), L"The cell (1, 1) should not be empty after placing the illusion.");
            Assert::AreEqual(std::string("blue"), board.GetGrid()[x][y]->top().GetColor(), L"The color of the card on the board should be blue.");
            Assert::AreEqual(static_cast<int>(3), static_cast<int>(board.GetGrid()[x][y]->top().GetValue()), L"The value of the card on the board should be 3.");
            Assert::IsFalse(illusion.GetPosition(), L"The illusion card's position should be face down after being placed.");
            Assert::IsTrue(player.GetHasUsedIllusion(), L"The player's hasUsedIllusion flag should be true after using the illusion.");
        }

        TEST_METHOD(TestRemovePlayedCard)
        {
            Player player{ "TestPlayer", "red" };
            Card testCard{ 2,"red", true };
            player.AddPlayedCard(testCard);
            Assert::IsTrue(std::find(player.GetPlayedCards().begin(), player.GetPlayedCards().end(), testCard) != player.GetPlayedCards().end(),
                L"The card should be in the player's played cards.");
            player.RemovePlayedCard(testCard);
            Assert::IsTrue(std::find(player.GetPlayedCards().begin(), player.GetPlayedCards().end(), testCard) == player.GetPlayedCards().end(),
                L"The card should no longer be in the player's played cards.");
        }

        TEST_METHOD(TestPlaceETERCard)
        {
            Board board;
            Player player{ "TestPlayer", "red" };
            Card testCard{ 5, "red", true }; 
            Card testCard2{ 3, "red", true }; 
            size_t x = 2, y = 2;

            player.AddCardToHand(testCard);
            Assert::IsTrue(std::find(player.GetCardsInHand().begin(), player.GetCardsInHand().end(), testCard) != player.GetCardsInHand().end(),
                L"The ETER card should be in the player's hand before placing it.");

            bool result = player.placeCard(x, y, testCard, board);
            Assert::IsTrue(result, L"The ETER card should be successfully placed on an empty space.");
            Assert::IsFalse(board.isEmptyCell(x, y), L"The cell (2, 2) should not be empty after placing the ETER card.");
            Assert::IsTrue(std::find(player.GetCardsInHand().begin(), player.GetCardsInHand().end(), testCard) == player.GetCardsInHand().end(),
                L"The ETER card should no longer be in the player's hand after placing it.");
            Assert::IsTrue(std::find(player.GetPlayedCards().begin(), player.GetPlayedCards().end(), testCard) != player.GetPlayedCards().end(),
                L"The ETER card should now be in the player's played cards.");

            player.AddCardToHand(testCard2);
            Assert::IsTrue(std::find(player.GetCardsInHand().begin(), player.GetCardsInHand().end(), testCard2) != player.GetCardsInHand().end(),
                L"The second card should be in the player's hand before attempting to place it.");

            result = player.placeCard(x, y, testCard2, board);
            Assert::IsFalse(result, L"The second card should not be placed on top of the ETER card.");
            Assert::IsTrue(board.GetGrid()[x][y]->top() == testCard, L"The top card on the stack should still be the ETER card.");
            Assert::IsTrue(std::find(player.GetCardsInHand().begin(), player.GetCardsInHand().end(), testCard2) != player.GetCardsInHand().end(),
                L"The second card should still be in the player's hand after the failed placement.");
            Assert::IsTrue(std::find(player.GetPlayedCards().begin(), player.GetPlayedCards().end(), testCard2) == player.GetPlayedCards().end(),
                L"The second card should not be in the player's played cards after the failed placement.");
        }

    };
}
