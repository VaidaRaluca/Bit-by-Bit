#include "stdafx.h"  
#include "CppUnitTest.h"  
import card;  
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace eter; 

namespace CardTests
{
    TEST_CLASS(CardTests)
    {
    public:

        TEST_METHOD(Constructor)
        {
            Card card{ 3, "red", true };

            //Assert::AreEqual(3, static_cast<int>(card.GetValue())); 

            //Assert::AreEqual("red", card.GetColor().c_str());


            //Assert::IsTrue(card.GetPosition());  
        }
    };
}
