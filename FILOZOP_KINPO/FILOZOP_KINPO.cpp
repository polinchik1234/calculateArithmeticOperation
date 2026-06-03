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
        return FractionNumber("0");
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

