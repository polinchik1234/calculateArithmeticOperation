#include "Arithmetic.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <fstream>
#include <string>

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

bool FractionNumber::isZero() const {
    for (uint8_t d : this->integerPart) if (d != 0) return false;
    for (uint8_t d : this->fractionPart) if (d != 0) return false;
    return true;
}

// Преобразует число FractionNumber в число типа double
double FractionNumber::convertToDouble(const FractionNumber& fn) {
    double result = 0.0;
    for (size_t i = 0; i < fn.integerPart.size(); ++i)
        result = result * 10.0 + fn.integerPart[i];
    double frac = 0.0;
    double place = 0.1;
    for (size_t i = 0; i < fn.fractionPart.size(); ++i) {
        frac += fn.fractionPart[i] * place;
        place *= 0.1;
    }
    result += frac;
    if (fn.isNegative) result = -result;
    return result;
}

FractionNumber FractionNumber::convertFromDouble(double val, int precision) {
    // Работаем с модулем
    bool neg = val < 0;
    if (neg) val = -val;

    unsigned long long intPart = (unsigned long long)val;
    std::string intPartStr = std::to_string(intPart);
    val -= intPart;

    // Вычисляем множитель для сдвига дробной части
    long double scale = 1.0;
    for (int i = 0; i < precision; ++i) scale *= 10.0L;

    unsigned long long rounded = (unsigned long long)(val * scale + 0.5L);

    // Превращаем полученную округленную дробь в строку цифр
    std::string s = std::to_string(rounded);

    // Если дробь начиналась с нулей, возвращаем эти нули на место
    while ((int)s.size() < precision) s = "0" + s;

    // Склеиваем целую часть и готовую дробную часть через точку
    std::string resultStr = intPartStr + "." + s;

    size_t dot = resultStr.find('.');
    if (dot != std::string::npos) {
        size_t zero_sequence = resultStr.find("00000000", dot);
        if (zero_sequence != std::string::npos && zero_sequence > dot) {
            resultStr = resultStr.substr(0, zero_sequence);
        }
        size_t nine_sequence = resultStr.find("99999999", dot);
        if (nine_sequence != std::string::npos && nine_sequence > dot) {
            resultStr = resultStr.substr(0, nine_sequence);
            for (int i = (int)resultStr.size() - 1; i >= 0; --i) {
                if (resultStr[i] == '.') continue;
                if (resultStr[i] < '9') {
                    resultStr[i]++;
                    break;
                }
                else {
                    resultStr[i] = '0';
                }
            }
        }
    }

    if (!resultStr.empty() && resultStr.back() == '.') {
        resultStr.pop_back();
    }

    // Возвращаем знак минус, если исходное число было отрицательным
    if (neg) resultStr = "-" + resultStr;
    return FractionNumber(resultStr);
}

FractionNumber FractionNumber::powInt(FractionNumber base, unsigned long long exp) {
    FractionNumber result;
    result.integerPart = { 1 }; result.fractionPart = {}; result.isNegative = false;
    while (exp > 0) {
        if (exp % 2 == 1) result = result.mul(base);
        base = base.mul(base);
        exp /= 2;
    }
    return result;
}

double FractionNumber::calcLn(double x) {
    if (x <= 0.0) return 0.0;

    double result = 0.0;
    const double LN_1_1 = 0.09531017980432493;

    while (x > 1.3) { x /= 1.1; result += LN_1_1; }
    while (x < 0.7) { x *= 1.1; result -= LN_1_1; }

    double t = (x - 1.0) / (x + 1.0);
    double t2 = t * t;
    double power = t;
    double sum = 0.0;

    for (int k = 0; k < 200; ++k) {
        double term = power / (2 * k + 1);
        sum += term;
        power *= t2;
        if (term < 1e-19 && term > -1e-19) break;
    }
    return result + 2.0 * sum;
}

double FractionNumber::calcExp(double x) {
    double result = 1.0;
    double term = 1.0;
    for (int k = 1; k < 250; ++k) {
        term *= x / k;
        result += term;
        if (term < 1e-19 && term > -1e-19) break;
    }
    return result;
}

unsigned long long FractionNumber::vectorToInt(const std::vector<uint8_t>& vec) {
    unsigned long long result = 0;
    for (uint8_t d : vec) {
        result = result * 10 + d;
    }
    return result;
}

bool readFile(ifstream& input_file, vector<string>& file_content)
{
    string input_line;

    // Считываем построчно данные из файла до конца файла
    while (getline(input_file, input_line))
    {
        file_content.push_back(input_line);
    }

    // После считывания закрываем файл
    input_file.close();

    // Проверка, удалось ли загрузить данные из файла
    if (!file_content.empty())
    {
        return true;
    }

    // Если не получилось считать данные, возвращаем ошибку о записи файла
    return false;
}

vector<string> splitString(const string& input_data) 
{
    vector<string> splited_string;
    size_t i = 0;
    size_t n = input_data.length();

    // Для каждого символа строки
    while (i < n) {

        // Если символ пробел или табуляция, пропустить
        if (input_data[i] == ' ' || input_data[i] == '\t') {
            i++;
            continue;
        }

        // Если символ не пробел
        // Запоминаем индекс начала подстроки
        size_t start = i;

        // Дойти до конца строки или до следующего пробела
        while (i < n && input_data[i] != ' ' && input_data[i] != '\t') {
            i++;
        }

        // Взять получившуюся подстроку
        string sub = input_data.substr(start, i - start);

        // Добавить её в контейнер
        splited_string.push_back(sub);
    }

    return splited_string;
}

DataErrors parseInputData(const string& input_data, string& operation, FractionNumber& first, FractionNumber& second)
{
    //Разбиваем строку на токены
    vector<string> tokens = splitString(input_data);

    // Если число токенов не равно 3
    if (tokens.size() != 3) {
        return DataErrors::WRONG_INPUT;
    }

    string op = tokens[0];
    string token2 = tokens[1];
    string token3 = tokens[2];

    // Если первый токен - это не sqrt или +, -, *, /, ^:
    if (op != "sqrt" && op != "+" && op != "-" && op != "*" && op != "/" && op != "^") {
        return DataErrors::WRONG_OPERATION;
    }

    // Если второй и третий токен не дробное число
    try {
        FractionNumber tempFirst(token2);
        FractionNumber tempSecond(token3);
    }
    catch (...) {
        return DataErrors::NO_FRACTION;
    }

    FractionNumber num1(token2);
    FractionNumber num2(token3);

    // Для удобства проверки диапазонов переводим в double
    double val1 = num1.convertToDouble(num1);
    double val2 = num2.convertToDouble(num2);


    // Проверка диапазонов для операции возведения в степень
    if (op == "^") {
        if ((val1 == 0.0 && val2 < 0.0) || (val1 < -100.0 || val1 > 100.0 || val2 < -5.0 || val2 > 5.0)) {
            return DataErrors::INCORRECT_RANGE;
        }
    }

    // Если первый токен – sqrt и второй не в диапазону [0, 100000] 
    // или третий не в диапазоне [-10, 0) U (0, 10]
    if (op == "sqrt") {
        if (val1 < 0.0 || val1 > 100000.0 || val2 < -10.0 || val2 > 10.0 || val2 == 0.0) {
            return DataErrors::INCORRECT_RANGE;
        }
    }

    // Если первый токен +,-,/,* и второй или третий токен больше 1000 по модулю
    if (op == "+" || op == "-" || op == "*" || op == "/") {
        if (abs(val1) > 1000.0 || abs(val2) > 1000.0) {
            return DataErrors::INCORRECT_RANGE;
        }
    }

    // Сохраняем в operation значение первого токена
    operation = op;

    // Преобразовываем второй токен в объект FractionNumber и сохраняем в first
    first = num1;

    // Преобразовываем третий токен в объект FractionNumber и сохранем в second
    second = num2;

    // Ошибок нет
    return DataErrors::NO_DATA_ERROR;
}

void writeResultToFile(ofstream& output_file, const FractionNumber& result)
{
    // Если число отрицательное и это не ноль
    if (result.isNegative && !result.isZero())
    {
        output_file << "-";
    }

    // Вывод целой части
    if (result.integerPart.empty())
    {
        output_file << "0";
    }
    else
    {
        for (uint8_t digit : result.integerPart)
        {
            output_file << (int)digit;
        }
    }

    // Если есть дробная часть, пишем точку и саму дробную часть
    if (!result.fractionPart.empty())
    {
        output_file << ".";

        for (uint8_t digit : result.fractionPart)
        {
            output_file << (int)digit;
        }
    }

    output_file.close();
}



FractionNumber FractionNumber::add(const FractionNumber& other)
{
    // Если первое число равно 0, вернуть второе
    if (this->isZero()) return other;
    // Если второе число равно 0, вернуть первое
    if (other.isZero()) return *this;

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

    if (result.isZero()) {
        result.isNegative = false;
    }

    return result;
}

FractionNumber FractionNumber::mul(const FractionNumber& other) {

    FractionNumber result;

    // Если одно из чисел равно 0, вернуть 0
    if (this->isZero() || other.isZero()) {
        result.integerPart = { 0 };
        result.fractionPart = {};
        result.isNegative = false;
        return result;
    }

    // Определяем знак результата
    result.isNegative = (this->isNegative != other.isNegative);

    // Складываем количество цифр в дробных частях
    size_t totalFracLen = this->fractionPart.size() + other.fractionPart.size();

    // Объединяем целую и дробную часть у первого числа
    std::vector<uint8_t> num1 = this->integerPart;
    num1.insert(num1.end(), this->fractionPart.begin(), this->fractionPart.end());

    // Объединяем целую и дробную часть у второго числа
    std::vector<uint8_t> num2 = other.integerPart;
    num2.insert(num2.end(), other.fractionPart.begin(), other.fractionPart.end());

    // Создаем массив для результата размером, равным сумме количества цифр 
    // первого и второго целых чисел. Заполняем все ячейки нулями
    size_t resSize = num1.size() + num2.size();
    std::vector<uint8_t> resDigits(resSize, 0);

    // Берем цифры второго числа, двигаясь справа налево
    for (int j = (int)num2.size() - 1; j >= 0; j--) {
        // Обнуляем перенос
        int carry = 0;

        // Берем цифры первого числа, двигаясь справа налево
        for (int i = (int)num1.size() - 1; i >= 0; i--) {
            // Индекс текущей ячейки в массиве результата
            int currentPos = i + j + 1;

            // Перемножаем текущие цифры
            int prod = num1[i] * num2[j];

            // Прибавляем значение, которое уже лежит в ячейке массива результата, и накопленный перенос
            int sum = prod + carry + resDigits[currentPos];

            // Записываем последнюю цифру
            resDigits[currentPos] = sum % 10;

            // Обновляем перенос
            carry = sum / 10;

            // Если все цифры первого числа закончились
            if (i == 0) {
                // Записываем оставшийся перенос в ячейку слева
                resDigits[currentPos - 1] += carry;
            }
        }
    }

    // Проверяем, есть ли дробная часть
    if (totalFracLen > 0) {
        // Проверяем, можно ли разделить результат на целую и дробную часть
        if (resDigits.size() > totalFracLen) {
            // Определяем целую и дробную часть
            result.fractionPart.assign(resDigits.end() - totalFracLen, resDigits.end());
            result.integerPart.assign(resDigits.begin(), resDigits.end() - totalFracLen);
        }
        // Все цифры находятся в дробной части, целая часть равна 0
        else {
            result.fractionPart.assign(resDigits.begin(), resDigits.end());

            // Дополняем дробную часть ведущими нулями, если массив цифр оказался короче, чем нужно
            while (result.fractionPart.size() < totalFracLen) {
                result.fractionPart.insert(result.fractionPart.begin(), 0);
            }
            result.integerPart = { 0 };
        }
    }
    else {
        // Если дробной части нет
        result.integerPart = resDigits;
        result.fractionPart = {};
    }

    // Убираем ведущие и хвостовые нули
    removeLeadingZeros(result.integerPart);
    removeTrailingZeros(result.fractionPart);

    return result;
}

FractionNumber FractionNumber::div(const FractionNumber& other) {

    // Если делитель равен 0, вернуть ошибку
    if (other.isZero()) {
        throw std::invalid_argument("Division by zero.");
    }

    // Если делимое равно 0, вернуть 0
    if (this->isZero()) {
        return FractionNumber("0");
    }

    // Определяем знак результата
    bool targetNegative = (this->isNegative != other.isNegative);

    std::vector<uint8_t> frac_A = this->fractionPart;
    std::vector<uint8_t> frac_B = other.fractionPart;

    size_t max_frac_len = std::max(frac_A.size(), frac_B.size());

    // Выравниваем дробные части нулями
    appendZerosRight(frac_A, max_frac_len);
    appendZerosRight(frac_B, max_frac_len);

    // Объединяем целую и дробную часть у первого числа
    std::vector<uint8_t> dividend_vector = this->integerPart;
    dividend_vector.insert(dividend_vector.end(), frac_A.begin(), frac_A.end());

    // Объединяем целую и дробную часть у второго числа
    std::vector<uint8_t> divisor_vector = other.integerPart;
    divisor_vector.insert(divisor_vector.end(), frac_B.begin(), frac_B.end());

    // Удаляем ведущие нули у обоих чисел
    removeLeadingZeros(divisor_vector);
    removeLeadingZeros(dividend_vector);

    // Запоминаем исходный размер делимого, чтобы знать, где заканчивается целая часть
    size_t real_dividend_size = dividend_vector.size();

    FractionNumber result;
    result.isNegative = targetNegative;

    std::vector<uint8_t> remainder;
    size_t current_digit_idx = 0;

    FractionNumber rem_fn;
    FractionNumber div_fn;
    div_fn.integerPart = divisor_vector;
    div_fn.fractionPart = {};
    div_fn.isNegative = false;

    // Цикл деления столбиком
    // Выполняется, пока не закончатся цифры в делимом или пока не наберём 16 знаков в дробной части
    while (current_digit_idx < dividend_vector.size() || result.fractionPart.size() < 16) {

        // Определяем, перешли ли мы уже к вычислению дробной части
        bool is_fraction_now = (current_digit_idx >= real_dividend_size);

        // Если цифры в делимом ещё есть - берём текущую, если закончились — сносим ноль
        uint8_t next_digit = 0;
        if (current_digit_idx < dividend_vector.size()) {
            next_digit = dividend_vector[current_digit_idx];
        }
        // Сдвигаем указатель разряда вперед
        current_digit_idx++;

        // Добавляем снесённую цифру в конец текущего остатка и убираем лишние ведущие нули
        remainder.push_back(next_digit);
        removeLeadingZeros(remainder);

        // Считаем, сколько раз делитель поместится в текущий остаток
        int fit_count = 0;
        while (true) {
            bool remainder_is_less = false;

            // Если количество разрядов разное, то меньше то число, у которого вектор короче
            if (remainder.size() != divisor_vector.size()) {
                remainder_is_less = remainder.size() < divisor_vector.size();
            }
            // Если длины векторов одинаковы, сравниваем их поэлементно
            else {
                remainder_is_less = remainder < divisor_vector;
            }
            // Если остаток стал меньше делителя, подбор цифры завершён
            if (remainder_is_less) {
                break;
            }

            // Настраиваем объект остатка под текущий вектор remainder
            rem_fn.integerPart = remainder;
            rem_fn.fractionPart = {};
            rem_fn.isNegative = false;

            // Вычитаем делитель из остатка
            FractionNumber sub_res = rem_fn.sub(div_fn);

            // Обновляем остаток полученной разностью и зачищаем ведущие нули
            remainder = sub_res.integerPart;
            removeLeadingZeros(remainder);

            // Увеличиваем счётчик успешных вычитаний
            fit_count++;
        }

        // Добавляем цифру в целую или дробную часть
        if (!is_fraction_now) {
            result.integerPart.push_back(fit_count);
        }
        else {
            result.fractionPart.push_back(fit_count);
        }

        // Выходим из цикла, если число разделилось нацело
        if (current_digit_idx >= dividend_vector.size() &&
            remainder.size() == 1 && remainder[0] == 0) {
            break;
        }
    }

    // Если целая часть пустая, записываем 0
    if (result.integerPart.empty()) result.integerPart.push_back(0);
    removeLeadingZeros(result.integerPart);

    // Обрабатываем случаи с периодическими дробями
    std::string s = result.toString();
    size_t dot = s.find('.');

    if (dot != std::string::npos && s.length() > dot + 2) {
        char last_char = s.back();

        if (last_char != '0') {
            size_t zero_count = 0;
            for (int i = (int)s.length() - 2; i > (int)dot; i--) {
                if (s[i] == '0') zero_count++;
                else break;
            }

            if (zero_count >= 3) {
                for (size_t i = s.length() - 1 - zero_count; i < s.length() - 1; i++) {
                    s[i] = last_char;
                }

                result.fractionPart.clear();
                for (size_t i = dot + 1; i < s.length(); i++) {
                    result.fractionPart.push_back(s[i] - '0');
                }
            }
        }
    }

    // Оставляем точность до 16 знаков после запятой
    if (result.fractionPart.size() > 16) {
        result.fractionPart.resize(16);
    }

    // Убираем хвостовые нули
    removeTrailingZeros(result.fractionPart);

    return result;
}

FractionNumber FractionNumber::degree(const FractionNumber& exponent) {

    // Если показатель степени равен 0, вернуть 1
    if (exponent.isZero()) {
        FractionNumber res;
        res.integerPart = { 1 };
        res.fractionPart = {};
        res.isNegative = false;
        return res;
    }

    // Если основание степени равно 0
    if (this->isZero()) {
        // Если степень положительная, вернуть 0
        if (!exponent.isNegative) {
            FractionNumber res;
            res.integerPart = { 0 };
            res.fractionPart = {};
            res.isNegative = false;
            return res;
        }
        // Выводим ошибку
        throw std::invalid_argument("Zero raised to a negative power.");
    }

    // Проверяем, равен ли показатель степени единице
    bool otherIsOne = false;
    if (exponent.integerPart.size() == 1 && exponent.integerPart[0] == 1 && !exponent.isNegative) {
        bool onlyZeros = true;
        for (auto d : exponent.fractionPart) if (d != 0) onlyZeros = false;
        if (onlyZeros) otherIsOne = true;
    }
    // Если степень равна 1, возвращаем основание
    if (otherIsOne) return *this;

    // Проверяем, является ли степень целым числом
    bool expIsInteger = true;
    for (auto d : exponent.fractionPart) if (d != 0) { expIsInteger = false; break; }

    
    if (expIsInteger) {

        unsigned long long loopLimit = vectorToInt(exponent.integerPart);

        // Создаем модуль основания
        FractionNumber baseAbs = *this; baseAbs.isNegative = false;
        // Вызываем возведение в степень для модуля числа
        FractionNumber result = powInt(baseAbs, loopLimit);

        // Если степень была отрицательной, получаем обратное число для результата
        if (exponent.isNegative) {
            FractionNumber one; one.integerPart = { 1 };
            result = one.div(result);
        }

        // Определяем знак итогового числа
        // минус сохраняется, если исходное число было отрицательным и степень нечётная
        result.isNegative = this->isNegative && (loopLimit % 2 == 1);
        // Убираем возможные лишние нули на конце дробной части и возвращаем результат
        removeTrailingZeros(result.fractionPart);
        return result;
    }

    // Переводим основание и степень из объектов класса в тип double
    double base = convertToDouble(*this);
    double exp = convertToDouble(exponent);

    // Нельзя возводить отрицательное число в дробную степень
    if (base < 0 && exp != (long long)exp) {
        throw std::invalid_argument("Negative base with non-integer exponent.");
    }

    // Запоминаем, было ли основание отрицательным, и работаем с модулем
    bool baseNeg = base < 0;
    if (baseNeg) base = -base;

    // Вычисляем степень по формуле: x^y = e^(y * ln(x))
    double lnBase = calcLn(base);
    double val = calcExp(exp * lnBase);

    // Конвертируем полученный результат обратно в FractionNumber
    FractionNumber result = convertFromDouble(val, 16); // Заменено на convertFromDouble

    // Восстановление знака
    if (baseNeg) {
        // Преобразуем целую часть степени в число, чтобы проверить её чётность
        unsigned long long intExp = vectorToInt(exponent.integerPart);
        // Минус остаётся только если целая часть степени была нечётной
        result.isNegative = (intExp % 2 == 1);
    }
    // Если основание было положительным, результат всегда положительный
    else {
        result.isNegative = false;
    }

    removeTrailingZeros(result.fractionPart);
    return result;
}

FractionNumber FractionNumber::sqrt(const FractionNumber& other) {

    // Если подкоренное выражение равно 0, вернуть 0
    if (this->isZero()) {
        FractionNumber zero;
        zero.integerPart = { 0 };
        zero.fractionPart = {};
        zero.isNegative = false;
        return zero;
    }

    // Вычисляем обратное число для степени корня
    FractionNumber one("1");
    FractionNumber invExp = one.div(other);

    FractionNumber tempBase = *this;

    // Берем модуль числа
    bool wasNegative = tempBase.isNegative;
    tempBase.isNegative = false;

    // Возводим в степень
    FractionNumber result = tempBase.degree(invExp);

    // Если исходное число под корнем было отрицательным, возвращаем минус
    if (wasNegative) {

        result.isNegative = true;
    }

    return result;
}

int main(int argc, char* argv[])
{
}

