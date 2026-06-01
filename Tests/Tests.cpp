#include "pch.h"
#include "CppUnitTest.h"
#include "string.h"
#include "../FILOZOP_KINPO/Arithmetic.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Tests_add)
	{
	public:
		
        TEST_METHOD(EqualModules_DifferentSigns)
        {
            FractionNumber a("1.123");
            FractionNumber b("-1.123");

            FractionNumber result = a.add(b);

            FractionNumber expected("0.0");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.123 + (-1.123) should equal 0");
        }

        TEST_METHOD(DifferentLengthFractionalPart)
        {
            FractionNumber a("1.123");
            FractionNumber b("2.32");

            FractionNumber result = a.add(b);

            FractionNumber expected("3.443");
            Assert::AreEqual(expected.toString(), result.toString(), L"1.123 + 2.32 should equal 3.443");
        }

        TEST_METHOD(BothNegative)
        {
            FractionNumber a("-1.123");
            FractionNumber b("-2.32");

            FractionNumber result = a.add(b);

            FractionNumber expected("-3.443");
            Assert::AreEqual(expected.toString(), result.toString(), L"-1.123 + (-2.32) = -3.443");
        }

        TEST_METHOD(NoIntegerPartOneNumber)
        {
            FractionNumber a("0.123");
            FractionNumber b("2.32");

            FractionNumber result = a.add(b);

            FractionNumber expected("2.443");
            Assert::AreEqual(expected.toString(), result.toString(), L"0.123 + 2.32 = 2.443");
        }

        TEST_METHOD(NoIntegerPartBothNumbers)
        {
            FractionNumber a("0.123");
            FractionNumber b("-0.32");

            FractionNumber result = a.add(b);

            FractionNumber expected("-0.197");
            Assert::AreEqual(expected.toString(), result.toString(), L"0.123 + (-0.32) = -0.197");
        }

        TEST_METHOD(ManyDigitsIntegerPartOneNumber)
        {
            FractionNumber a("123.123");
            FractionNumber b("2.32");

            FractionNumber result = a.add(b);

            FractionNumber expected("125.443");
            Assert::AreEqual(expected.toString(), result.toString(), L"123.123 + 2.32 = 125.443");
        }

        TEST_METHOD(ManyDigitsIntegerPartBothNumbers)
        {
            FractionNumber a("123.123");
            FractionNumber b("-112.32");

            FractionNumber result = a.add(b);

            FractionNumber expected("10.803");
            Assert::AreEqual(expected.toString(), result.toString(), L"123.123 + (-112.32) = 10.803");
        }

        TEST_METHOD(NoFractionalPartOneNumber)
        {
            FractionNumber a("1.0");
            FractionNumber b("2.32");

            FractionNumber result = a.add(b);

            FractionNumber expected("3.32");
            Assert::AreEqual(expected.toString(), result.toString(), L"1 + 2.32 = 3.32");
        }

        TEST_METHOD(NoFractionalPartBothNumbers)
        {
            FractionNumber a("1.0");
            FractionNumber b("-2.0");

            FractionNumber result = a.add(b);

            FractionNumber expected("-1");
            Assert::AreEqual(expected.toString(), result.toString(), L"1 + (-2) = -1");
        }

        TEST_METHOD(OneDigitFractionalPartOneNumber)
        {
            FractionNumber a("1.1");
            FractionNumber b("2.32");

            FractionNumber result = a.add(b);

            FractionNumber expected("3.42");
            Assert::AreEqual(expected.toString(), result.toString(), L"1.1 + 2.32 = 3.42");
        }

        TEST_METHOD(OneDigitFractionalPartBothNumbers)
        {
            FractionNumber a("1.1");
            FractionNumber b("2.3");

            FractionNumber result = a.add(b);

            FractionNumber expected("3.4");
            Assert::AreEqual(expected.toString(), result.toString(), L"1.1 + 2.3 = 3.4");
        }

        TEST_METHOD(TwoDigitsFractionalPartBothNumbers)
        {
            FractionNumber a("1.12");
            FractionNumber b("2.23");

            FractionNumber result = a.add(b);

            FractionNumber expected("3.35");
            Assert::AreEqual(expected.toString(), result.toString(), L"1.12 + 2.23 = 3.35");
        }

        TEST_METHOD(ThreeDigitsFractionalPartBothNumbers)
        {
            FractionNumber a("1.123");
            FractionNumber b("2.234");

            FractionNumber result = a.add(b);

            FractionNumber expected("3.357");
            Assert::AreEqual(expected.toString(), result.toString(), L"1.123 + 2.234 = 3.357");
        }

        TEST_METHOD(SecondNumberMoreFractionalDigits)
        {
            FractionNumber a("1.123");
            FractionNumber b("2.2345");

            FractionNumber result = a.add(b);

            FractionNumber expected("3.3575");
            Assert::AreEqual(expected.toString(), result.toString(), L"1.123 + 2.2345 = 3.3575");
        }

        TEST_METHOD(CarryFromFractionalToInteger)
        {
            FractionNumber a("2.99");
            FractionNumber b("0.02");

            FractionNumber result = a.add(b);

            FractionNumber expected("3.01");
            Assert::AreEqual(expected.toString(), result.toString(), L"2.99 + 0.02 = 3.01");
        }

        TEST_METHOD(OneCarryInsideFractionalPart)
        {
            FractionNumber a("1.123");
            FractionNumber b("2.29");

            FractionNumber result = a.add(b);

            FractionNumber expected("3.413");
            Assert::AreEqual(expected.toString(), result.toString(), L"1.123 + 2.29 = 3.413");
        }

        TEST_METHOD(TwoCarriesInsideFractionalPart)
        {
            FractionNumber a("1.123");
            FractionNumber b("2.299");

            FractionNumber result = a.add(b);

            FractionNumber expected("3.422");
            Assert::AreEqual(expected.toString(), result.toString(), L"1.123 + 2.299 = 3.422");
        }

        TEST_METHOD(OneCarryInIntegerPart)
        {
            FractionNumber a("1.123");
            FractionNumber b("9.23");

            FractionNumber result = a.add(b);

            FractionNumber expected("10.353");
            Assert::AreEqual(expected.toString(), result.toString(), L"1.123 + 9.23 = 10.353");
        }

        TEST_METHOD(TwoCarriesInIntegerPart)
        {
            FractionNumber a("199.123");
            FractionNumber b("2.23");

            FractionNumber result = a.add(b);

            FractionNumber expected("201.353");
            Assert::AreEqual(expected.toString(), result.toString(), L"199.123 + 2.23 = 201.353");
        }

        TEST_METHOD(RemoveTrailingZeros)
        {
            FractionNumber a("2.355");
            FractionNumber b("-1.355");

            FractionNumber result = a.add(b);

            FractionNumber expected("1");
            Assert::AreEqual(expected.toString(), result.toString(), L"2.355 + (-1.355) = 1");
        }

        TEST_METHOD(FirstNumberLargerByAbs)
        {
            FractionNumber a("5.01");
            FractionNumber b("-4.99");

            FractionNumber result = a.add(b);

            FractionNumber expected("0.02");
            Assert::AreEqual(expected.toString(), result.toString(), L"5.01 + (-4.99) = 0.02");
        }

        TEST_METHOD(SecondNumberLargerByAbs)
        {
            FractionNumber a("-3.14");
            FractionNumber b("4.5");

            FractionNumber result = a.add(b);

            FractionNumber expected("1.36");
            Assert::AreEqual(expected.toString(), result.toString(), L"-3.14 + 4.5 = 1.36");
        }

        TEST_METHOD(AddZero)
        {
            FractionNumber a("1.123");
            FractionNumber b("0.0");

            FractionNumber result = a.add(b);

            FractionNumber expected("1.123");
            Assert::AreEqual(expected.toString(), result.toString(), L"1.123 + 0 = 1.123");
        }

        TEST_METHOD(BothZeros)
        {
            FractionNumber a("0");
            FractionNumber b("0");

            FractionNumber result = a.add(b);

            FractionNumber expected("0");
            Assert::AreEqual(expected.toString(), result.toString(), L"0 + 0 = 0");
        }
	};
}
