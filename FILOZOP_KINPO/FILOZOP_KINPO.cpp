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

    if (fractionPart.empty())
    {
        result = result + "0";
    }
    else
    {
        for (int i = 0; i < fractionPart.size(); i++)
        {
            result = result + to_string(fractionPart[i]);
        }
    }

    return result;
}

void FractionNumber::appendZerosRight(std::vector<uint8_t>& vec, size_t targetLen) const {
    while (vec.size() < targetLen) {
        vec.push_back(0);
    }
}

void FractionNumber::prependZerosLeft(std::vector<uint8_t>& vec, size_t targetLen) const {
    while (vec.size() < targetLen) {
        vec.insert(vec.begin(), 0);
    }
}

bool FractionNumber::compareByModule(const FractionNumber& other,
    const std::vector<uint8_t>& f1,
    const std::vector<uint8_t>& f2) const
{
    //Сравниваем целые части по длине
    if (this->integerPart.size() != other.integerPart.size()) {
        return this->integerPart.size() > other.integerPart.size();
    }

    //Сравниваем целые части по каждой цифре
    for (size_t i = 0; i < this->integerPart.size(); i++) {
        if (this->integerPart[i] != other.integerPart[i]) {
            return this->integerPart[i] > other.integerPart[i];
        }
    }

    //Сравниваем выровненные дробные части
    for (size_t i = 0; i < f1.size(); i++) {
        if (f1[i] != f2[i]) {
            return f1[i] > f2[i];
        }
    }

    return true;
}

void FractionNumber::removeLeadingZeros(std::vector<uint8_t>& vec) const {
    while (vec.size() > 1 && vec[0] == 0) {
        vec.erase(vec.begin());
    }
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

