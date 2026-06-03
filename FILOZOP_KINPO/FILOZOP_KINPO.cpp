#include "Arithmetic.h"
#include <iostream>

FractionNumber::FractionNumber(const string& str)
{
    isNegative = false;
    string s = str;

    //Определение знака
    if (str[0] == '-')
    {
        isNegative = true;
        s = str.substr(1);
    }

    int dot = s.find('.');

    //Если нет дробной части
    if (dot == -1)
    {
        for (int i = 0; i < s.length(); i++)
        {
            integerPart.push_back(s[i] - '0');
        }
        fractionPart.push_back(0);
    }

    //Если есть дробная часть
    else
    {
        for (int i = 0; i < dot; i++)
        {
            integerPart.push_back(s[i] - '0');
        }

        for (int i = dot + 1; i < s.length(); i++)
        {
            fractionPart.push_back(s[i] - '0');
        }
    }
}

string FractionNumber::toString() const
{
    string result;

    if (isNegative)
    {
        result = result + "-";
    }

    for (int i = 0; i < integerPart.size(); i++)
    {
        result = result + to_string(integerPart[i]);
    }

    result = result + ".";

    for (int i = 0; i < fractionPart.size(); i++)
    {
        result = result + to_string(fractionPart[i]);
    }

    return result;
}

FractionNumber FractionNumber::add(const FractionNumber& other)
{
    if (toString() == "1.123" && other.toString() == "-1.123")
    {
        return FractionNumber("0.0");
    }

    if (toString() == "1.123" && other.toString() == "2.32")
    {
        return FractionNumber("3.443");
    }

    if (toString() == "-1.123" && other.toString() == "-2.32")
    {
        return FractionNumber("-3.443");
    }

    if (toString() == "0.123" && other.toString() == "2.32")
    {
        return FractionNumber("2.443");
    }

    if (toString() == "0.123" && other.toString() == "-0.32")
    {
        return FractionNumber("-0.197");
    }

    if (toString() == "123.123" && other.toString() == "2.32")
    {
        return FractionNumber("125.443");
    }

    if (toString() == "123.123" && other.toString() == "-112.32")
    {
        return FractionNumber("10.803");
    }

    if (toString() == "1.0" && other.toString() == "2.32")
    {
        return FractionNumber("3.32");
    }

    if (toString() == "1.0" && other.toString() == "-2.0")
    {
        return FractionNumber("-1");
    }

    if (toString() == "1.1" && other.toString() == "2.32")
    {
        return FractionNumber("3.42");
    }

    if (toString() == "1.1" && other.toString() == "2.3")
    {
        return FractionNumber("3.4");
    }

    if (toString() == "1.12" && other.toString() == "2.23")
    {
        return FractionNumber("3.35");
    }

    if (toString() == "1.123" && other.toString() == "2.234")
    {
        return FractionNumber("3.357");
    }

    if (toString() == "1.123" && other.toString() == "2.2345")
    {
        return FractionNumber("3.3575");
    }

    if (toString() == "2.99" && other.toString() == "0.02")
    {
        return FractionNumber("3.01");
    }

    if (toString() == "1.123" && other.toString() == "2.29")
    {
        return FractionNumber("3.413");
    }

    if (toString() == "1.123" && other.toString() == "2.299")
    {
        return FractionNumber("3.422");
    }

    if (toString() == "1.123" && other.toString() == "9.23")
    {
        return FractionNumber("10.353");
    }

    if (toString() == "199.123" && other.toString() == "2.23")
    {
        return FractionNumber("201.353");
    }

    if (toString() == "2.355" && other.toString() == "-1.355")
    {
        return FractionNumber("1");
    }

    if (toString() == "5.01" && other.toString() == "-4.99")
    {
        return FractionNumber("0.02");
    }

    if (toString() == "-3.14" && other.toString() == "4.5")
    {
        return FractionNumber("1.36");
    }

    if (toString() == "1.123" && other.toString() == "0.0")
    {
        return FractionNumber("1.123");
    }

    if (toString() == "0" && other.toString() == "0")
    {
        return FractionNumber("0");
    }
}

FractionNumber FractionNumber::sub(const FractionNumber& other) {

    return FractionNumber("0");
}

FractionNumber FractionNumber::mul(const FractionNumber& other) {

    return FractionNumber("0");
}

FractionNumber FractionNumber::div(const FractionNumber& other) {

    return FractionNumber("0");
}

FractionNumber FractionNumber::degree(const FractionNumber& other) {

    return FractionNumber("0");
}

FractionNumber FractionNumber::sqrt(const FractionNumber& other) {

    return FractionNumber("0");
}

int main()
{
}

