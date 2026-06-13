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

    TEST_CLASS(Tests_sub)
    {
    public:

        TEST_METHOD(EqualAbsoluteValues_OppositeSigns)
        {
            FractionNumber a("-1.123");
            FractionNumber b("1.123");

            FractionNumber result = a.sub(b);

            FractionNumber expected("-2.246");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"-1.123 - 1.123 should equal -2.246");
        }

        TEST_METHOD(DifferentFractionLengths)
        {
            FractionNumber a("1.123");
            FractionNumber b("2.32");

            FractionNumber result = a.sub(b);

            FractionNumber expected("-1.197");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.123 - 2.32 should equal -1.197");
        }

        TEST_METHOD(BothNegative)
        {
            FractionNumber a("-1.123");
            FractionNumber b("-2.32");

            FractionNumber result = a.sub(b);

            FractionNumber expected("1.197");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"-1.123 - (-2.32) should equal 1.197");
        }

        TEST_METHOD(NoIntegerPart_OneNumber)
        {
            FractionNumber a("0.123");
            FractionNumber b("2.32");

            FractionNumber result = a.sub(b);

            FractionNumber expected("-2.197");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"0.123 - 2.32 should equal -2.197");
        }

        TEST_METHOD(NoIntegerPart_BothNumbers)
        {
            FractionNumber a("0.123");
            FractionNumber b("-0.32");

            FractionNumber result = a.sub(b);

            FractionNumber expected("0.443");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"0.123 - (-0.32) should equal 0.443");
        }

        TEST_METHOD(ManyDigitsIntegerPart_OneNumber)
        {
            FractionNumber a("123.123");
            FractionNumber b("2.32");

            FractionNumber result = a.sub(b);

            FractionNumber expected("120.803");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"123.123 - 2.32 should equal 120.803");
        }

        TEST_METHOD(ManyDigitsIntegerPart_BothNumbers)
        {
            FractionNumber a("123.123");
            FractionNumber b("-112.32");

            FractionNumber result = a.sub(b);

            FractionNumber expected("235.443");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"123.123 - (-112.32) should equal 235.443");
        }

        TEST_METHOD(NoFractionalPart_OneNumber)
        {
            FractionNumber a("1");
            FractionNumber b("2.32");

            FractionNumber result = a.sub(b);

            FractionNumber expected("-1.32");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1 - 2.32 should equal -1.32");
        }

        TEST_METHOD(NoFractionalPart_BothNumbers)
        {
            FractionNumber a("1");
            FractionNumber b("-2");

            FractionNumber result = a.sub(b);

            FractionNumber expected("3");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1 - (-2) should equal 3");
        }

        TEST_METHOD(SingleDigitFraction_OneNumber)
        {
            FractionNumber a("1.1");
            FractionNumber b("2.32");

            FractionNumber result = a.sub(b);

            FractionNumber expected("-1.22");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.1 - 2.32 should equal -1.22");
        }

        TEST_METHOD(SingleDigitFraction_BothNumbers)
        {
            FractionNumber a("1.1");
            FractionNumber b("2.3");

            FractionNumber result = a.sub(b);

            FractionNumber expected("-1.2");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.1 - 2.3 should equal -1.2");
        }

        TEST_METHOD(TwoDigitsFraction_BothNumbers)
        {
            FractionNumber a("1.12");
            FractionNumber b("2.23");

            FractionNumber result = a.sub(b);

            FractionNumber expected("-1.11");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.12 - 2.23 should equal -1.11");
        }

        TEST_METHOD(ThreeDigitsFraction_BothNumbers)
        {
            FractionNumber a("1.123");
            FractionNumber b("2.234");

            FractionNumber result = a.sub(b);

            FractionNumber expected("-1.111");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.123 - 2.234 should equal -1.111");
        }

        TEST_METHOD(SecondNumberHasMoreFractionDigits)
        {
            FractionNumber a("1.123");
            FractionNumber b("2.2345");

            FractionNumber result = a.sub(b);

            FractionNumber expected("-1.1115");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.123 - 2.2345 should equal -1.1115");
        }

        TEST_METHOD(BorrowFromFractionalToInteger)
        {
            FractionNumber a("3.01");
            FractionNumber b("2.99");

            FractionNumber result = a.sub(b);

            FractionNumber expected("0.02");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"3.01 - 2.99 should equal 0.02");
        }

        TEST_METHOD(SingleBorrowInsideFractional)
        {
            FractionNumber a("1.23");
            FractionNumber b("0.05");

            FractionNumber result = a.sub(b);

            FractionNumber expected("1.18");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.23 - 0.05 should equal 1.18");
        }

        TEST_METHOD(DoubleBorrowInsideFractional)
        {
            FractionNumber a("100.123");
            FractionNumber b("99.230");

            FractionNumber result = a.sub(b);

            FractionNumber expected("0.893");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"100.123 - 99.230 should equal 0.893");
        }

        TEST_METHOD(SingleBorrowInIntegerPart)
        {
            FractionNumber a("201.353");
            FractionNumber b("199.231");

            FractionNumber result = a.sub(b);

            FractionNumber expected("2.122");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"201.353 - 199.231 should equal 2.122");
        }

        TEST_METHOD(DoubleBorrowInIntegerPart)
        {
            FractionNumber a("201.353");
            FractionNumber b("2.230");

            FractionNumber result = a.sub(b);

            FractionNumber expected("199.123");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"201.353 - 2.230 should equal 199.123");
        }

        TEST_METHOD(TrailingZerosRemoval)
        {
            FractionNumber a("2.305");
            FractionNumber b("-1.305");

            FractionNumber result = a.sub(b);

            FractionNumber expected("3.61");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"2.305 - (-1.305) should equal 3.61");
        }

        TEST_METHOD(FirstNumberLargerAbsoluteValue)
        {
            FractionNumber a("5.01");
            FractionNumber b("-4.99");

            FractionNumber result = a.sub(b);

            FractionNumber expected("10");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"5.01 - (-4.99) should equal 10");
        }

        TEST_METHOD(SecondNumberLargerAbsoluteValue)
        {
            FractionNumber a("-3.14");
            FractionNumber b("4.5");

            FractionNumber result = a.sub(b);

            FractionNumber expected("-7.64");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"-3.14 - 4.5 should equal -7.64");
        }

        TEST_METHOD(SubtractZero)
        {
            FractionNumber a("1.123");
            FractionNumber b("0");

            FractionNumber result = a.sub(b);

            FractionNumber expected("1.123");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.123 - 0 should equal 1.123");
        }

        TEST_METHOD(SubtractFromZero)
        {
            FractionNumber a("0");
            FractionNumber b("2.32");

            FractionNumber result = a.sub(b);

            FractionNumber expected("-2.32");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"0 - 2.32 should equal -2.32");
        }

        TEST_METHOD(BothZero)
        {
            FractionNumber a("0");
            FractionNumber b("0");

            FractionNumber result = a.sub(b);

            FractionNumber expected("0");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"0 - 0 should equal 0");
        }
    };


    TEST_CLASS(Tests_mul)
    {
    public:

        TEST_METHOD(FirstMultiplierZero)
        {
            FractionNumber a("0");
            FractionNumber b("2.3");

            FractionNumber result = a.mul(b);

            FractionNumber expected("0");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"0 * 2.3 should equal 0");
        }

        TEST_METHOD(SecondMultiplierZero)
        {
            FractionNumber a("1.123");
            FractionNumber b("0");

            FractionNumber result = a.mul(b);

            FractionNumber expected("0");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.123 * 0 should equal 0");
        }

        TEST_METHOD(BothMultipliersZero)
        {
            FractionNumber a("0");
            FractionNumber b("0");

            FractionNumber result = a.mul(b);

            FractionNumber expected("0");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"0 * 0 should equal 0");
        }

        TEST_METHOD(BothPositive)
        {
            FractionNumber a("1.123");
            FractionNumber b("2.32");

            FractionNumber result = a.mul(b);

            FractionNumber expected("2.60536");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.123 * 2.32 should equal 2.60536");
        }

        TEST_METHOD(BothNegative)
        {
            FractionNumber a("-1.123");
            FractionNumber b("-2.32");

            FractionNumber result = a.mul(b);

            FractionNumber expected("2.60536");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"-1.123 * -2.32 should equal 2.60536");
        }

        TEST_METHOD(DifferentSigns)
        {
            FractionNumber a("1.123");
            FractionNumber b("-2.32");

            FractionNumber result = a.mul(b);

            FractionNumber expected("-2.60536");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.123 * -2.32 should equal -2.60536");
        }

        TEST_METHOD(TrailingZerosRemoval)
        {
            FractionNumber a("2.5");
            FractionNumber b("0.4");

            FractionNumber result = a.mul(b);

            FractionNumber expected("1");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"2.5 * 0.4 should equal 1");
        }

        TEST_METHOD(MultiplyByOne)
        {
            FractionNumber a("1.123");
            FractionNumber b("1");

            FractionNumber result = a.mul(b);

            FractionNumber expected("1.123");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.123 * 1 should equal 1.123");
        }

        TEST_METHOD(MultiplyByMinusOne)
        {
            FractionNumber a("1.123");
            FractionNumber b("-1");

            FractionNumber result = a.mul(b);

            FractionNumber expected("-1.123");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.123 * -1 should equal -1.123");
        }

        TEST_METHOD(EqualFractionLength)
        {
            FractionNumber a("1.1234");
            FractionNumber b("2.3214");

            FractionNumber result = a.mul(b);

            FractionNumber expected("2.60786076");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.1234 * 2.3214 should equal 2.60786076");
        }

        TEST_METHOD(NoIntegerPartOneNumber)
        {
            FractionNumber a("0.123");
            FractionNumber b("2.32");

            FractionNumber result = a.mul(b);

            FractionNumber expected("0.28536");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"0.123 * 2.32 should equal 0.28536");
        }

        TEST_METHOD(NoIntegerPartBothNumbers)
        {
            FractionNumber a("0.123");
            FractionNumber b("0.32");

            FractionNumber result = a.mul(b);

            FractionNumber expected("0.03936");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"0.123 * 0.32 should equal 0.03936");
        }

        TEST_METHOD(ManyDigitsIntegerPartOneNumber)
        {
            FractionNumber a("123.123");
            FractionNumber b("2.32");

            FractionNumber result = a.mul(b);

            FractionNumber expected("285.64536");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"123.123 * 2.32 should equal 285.64536");
        }

        TEST_METHOD(ManyDigitsIntegerPartBothNumbers)
        {
            FractionNumber a("123.123");
            FractionNumber b("211.32");

            FractionNumber result = a.mul(b);

            FractionNumber expected("26018.35236");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"123.123 * 211.32 should equal 26018.35236");
        }

        TEST_METHOD(NoFractionalPartOneNumber)
        {
            FractionNumber a("1.123");
            FractionNumber b("2");

            FractionNumber result = a.mul(b);

            FractionNumber expected("2.246");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.123 * 2 should equal 2.246");
        }

        TEST_METHOD(NoFractionalPartBothNumbers)
        {
            FractionNumber a("1");
            FractionNumber b("2");

            FractionNumber result = a.mul(b);

            FractionNumber expected("2");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1 * 2 should equal 2");
        }

        TEST_METHOD(SingleDigitFractionOneNumber)
        {
            FractionNumber a("1.1");
            FractionNumber b("2.32");

            FractionNumber result = a.mul(b);

            FractionNumber expected("2.552");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.1 * 2.32 should equal 2.552");
        }

        TEST_METHOD(SingleDigitFractionBothNumbers)
        {
            FractionNumber a("1.1");
            FractionNumber b("2.3");

            FractionNumber result = a.mul(b);

            FractionNumber expected("2.53");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.1 * 2.3 should equal 2.53");
        }

        TEST_METHOD(TwoDigitsFractionBothNumbers)
        {
            FractionNumber a("1.12");
            FractionNumber b("2.32");

            FractionNumber result = a.mul(b);

            FractionNumber expected("2.5984");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.12 * 2.32 should equal 2.5984");
        }

        TEST_METHOD(ThreeDigitsFractionBothNumbers)
        {
            FractionNumber a("1.123");
            FractionNumber b("2.321");

            FractionNumber result = a.mul(b);

            FractionNumber expected("2.606483");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.123 * 2.321 should equal 2.606483");
        }

        TEST_METHOD(SecondNumberHasMoreFractionDigits)
        {
            FractionNumber a("1.123");
            FractionNumber b("2.3211");

            FractionNumber result = a.mul(b);

            FractionNumber expected("2.6065953");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.123 * 2.3211 should equal 2.6065953");
        }

        TEST_METHOD(CarryFromFractionalToInteger)
        {
            FractionNumber a("0.5");
            FractionNumber b("2.0");

            FractionNumber result = a.mul(b);

            FractionNumber expected("1");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"0.5 * 2.0 should equal 1");
        }

        TEST_METHOD(SingleCarryInsideFractional)
        {
            FractionNumber a("0.25");
            FractionNumber b("0.4");

            FractionNumber result = a.mul(b);

            FractionNumber expected("0.1");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"0.25 * 0.4 should equal 0.1");
        }

        TEST_METHOD(DoubleCarryInsideFractional)
        {
            FractionNumber a("0.99");
            FractionNumber b("0.99");

            FractionNumber result = a.mul(b);

            FractionNumber expected("0.9801");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"0.99 * 0.99 should equal 0.9801");
        }

        TEST_METHOD(SingleCarryInIntegerPart)
        {
            FractionNumber a("50.5");
            FractionNumber b("2.0");

            FractionNumber result = a.mul(b);

            FractionNumber expected("101");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"50.5 * 2.0 should equal 101");
        }

        TEST_METHOD(DoubleCarryInIntegerPart)
        {
            FractionNumber a("199.0");
            FractionNumber b("2.0");

            FractionNumber result = a.mul(b);

            FractionNumber expected("398");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"199.0 * 2.0 should equal 398");
        }
    };

    TEST_CLASS(Tests_div)
    {
    public:

        TEST_METHOD(DivideZeroByNumber)
        {
            FractionNumber a("0");
            FractionNumber b("2.32");

            FractionNumber result = a.div(b);

            FractionNumber expected("0");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"0 / 2.32 should equal 0");
        }

        TEST_METHOD(DivideZeroByNegativeNumber)
        {
            FractionNumber a("0");
            FractionNumber b("-2.32");

            FractionNumber result = a.div(b);

            FractionNumber expected("0");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"0 / (-2.32) should equal 0");
        }

        TEST_METHOD(DivideByZero)
        {
            FractionNumber a("1.123");
            FractionNumber b("0");

            bool errorThrown = false;
            try {
                FractionNumber result = a.div(b);
            }
            catch (const std::invalid_argument&) {
                errorThrown = true;
            }
            catch (...) {
                errorThrown = false;
            }

            Assert::IsTrue(errorThrown, L"1.123 / 0 should throw std::invalid_argument");
        }

        TEST_METHOD(DivideZeroByZero)
        {
            FractionNumber a("0");
            FractionNumber b("0");

            bool errorThrown = false;
            try {
                FractionNumber result = a.div(b);
            }
            catch (const std::invalid_argument&) {
                errorThrown = true;
            }
            catch (...) {
                errorThrown = false;
            }

            Assert::IsTrue(errorThrown, L"0 / 0 should throw std::invalid_argument");
        }

        TEST_METHOD(DivideByOne)
        {
            FractionNumber a("1.123");
            FractionNumber b("1");

            FractionNumber result = a.div(b);

            FractionNumber expected("1.123");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.123 / 1 should equal 1.123");
        }

        TEST_METHOD(DivideByMinusOne)
        {
            FractionNumber a("1.123");
            FractionNumber b("-1");

            FractionNumber result = a.div(b);

            FractionNumber expected("-1.123");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.123 / -1 should equal -1.123");
        }

        TEST_METHOD(DivideNumberByItself)
        {
            FractionNumber a("1.123");
            FractionNumber b("1.123");

            FractionNumber result = a.div(b);

            FractionNumber expected("1");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.123 / 1.123 should equal 1");
        }

        TEST_METHOD(ResultLessThanOne)
        {
            FractionNumber a("1.2");
            FractionNumber b("2.5");

            FractionNumber result = a.div(b);

            FractionNumber expected("0.48");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.2 / 2.5 should equal 0.48");
        }

        TEST_METHOD(BothPositive)
        {
            FractionNumber a("1.123");
            FractionNumber b("2.32");

            FractionNumber result = a.div(b);

            FractionNumber expected("0.484051724137931");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.123 / 2.32 should equal 0.484051724137931");
        }

        TEST_METHOD(BothNegative)
        {
            FractionNumber a("-1.123");
            FractionNumber b("-2.32");

            FractionNumber result = a.div(b);

            FractionNumber expected("0.484051724137931");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"-1.123 / -2.32 should equal 0.484051724137931");
        }

        TEST_METHOD(DifferentSigns)
        {
            FractionNumber a("1.123");
            FractionNumber b("-2.32");

            FractionNumber result = a.div(b);

            FractionNumber expected("-0.484051724137931");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.123 / -2.32 should equal -0.484051724137931");
        }

        TEST_METHOD(TrailingZerosRemoval)
        {
            FractionNumber a("1.5");
            FractionNumber b("0.5");

            FractionNumber result = a.div(b);

            FractionNumber expected("3");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.5 / 0.5 should equal 3");
        }

        TEST_METHOD(EqualFractionLength)
        {
            FractionNumber a("1.1234");
            FractionNumber b("2.3214");

            FractionNumber result = a.div(b);

            FractionNumber expected("0.4839321099336607");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.1234 / 2.3214 should equal 0.4839321099336607");
        }

        TEST_METHOD(NoIntegerPartOneNumber)
        {
            FractionNumber a("0.123");
            FractionNumber b("2.32");

            FractionNumber result = a.div(b);

            FractionNumber expected("0.0530172413793103");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"0.123 / 2.32 should equal 0.0530172413793103");
        }

        TEST_METHOD(NoIntegerPartBothNumbers)
        {
            FractionNumber a("0.123");
            FractionNumber b("0.32");

            FractionNumber result = a.div(b);

            FractionNumber expected("0.384375");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"0.123 / 0.32 should equal 0.384375");
        }

        TEST_METHOD(ManyDigitsIntegerPartOneNumber)
        {
            FractionNumber a("123.123");
            FractionNumber b("2.32");

            FractionNumber result = a.div(b);

            FractionNumber expected("53.0702586206896551");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"123.123 / 2.32 should equal 53.0702586206896551");
        }

        TEST_METHOD(ManyDigitsIntegerPartBothNumbers)
        {
            FractionNumber a("123.123");
            FractionNumber b("211.32");

            FractionNumber result = a.div(b);

            FractionNumber expected("0.5826377058489494");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"123.123 / 211.32 should equal 0.5826377058489494");
        }

        TEST_METHOD(NoFractionalPartOneNumber)
        {
            FractionNumber a("1.123");
            FractionNumber b("2");

            FractionNumber result = a.div(b);

            FractionNumber expected("0.5615");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.123 / 2 should equal 0.5615");
        }

        TEST_METHOD(NoFractionalPartBothNumbers)
        {
            FractionNumber a("1");
            FractionNumber b("2");

            FractionNumber result = a.div(b);

            FractionNumber expected("0.5");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1 / 2 should equal 0.5");
        }

        TEST_METHOD(SingleDigitFractionOneNumber)
        {
            FractionNumber a("1.1");
            FractionNumber b("2.32");

            FractionNumber result = a.div(b);

            FractionNumber expected("0.4741379310344827");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.1 / 2.32 should equal 0.4741379310344827");
        }

        TEST_METHOD(SingleDigitFractionBothNumbers)
        {
            FractionNumber a("1.1");
            FractionNumber b("2.3");

            FractionNumber result = a.div(b);

            FractionNumber expected("0.4782608695652173");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.1 / 2.3 should equal 0.4782608695652173");
        }

        TEST_METHOD(TwoDigitsFractionBothNumbers)
        {
            FractionNumber a("1.12");
            FractionNumber b("2.32");

            FractionNumber result = a.div(b);

            FractionNumber expected("0.4827586206896551");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.12 / 2.32 should equal 0.4827586206896551");
        }

        TEST_METHOD(ThreeDigitsFractionBothNumbers)
        {
            FractionNumber a("1.123");
            FractionNumber b("2.321");

            FractionNumber result = a.div(b);

            FractionNumber expected("0.4838431710469625");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.123 / 2.321 should equal 0.4838431710469625");
        }

        TEST_METHOD(SecondNumberHasMoreFractionDigits)
        {
            FractionNumber a("1.123");
            FractionNumber b("2.3211");

            FractionNumber result = a.div(b);

            FractionNumber expected("0.4838223256214725");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.123 / 2.3211 should equal 0.4838223256214725");
        }

        TEST_METHOD(CarryFromFractionalToInteger)
        {
            FractionNumber a("1.0");
            FractionNumber b("0.5");

            FractionNumber result = a.div(b);

            FractionNumber expected("2");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.0 / 0.5 should equal 2");
        }

        TEST_METHOD(SingleCarryInsideFractional)
        {
            FractionNumber a("0.1");
            FractionNumber b("0.4");

            FractionNumber result = a.div(b);

            FractionNumber expected("0.25");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"0.1 / 0.4 should equal 0.25");
        }

        TEST_METHOD(DoubleCarryInsideFractional)
        {
            FractionNumber a("0.9801");
            FractionNumber b("0.99");

            FractionNumber result = a.div(b);

            FractionNumber expected("0.99");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"0.9801 / 0.99 should equal 0.99");
        }

        TEST_METHOD(SingleCarryInIntegerPart)
        {
            FractionNumber a("38.0");
            FractionNumber b("2.0");

            FractionNumber result = a.div(b);

            FractionNumber expected("19");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"38.0 / 2.0 should equal 19");
        }

        TEST_METHOD(DoubleCarryInIntegerPart)
        {
            FractionNumber a("398.0");
            FractionNumber b("2.0");

            FractionNumber result = a.div(b);

            FractionNumber expected("199");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"398.0 / 2.0 should equal 199");
        }

        TEST_METHOD(DivisionByTwoDecimalPlacesGivesInteger)
        {
            FractionNumber a("1.0");
            FractionNumber b("0.25");

            FractionNumber result = a.div(b);

            FractionNumber expected("4");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.0 / 0.25 should equal 4");
        }

        TEST_METHOD(DivisionByThreeDecimalPlacesGivesInteger)
        {
            FractionNumber a("1.0");
            FractionNumber b("0.125");

            FractionNumber result = a.div(b);

            FractionNumber expected("8");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.0 / 0.125 should equal 8");
        }

        TEST_METHOD(DivisionByTwoDecimalPlacesGivesFiniteDecimal)
        {
            FractionNumber a("0.1");
            FractionNumber b("0.16");

            FractionNumber result = a.div(b);

            FractionNumber expected("0.625");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"0.1 / 0.16 should equal 0.625");
        }

        TEST_METHOD(DivisionByThreeDecimalPlacesGivesFiniteDecimal)
        {
            FractionNumber a("0.1");
            FractionNumber b("0.64");

            FractionNumber result = a.div(b);

            FractionNumber expected("0.15625");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"0.1 / 0.64 should equal 0.15625");
        }

        TEST_METHOD(DivisionByRepeatingDecimal)
        {
            FractionNumber a("1");
            FractionNumber b("0.3333333333333333");

            FractionNumber result = a.div(b);

            FractionNumber expected("3.3333333333333333");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1 / 0.(3) should equal 3.(3)");
        }

        TEST_METHOD(DivisionByOddPower1)
        {
            FractionNumber a("0.6");
            FractionNumber b("0.3");

            FractionNumber result = a.div(b);

            FractionNumber expected("2");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"0.6 / 0.3 should equal 2");
        }

        TEST_METHOD(DivisionByOddPower2)
        {
            FractionNumber a("1.0");
            FractionNumber b("0.5");

            FractionNumber result = a.div(b);

            FractionNumber expected("2");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"1.0 / 0.5 should equal 2");
        }

        TEST_METHOD(DivisionByOddNumber1)
        {
            FractionNumber a("0.12");
            FractionNumber b("0.3");

            FractionNumber result = a.div(b);

            FractionNumber expected("0.4");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"0.12 / 0.3 should equal 0.4");
        }

        TEST_METHOD(DivisionByOddNumber2)
        {
            FractionNumber a("0.28");
            FractionNumber b("0.7");

            FractionNumber result = a.div(b);

            FractionNumber expected("0.4");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"0.28 / 0.7 should equal 0.4");
        }
    };

    TEST_CLASS(Tests_degree)
    {
    public:

        TEST_METHOD(ZeroExponent)
        {
            FractionNumber a("1.123");
            FractionNumber b("0");
            FractionNumber result = a.degree(b);
            FractionNumber expected("1");
            Assert::AreEqual(expected.toString(), result.toString(), L"1.123^0 should equal 1");
        }

        TEST_METHOD(FirstExponent)
        {
            FractionNumber a("1.123");
            FractionNumber b("1.0");
            FractionNumber result = a.degree(b);
            FractionNumber expected("1.123");
            Assert::AreEqual(expected.toString(), result.toString(), L"1.123^1 should equal 1.123");
        }

        TEST_METHOD(NegativeFractionalExponent)
        {
            FractionNumber a("1.123");
            FractionNumber b("-2.32");
            FractionNumber result = a.degree(b);
            FractionNumber expected("0.7640450483426522");
            Assert::AreEqual(expected.toString(), result.toString(), L"1.123^(-2.32) should equal 0.7640450483426522");
        }

        TEST_METHOD(PositiveFractionalExponent)
        {
            FractionNumber a("1.123");
            FractionNumber b("2.32");
            FractionNumber result = a.degree(b);
            FractionNumber expected("1.3088233503628821");
            Assert::AreEqual(expected.toString(), result.toString(), L"1.123^2.32 should equal 1.3088233503628821");
        }

        TEST_METHOD(ZeroPositiveExponent)
        {
            FractionNumber a("0");
            FractionNumber b("2.32");
            FractionNumber result = a.degree(b);
            FractionNumber expected("0");
            Assert::AreEqual(expected.toString(), result.toString(), L"0^2.32 should equal 0");
        }

        TEST_METHOD(ZeroNegativeExponent)
        {
            FractionNumber a("0");
            FractionNumber b("-2.32");
            bool errorThrown = false;
            try {
                FractionNumber result = a.degree(b);
            }
            catch (const std::exception&) {
                errorThrown = true;
            }
            Assert::IsTrue(errorThrown, L"0^(-2.32) should throw an error (division by zero)");
        }

        TEST_METHOD(NegativeBaseOddRoot)
        {
            FractionNumber a("-27.0");
            FractionNumber b("0.33333");
            bool errorThrown = false;
            try {
                FractionNumber result = a.degree(b);
            }
            catch (const std::exception&) {
                errorThrown = true;
            }
            Assert::IsTrue(errorThrown, L"(-27)^0.33333 should throw an error");
        }

        TEST_METHOD(NegativeBaseEvenRoot)
        {
            FractionNumber a("-8");
            FractionNumber b("0.5");
            bool errorThrown = false;
            try {
                FractionNumber result = a.degree(b);
            }
            catch (const std::exception&) {
                errorThrown = true;
            }
            Assert::IsTrue(errorThrown, L"(-8)^0.5 should throw an error (even root of negative number)");
        }

        TEST_METHOD(TrailingZerosRemoval)
        {
            FractionNumber a("9.0");
            FractionNumber b("0.5");
            FractionNumber result = a.degree(b);
            FractionNumber expected("3");
            Assert::AreEqual(expected.toString(), result.toString(), L"9^0.5 should equal 3");
        }

        TEST_METHOD(EqualFractionLength)
        {
            FractionNumber a("1.1234");
            FractionNumber b("2.3214");
            FractionNumber result = a.degree(b);
            FractionNumber expected("1.3101185670438591");
            Assert::AreEqual(expected.toString(), result.toString(), L"1.1234^2.3214 should equal 1.3101185670438591");
        }

        TEST_METHOD(NoIntegerPartOneNumber)
        {
            FractionNumber a("0.123");
            FractionNumber b("2.32");
            FractionNumber result = a.degree(b);
            FractionNumber expected("0.0077371293686742");
            Assert::AreEqual(expected.toString(), result.toString(), L"0.123^2.32 should equal 0.0077371293686742");
        }

        TEST_METHOD(NoIntegerPartBothNumbers)
        {
            FractionNumber a("0.123");
            FractionNumber b("0.32");
            FractionNumber result = a.degree(b);
            FractionNumber expected("0.511410494327142");
            Assert::AreEqual(expected.toString(), result.toString(), L"0.123^0.32 should equal 0.511410494327142");
        }

        TEST_METHOD(ManyDigitsIntegerPartOneNumber)
        {
            FractionNumber a("12.123");
            FractionNumber b("2.32");
            FractionNumber result = a.degree(b);
            FractionNumber expected("326.569366656253692");
            Assert::AreEqual(expected.toString(), result.toString(), L"12.123^2.32 should equal 326.569366656253692");
        }

        TEST_METHOD(NoFractionalPartOneNumber)
        {
            FractionNumber a("1.123");
            FractionNumber b("2");
            FractionNumber result = a.degree(b);
            FractionNumber expected("1.261129");
            Assert::AreEqual(expected.toString(), result.toString(), L"1.123^2 should equal 1.261129");
        }

        TEST_METHOD(NoFractionalPartBothNumbers)
        {
            FractionNumber a("1");
            FractionNumber b("2");
            FractionNumber result = a.degree(b);
            FractionNumber expected("1");
            Assert::AreEqual(expected.toString(), result.toString(), L"1^2 should equal 1");
        }

        TEST_METHOD(SingleDigitFractionOneNumber)
        {
            FractionNumber a("1.1");
            FractionNumber b("2.32");
            FractionNumber result = a.degree(b);
            FractionNumber expected("1.2474726407568808");
            Assert::AreEqual(expected.toString(), result.toString(), L"1.1^2.32 should equal 1.2474726407568808");
        }

        TEST_METHOD(SingleDigitFractionBothNumbers)
        {
            FractionNumber a("1.1");
            FractionNumber b("2.3");
            FractionNumber result = a.degree(b);
            FractionNumber expected("1.2450969688995253");
            Assert::AreEqual(expected.toString(), result.toString(), L"1.1^2.3 should equal 1.2450969688995253");
        }

        TEST_METHOD(TwoDigitsFractionBothNumbers)
        {
            FractionNumber a("1.12");
            FractionNumber b("2.32");
            FractionNumber result = a.degree(b);
            FractionNumber expected("1.3007259737096053");
            Assert::AreEqual(expected.toString(), result.toString(), L"1.12^2.32 should equal 1.3007259737096053");
        }

        TEST_METHOD(ThreeDigitsFractionBothNumbers)
        {
            FractionNumber a("1.123");
            FractionNumber b("2.321");
            FractionNumber result = a.degree(b);
            FractionNumber expected("1.3089751874891016");
            Assert::AreEqual(expected.toString(), result.toString(), L"1.123^2.321 should equal 1.3089751874891016");
        }

        TEST_METHOD(SecondNumberHasMoreFractionDigits)
        {
            FractionNumber a("1.123");
            FractionNumber b("2.3211");
            FractionNumber result = a.degree(b);
            FractionNumber expected("1.3089903721704979");
            Assert::AreEqual(expected.toString(), result.toString(), L"1.123^2.3211 should equal 1.3089903721704979");
        }

        TEST_METHOD(CarryFromFractionalToInteger)
        {
            FractionNumber a("4.0");
            FractionNumber b("0.5");
            FractionNumber result = a.degree(b);
            FractionNumber expected("2");
            Assert::AreEqual(expected.toString(), result.toString(), L"4^0.5 should equal 2");
        }

        TEST_METHOD(SingleCarryInsideFractional)
        {
            FractionNumber a("0.25");
            FractionNumber b("0.5");
            FractionNumber result = a.degree(b);
            FractionNumber expected("0.5");
            Assert::AreEqual(expected.toString(), result.toString(), L"0.25^0.5 should equal 0.5");
        }

        TEST_METHOD(DoubleCarryInsideFractional)
        {
            FractionNumber a("0.9801");
            FractionNumber b("0.5");
            FractionNumber result = a.degree(b);
            FractionNumber expected("0.99");
            Assert::AreEqual(expected.toString(), result.toString(), L"0.9801^0.5 should equal 0.99");
        }

        TEST_METHOD(SingleCarryInIntegerPart)
        {
            FractionNumber a("4.0");
            FractionNumber b("2.0");
            FractionNumber result = a.degree(b);
            FractionNumber expected("16");
            Assert::AreEqual(expected.toString(), result.toString(), L"4^2 should equal 16");
        }

        TEST_METHOD(DoubleCarryInIntegerPart)
        {
            FractionNumber a("99.0");
            FractionNumber b("2.0");
            FractionNumber result = a.degree(b);
            FractionNumber expected("9801");
            Assert::AreEqual(expected.toString(), result.toString(), L"99^2 should equal 9801");
        }

        TEST_METHOD(TableValue1)
        {
            FractionNumber a("11.0");
            FractionNumber b("2.0");
            FractionNumber result = a.degree(b);
            FractionNumber expected("121");
            Assert::AreEqual(expected.toString(), result.toString(), L"11^2 should equal 121");
        }

        TEST_METHOD(TableValue2)
        {
            FractionNumber a("15.0");
            FractionNumber b("2.0");
            FractionNumber result = a.degree(b);
            FractionNumber expected("225");
            Assert::AreEqual(expected.toString(), result.toString(), L"15^2 should equal 225");
        }

        TEST_METHOD(Power2To3)
        {
            FractionNumber a("2.0");
            FractionNumber b("3.0");
            FractionNumber result = a.degree(b);
            FractionNumber expected("8");
            Assert::AreEqual(expected.toString(), result.toString(), L"2^3 should equal 8");
        }

        TEST_METHOD(Power2To5)
        {
            FractionNumber a("2.0");
            FractionNumber b("5.0");
            FractionNumber result = a.degree(b);
            FractionNumber expected("32");
            Assert::AreEqual(expected.toString(), result.toString(), L"2^5 should equal 32");
        }

        TEST_METHOD(Power2To20)
        {
            FractionNumber a("2.0");
            FractionNumber b("20.0");
            FractionNumber result = a.degree(b);
            FractionNumber expected("1048576");
            Assert::AreEqual(expected.toString(), result.toString(), L"2^20 should equal 1048576");
        }

        TEST_METHOD(Power3To5)
        {
            FractionNumber a("3.0");
            FractionNumber b("5.0");
            FractionNumber result = a.degree(b);
            FractionNumber expected("243");
            Assert::AreEqual(expected.toString(), result.toString(), L"3^5 should equal 243");
        }

        TEST_METHOD(Power3To15)
        {
            FractionNumber a("3.0");
            FractionNumber b("15.0");
            FractionNumber result = a.degree(b);
            FractionNumber expected("14348907");
            Assert::AreEqual(expected.toString(), result.toString(), L"3^15 should equal 14348907");
        }
    };


    TEST_CLASS(Tests_sqrt)
    {
    public:

        TEST_METHOD(SqrtOfZero)
        {
            FractionNumber a("0");
            FractionNumber b("2.32");

            FractionNumber result = a.sqrt(b);

            FractionNumber expected("0");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"Root 2.32 of 0 should equal 0");
        }

        TEST_METHOD(PositiveRootDegree)
        {
            FractionNumber a("1.123");
            FractionNumber b("2.32");

            FractionNumber result = a.sqrt(b);

            FractionNumber expected("1.0512727619878441");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"Root 2.32 of 1.123 should equal 1.0512727619878441");
        }

        TEST_METHOD(NegativeRootDegree)
        {
            FractionNumber a("1.123");
            FractionNumber b("-2.32");

            FractionNumber result = a.sqrt(b);

            FractionNumber expected("0.951227917395203");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"Root -2.32 of 1.123 should equal 0.951227917395203");
        }

        TEST_METHOD(TrailingZerosRemoval)
        {
            FractionNumber a("4");
            FractionNumber b("0.5");

            FractionNumber result = a.sqrt(b);

            FractionNumber expected("16");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"Root 0.5 of 4 should equal 16");
        }

        TEST_METHOD(RootDegreeOne)
        {
            FractionNumber a("1.123");
            FractionNumber b("1.0");

            FractionNumber result = a.sqrt(b);

            FractionNumber expected("1.123");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"Root 1 of 1.123 should equal 1.123");
        }

        TEST_METHOD(RootDegreeZero)
        {
            FractionNumber a("1.123");
            FractionNumber b("0");

            bool errorThrown = false;
            try {
                FractionNumber result = a.sqrt(b);
            }
            catch (const std::exception&) {
                errorThrown = true;
            }

            Assert::IsTrue(errorThrown, L"Root 0 of 1.123 should throw an error");
        }

        TEST_METHOD(EqualFractionLength)
        {
            FractionNumber a("1.1234");
            FractionNumber b("2.3214");

            FractionNumber result = a.sqrt(b);

            FractionNumber expected("1.0514023441379918");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"Root 2.3214 of 1.1234 should equal 1.0514023441379918");
        }

        TEST_METHOD(NoIntegerPartOneNumber)
        {
            FractionNumber a("0.123");
            FractionNumber b("2.32");

            FractionNumber result = a.sqrt(b);

            FractionNumber expected("0.4052450516133315");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"Root 2.32 of 0.123 should equal 0.4052450516133315");
        }

        TEST_METHOD(NoIntegerPartBothNumbers)
        {
            FractionNumber a("0.123");
            FractionNumber b("0.32");

            FractionNumber result = a.sqrt(b);

            FractionNumber expected("0.001432034474621");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"Root 0.32 of 0.123 should equal 0.001432034474621");
        }

        TEST_METHOD(ManyDigitsIntegerPartOneNumber)
        {
            FractionNumber a("12.123");
            FractionNumber b("2.32");

            FractionNumber result = a.sqrt(b);

            FractionNumber expected("2.9313881046894776");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"Root 2.32 of 12.123 should equal 2.9313881046894776");
        }

        TEST_METHOD(NoFractionalPartOneNumber)
        {
            FractionNumber a("1.123");
            FractionNumber b("2");

            FractionNumber result = a.sqrt(b);

            FractionNumber expected("1.0597169433391163");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"Root 2 of 1.123 should equal 1.0597169433391163");
        }

        TEST_METHOD(NoFractionalPartBothNumbers)
        {
            FractionNumber a("1");
            FractionNumber b("2");

            FractionNumber result = a.sqrt(b);

            FractionNumber expected("1");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"Root 2 of 1 should equal 1");
        }

        TEST_METHOD(SingleDigitFractionOneNumber)
        {
            FractionNumber a("1.1");
            FractionNumber b("2.32");

            FractionNumber result = a.sqrt(b);

            FractionNumber expected("1.0419375138863967");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"Root 2.32 of 1.1 should equal 1.0419375138863967");
        }

        TEST_METHOD(SingleDigitFractionBothNumbers)
        {
            FractionNumber a("1.1");
            FractionNumber b("2.3");

            FractionNumber result = a.sqrt(b);

            FractionNumber expected("1.0423097964647208");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"Root 2.3 of 1.1 should equal 1.0423097964647208");
        }

        TEST_METHOD(TwoDigitsFractionBothNumbers)
        {
            FractionNumber a("1.12");
            FractionNumber b("2.32");

            FractionNumber result = a.sqrt(b);

            FractionNumber expected("1.0500613292287793");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"Root 2.32 of 1.12 should equal 1.0500613292287793");
        }

        TEST_METHOD(ThreeDigitsFractionBothNumbers)
        {
            FractionNumber a("1.123");
            FractionNumber b("2.321");

            FractionNumber result = a.sqrt(b);

            FractionNumber expected("1.0512501145352349");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"Root 2.321 of 1.123 should equal 1.0512501145352349");
        }

        TEST_METHOD(SecondNumberHasMoreFractionDigits)
        {
            FractionNumber a("1.123");
            FractionNumber b("2.3211");

            FractionNumber result = a.sqrt(b);

            FractionNumber expected("1.0512478508900871");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"Root 2.3211 of 1.123 should equal 1.0512478508900871");
        }

        TEST_METHOD(CarryFromFractionalToInteger)
        {
            FractionNumber a("4.0");
            FractionNumber b("0.5");

            FractionNumber result = a.sqrt(b);

            FractionNumber expected("16");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"Root 0.5 of 4 should equal 16");
        }

        TEST_METHOD(SingleCarryInsideFractional)
        {
            FractionNumber a("0.16");
            FractionNumber b("0.5");

            FractionNumber result = a.sqrt(b);

            FractionNumber expected("0.0256");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"Root 0.5 of 0.16 should equal 0.0256");
        }

        TEST_METHOD(DoubleCarryInsideFractional)
        {
            FractionNumber a("0.25");
            FractionNumber b("0.5");

            FractionNumber result = a.sqrt(b);

            FractionNumber expected("0.0625");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"Root 0.5 of 0.25 should equal 0.0625");
        }

        TEST_METHOD(SingleCarryInIntegerPart)
        {
            FractionNumber a("9.0");
            FractionNumber b("0.5");

            FractionNumber result = a.sqrt(b);

            FractionNumber expected("81");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"Root 0.5 of 9 should equal 81");
        }

        TEST_METHOD(DoubleCarryInIntegerPart)
        {
            FractionNumber a("99.0");
            FractionNumber b("0.5");

            FractionNumber result = a.sqrt(b);

            FractionNumber expected("9801");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"Root 0.5 of 99 should equal 9801");
        }

        TEST_METHOD(SquareRootOfTableValue225)
        {
            FractionNumber a("225.0");
            FractionNumber b("2.0");

            FractionNumber result = a.sqrt(b);

            FractionNumber expected("15");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"Square root of 225 should equal 15");
        }

        TEST_METHOD(SquareRootOfTableValue144)
        {
            FractionNumber a("144");
            FractionNumber b("2.0");

            FractionNumber result = a.sqrt(b);

            FractionNumber expected("12");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"Square root of 144 should equal 12");
        }

        TEST_METHOD(SquareRootOfPowerOfTwo64)
        {
            FractionNumber a("64.0");
            FractionNumber b("2.0");

            FractionNumber result = a.sqrt(b);

            FractionNumber expected("8");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"Square root of 64 should equal 8");
        }

        TEST_METHOD(SquareRootOfPowerOfTwo1024)
        {
            FractionNumber a("1024.0");
            FractionNumber b("2.0");

            FractionNumber result = a.sqrt(b);

            FractionNumber expected("32");

            Assert::AreEqual(expected.toString(), result.toString(),
                L"Square root of 1024 should equal 32");
        }
    };
}
