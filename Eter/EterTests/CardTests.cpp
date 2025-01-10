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


    };
}
