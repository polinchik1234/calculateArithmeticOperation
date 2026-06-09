#include "Arithmetic.h"
#include <iostream>
#include <algorithm>

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

void FractionNumber::removeTrailingZeros(std::vector<uint8_t>& vec) const {
    while (vec.size() > 0 && vec.back() == 0) {
        vec.pop_back();
    }
}

FractionNumber FractionNumber::add(const FractionNumber& other)
{
    FractionNumber result;

    // Дополняем более короткую дробную часть нулями справа до максимальной длины
    size_t maxFracLen = std::max(this->fractionPart.size(), other.fractionPart.size());
    std::vector<uint8_t> frac1 = this->fractionPart;
    std::vector<uint8_t> frac2 = other.fractionPart;
    appendZerosRight(frac1, maxFracLen);
    appendZerosRight(frac2, maxFracLen);

    // Если знаки одинаковые
    if (this->isNegative == other.isNegative) {
        result.isNegative = this->isNegative;
        int carry = 0;

        // Складываем дробную часть
        result.fractionPart.resize(maxFracLen);
        for (int i = (int)maxFracLen - 1; i >= 0; i--) {
            int sum = frac1[i] + frac2[i] + carry;
            result.fractionPart[i] = sum % 10;
            carry = sum / 10;
        }

        // Складываем целую часть
        int i = (int)this->integerPart.size() - 1;
        int j = (int)other.integerPart.size() - 1;
        std::vector<uint8_t> tempInt;

        while (i >= 0 || j >= 0 || carry > 0) {
            int sum = carry;
            if (i >= 0) { sum += this->integerPart[i]; i--; }
            if (j >= 0) { sum += other.integerPart[j]; j--; }

            tempInt.push_back(sum % 10);
            carry = sum / 10;
        }

        std::reverse(tempInt.begin(), tempInt.end());
        result.integerPart = tempInt;
    }
    // Если знаки разные
    else {
        // Сравниваем числа по модулю
        if (this->integerPart == other.integerPart && frac1 == frac2) {
            result.integerPart = { 0 };
            result.fractionPart = {};
            result.isNegative = false;
            return result;
        }

        // Находим, какое из чисел больше
        bool firstIsBigger = compareByModule(other, frac1, frac2);

        // Определяем, какое из чисел уменьшаемое
        const FractionNumber& A = firstIsBigger ? *this : other;
        // Определяем, какое из чисел вычитаемое
        const FractionNumber& B = firstIsBigger ? other : *this;
        std::vector<uint8_t> fA = firstIsBigger ? frac1 : frac2;
        std::vector<uint8_t> fB = firstIsBigger ? frac2 : frac1;

        // Определяем знак по числу у которого модуль больше
        result.isNegative = A.isNegative;
        int borrow = 0;

        // Вычитаем дробную часть
        result.fractionPart.resize(maxFracLen);
        for (int k = (int)maxFracLen - 1; k >= 0; k--) {
            int diff = fA[k] - fB[k] - borrow;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            }
            else {
                borrow = 0;
            }
            result.fractionPart[k] = diff;
        }

        // Выравниваем целые части нулями слева
        std::vector<uint8_t> intA = A.integerPart;
        std::vector<uint8_t> intB = B.integerPart;
        size_t maxIntLen = std::max(intA.size(), intB.size());
        prependZerosLeft(intA, maxIntLen);
        prependZerosLeft(intB, maxIntLen);

        // Вычитаем целые части
        std::vector<uint8_t> tempInt;
        for (int i = (int)maxIntLen - 1; i >= 0; i--) {
            int diff = intA[i] - intB[i] - borrow;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            }
            else {
                borrow = 0;
            }
            tempInt.push_back(diff);
        }

        std::reverse(tempInt.begin(), tempInt.end());
        result.integerPart = tempInt;

        // Убираем ведущие нули
        removeLeadingZeros(result.integerPart);
    }

    // Убираем хвостовые нули
    removeTrailingZeros(result.fractionPart);

    return result;
}

FractionNumber FractionNumber::sub(const FractionNumber& other) {

    FractionNumber modifiedOther = other;

    // Меняем знак на противоположный
    modifiedOther.isNegative = !other.isNegative;

    // Складываем текущее число с изменённым числом через метод add
    FractionNumber result = this->add(modifiedOther);

    return result;
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

