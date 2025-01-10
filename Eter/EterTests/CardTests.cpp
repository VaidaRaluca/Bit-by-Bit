#include "stdafx.h"
#include "CppUnitTest.h"
#include "Card.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace eter;
namespace EterTests
{
    TEST_CLASS(CardTests)
    {
    public:
        TEST_METHOD(TestCardSwap)
        {
            Card testCard{ 4, "red", true }; 
            Card testCard2{ 3, "blue", false };
            swap(testCard, testCard2);
            Assert::AreEqual(uint8_t(3), testCard.GetValue(), L"Card 1's value should be swapped to 3.");
            Assert::AreEqual(std::string("blue"), testCard.GetColor(), L"Card 1's color should be swapped to blue.");
            Assert::IsFalse(testCard.GetPosition(), L"Card 1's position should be swapped to false.");
            Assert::AreEqual(uint8_t(4), testCard2.GetValue(), L"Card 2's value should be swapped to 5.");
            Assert::AreEqual(std::string("red"), testCard2.GetColor(), L"Card 2's color should be swapped to red.");
            Assert::IsTrue(testCard2.GetPosition(), L"Card 2's position should be swapped to true.");
        }

        TEST_METHOD(TestCardMoveConstructor)
        {
            Card originalCard(10, "red", false);

            Card movedCard(std::move(originalCard));

            Assert::AreEqual(uint8_t(10), movedCard.GetValue(), L"Moved card should retain the value 10.");
            Assert::AreEqual(std::string("red"), movedCard.GetColor(), L"Moved card should retain the color 'red'.");
            Assert::IsFalse(movedCard.GetPosition(), L"Moved card should retain the position 'false'.");

            Assert::AreEqual(uint8_t(0), originalCard.GetValue(), L"Original card's value should be reset to 0.");
            Assert::AreEqual(std::string(""), originalCard.GetColor(), L"Original card's color should be empty after the move.");
            Assert::IsTrue(originalCard.GetPosition(), L"Original card's position should be reset to 'true' after the move.");
        }

        TEST_METHOD(TestCardMoveAssignmentOperator)
        {
            Card originalCard(10, "red", false); 
            Card targetCard(5, "blue", true);  

            targetCard = std::move(originalCard);

            Assert::AreEqual(uint8_t(10), targetCard.GetValue(), L"Target card should have the value 10 after the move.");
            Assert::AreEqual(std::string("red"), targetCard.GetColor(), L"Target card should have the color 'red' after the move.");
            Assert::IsFalse(targetCard.GetPosition(), L"Target card should have the position 'false' after the move.");

            Assert::AreEqual(uint8_t(0), originalCard.GetValue(), L"Original card's value should be reset to 0 after the move.");
            Assert::AreEqual(std::string(""), originalCard.GetColor(), L"Original card's color should be empty after the move.");
            Assert::IsTrue(originalCard.GetPosition(), L"Original card's position should be reset to 'true' after the move.");
        }


    };
}
