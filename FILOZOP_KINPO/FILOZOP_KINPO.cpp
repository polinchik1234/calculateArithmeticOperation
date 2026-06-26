/*!
\file
\brief Данный файл содержит заголовочный класс FractionNumber.
*
\mainpage Документация для класса вещественных чисел произвольной точности "FractionNumber"
Данная библиотека предназначена для работы с вещественными числами произвольной точности.
Класс представляет числа в виде динамических векторов
для целой и дробной частей, что позволяет обходить аппаратные ограничения стандартных
типов данных вроде double или float.

Библиотека поддерживает следующие возможности:
- Основные арифметические операции (сложение, вычитание, умножение, деление в столбик).
- Нахождение циклических периодов при делении.
- Извлечение корня заданной степени и возведение в произвольную степень (включая работу с дробными и отрицательными показателями).
- Автоматическую обработку знаков, удаление незначащих нулей и исправление ошибок округления.

Для функционирования программы достаточно стандартной библиотеки шаблонов C++ (STL),
включая модули `<string>` и `<vector>`. Программа разработана на языке С++
с поддержкой современных стандартов и подходит для интеграции в любые консольные
или графические приложения.

Программа должна получать два аргумента командной строки: путь к входному
файлу с исходными данными (числами и математическими операциями) и путь к
выходному файлу для сохранения результатов работы программы.

Пример команды запуска программы:
\code
./FractionNumberCalculator ./input.txt ./output.txt
\endcode

\author Filozop Polina
\date June 2026
\version 1.0
*/
#include "Arithmetic.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <fstream>
#include <string>
#include <numeric>

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

FractionNumber::FractionNumber()
{
    // По умолчанию число считается положительным
    isNegative = false;
}

string FractionNumber::toString() const
{
    string result;

    // Добавляем знак минус, если число отрицательное
    if (isNegative)
    {
        result += "-";
    }

    // Поразрядно собираем целую часть числа
    for (int i = 0; i < integerPart.size(); i++)
    {
        result = result + to_string(integerPart[i]);
    }

    // Добавляем точку между целой и дробной частью
    result = result + ".";

    // Формируем дробную часть числа
    if (fractionPart.empty())
    {
        // Если дробная часть отсутствует, записываем ноль
        result = result + "0";
    }
    else
    {
        // Если дробная часть есть, последовательно переносим все цифры
        for (int i = 0; i < fractionPart.size(); i++)
        {
            result = result + to_string(fractionPart[i]);
        }
    }

    return result;
}

void FractionNumber::appendZerosRight(std::vector<uint8_t>& vec, size_t targetLen)
{
    // Пока размер вектора меньше нужной длины
    while (vec.size() < targetLen)
    {
        // Добавляем ноль в конец
        vec.push_back(0);
    }
}

void FractionNumber::prependZerosLeft(std::vector<uint8_t>& vec, size_t targetLen)
{
    // Пока размер вектора меньше нужной длины
    while (vec.size() < targetLen)
    {
        // Добавляем ноль в начало
        vec.insert(vec.begin(), 0);
    }
}

bool FractionNumber::compareByModule(const FractionNumber& other,
    const std::vector<uint8_t>& f1,
    const std::vector<uint8_t>& f2) const
{
    //Сравниваем целые части по длине
    if (this->integerPart.size() != other.integerPart.size())
    {
        return this->integerPart.size() > other.integerPart.size();
    }

    //Сравниваем целые части по каждой цифре
    for (size_t i = 0; i < this->integerPart.size(); i++)
    {
        if (this->integerPart[i] != other.integerPart[i])
        {
            return this->integerPart[i] > other.integerPart[i];
        }
    }

    //Сравниваем выровненные дробные части
    for (size_t i = 0; i < f1.size(); i++)
    {
        if (f1[i] != f2[i])
        {
            return f1[i] > f2[i];
        }
    }

    return true;
}

void FractionNumber::removeLeadingZeros(std::vector<uint8_t>& vec)
{
    // Пока в векторе больше одного элемента и первый элемент равен 0
    while (vec.size() > 1 && vec[0] == 0)
    {
        // Удаляем этот ноль из начала
        vec.erase(vec.begin());
    }
}

void FractionNumber::removeTrailingZeros(std::vector<uint8_t>& vec)
{
    // Пока вектор не пустой и его самый последний элемент равен 0
    while (vec.size() > 0 && vec.back() == 0)
    {
        // Удаляем ноль с конца
        vec.pop_back();
    }
}

bool FractionNumber::isZero() const
{
    // Если целая часть не равна 0, возвращаем false
    if (!all_of(integerPart.begin(), integerPart.end(), [](uint8_t d) { return d == 0; })) {
        return false;
    }
    // Если дробная часть не равна 0, возвращаем false
    if (!all_of(fractionPart.begin(), fractionPart.end(), [](uint8_t d) { return d == 0; })) {
        return false;
    }
    return true;
}

void FractionNumber::incrementString(std::string& str)
{
    int i = (int)str.size() - 1;

    // Если на самом конце оказалась точка, просто сдвигаем указатель на цифру перед ней
    if (i >= 0 && str[i] == '.')
    {
        --i;
    }

    // Увеличиваем текущую цифру на единицу
    if (i >= 0)
    {
        str[i]++;
    }
}

void FractionNumber::handleFloatingArtifacts(std::string& resultStr)
{
    // Находим позицию точки в строке
    size_t dot = resultStr.find('.');
    if (dot == std::string::npos) return;

    // Поиск длинной последовательности нулей
    size_t zeroSequence = resultStr.find("00000000", dot);
    if (zeroSequence != std::string::npos && zeroSequence > dot)
    {
        // Отсекаем хвост из нулей и последующих случайных цифр
        resultStr.resize(zeroSequence);
    }

    // Поиск длинной последовательности девяток
    size_t nineSequence = resultStr.find("99999999", dot);
    if (nineSequence != std::string::npos && nineSequence > dot)
    {
        // Отрезаем хвост из девяток
        resultStr.resize(nineSequence);

        // Математически округляем оставшееся число вверх
        incrementString(resultStr);
    }

    // Если после всех усечений на конце осталась точка, удаляем её
    if (!resultStr.empty() && resultStr.back() == '.')
    {
        resultStr.pop_back();
    }
}

FractionNumber FractionNumber::convertFromDouble(double val, int precision)
{
    // Работаем с модулем
    bool neg = val < 0;
    if (neg) val = -val;

    // Отделяем целую часть и переводим её в строку
    unsigned long long intPart = (unsigned long long)val;
    std::string intPartStr = std::to_string(intPart);
    val -= intPart;

    // Вычисляем множитель для сдвига дробной части
    long double scale = 1.0;
    for (int i = 0; i < precision; ++i) scale *= 10.0L;

    // Округляем дробную часть до нужного количества знаков
    unsigned long long rounded = (unsigned long long)(val * scale + 0.5L);

    // Превращаем полученную округленную дробь в строку цифр
    std::string s = std::to_string(rounded);

    // Если дробь начиналась с нулей, возвращаем эти нули на место
    while ((int)s.size() < precision) s = "0" + s;

    // Склеиваем целую часть и готовую дробную часть через точку
    std::string resultStr = intPartStr + "." + s;

    // Выносим исправление погрешностей double во внешний метод
    handleFloatingArtifacts(resultStr);

    // Возвращаем знак минус, если исходное число было отрицательным
    if (neg) resultStr = "-" + resultStr;

    // Используем уже готовый конструктор класса
    return FractionNumber(resultStr);
}
    
FractionNumber FractionNumber::powInt(FractionNumber base, unsigned long long exp)
{
    FractionNumber result;
    result.integerPart = { 1 }; result.fractionPart = {}; result.isNegative = false;
    // Алгоритм возведения в степень
    while (exp > 0)
    {
        // Если степень нечётная, умножаем результат на текущее основание
        if (exp % 2 == 1) result = result.mul(base);
        // Возводим базу в квадрат
        base = base.mul(base);
        // Уменьшаем степень в два раза
        exp /= 2;
    }
    return result;
}

double FractionNumber::calcLn(double x)
{
    // Логарифм отрицательных чисел и нуля не существует
    if (x <= 0.0) return 0.0;

    double result = 0.0;
    const double LN_1_1 = 0.09531017980432493;

    // Сжимаем x в рамки от 0.7 до 1.3, чтобы расчеты были точными
    // Если число большое — делим на 1.1 и добавляем шаг к результату
    while (x > 1.3) { x /= 1.1; result += LN_1_1; }
    // Если число маленькое — умножаем на 1.1 и вычитаем шаг
    while (x < 0.7) { x *= 1.1; result -= LN_1_1; }

    // Вычисляем логарифм для x с помощью быстросходящегося ряда
    double t = (x - 1.0) / (x + 1.0);
    double t2 = t * t;
    double power = t;
    double sum = 0.0;

    // Разложение в ряд
    for (int k = 0; k < 200; ++k)
    {
        double term = power / (2 * k + 1);
        sum += term;
        // Меняем степень для следующего шага
        power *= t2;
        // Если слагаемое стало маленьким, выходим из цикла
        if (term < 1e-19 && term > -1e-19) break;
    }
    return result + 2.0 * sum;
}

double FractionNumber::calcExp(double x)
{
    double result = 1.0;
    double term = 1.0;

    // Вычисляем экспоненту через разложение в ряд Маклорена
    for (int k = 1; k < 250; ++k)
    {
        // Формируем член ряда: умножаем на x и делим на факториал
        term *= x / k;

        // Накапливаем сумму членов ряда
        result += term;

        // Проверка на сходимость: если точность достигнута, выходим из цикла
        if (term < 1e-19 && term > -1e-19) break;
    }
    return result;
}

unsigned long long FractionNumber::vectorToInt(const std::vector<uint8_t>& vec)
{
    // Собираем отдельные цифры из вектора в одно целое число
    return std::accumulate(vec.begin(), vec.end(), 0ULL, [](unsigned long long result, uint8_t d) {
        return result * 10 + d;
    });
}

// Преобразует число FractionNumber в число типа double
double FractionNumber::convertToDouble(const FractionNumber& fn)
{
    double result = static_cast<double>(vectorToInt(fn.integerPart));
    double frac = 0.0;
    double place = 0.1;

    // Переводим вектор цифр дробной части в число
    for (size_t i = 0; i < fn.fractionPart.size(); ++i)
    {
        frac += fn.fractionPart[i] * place;
        // Сдвигаем разряд вправо
        place *= 0.1;
    }

    // Складываем целую и дробную части
    result += frac;

    // Если число было отрицательным, добавляем минус
    if (fn.isNegative) result = -result;
    return result;
}

bool readFile(ifstream& inputFile, vector<string>& fileContent)
{
    string inputLine;

    // Считываем построчно данные из файла до конца файла
    while (getline(inputFile, inputLine))
    {
        fileContent.push_back(inputLine);
    }

    // После считывания закрываем файл
    inputFile.close();

    // Проверка, удалось ли загрузить данные из файла
    if (!fileContent.empty())
    {
        return true;
    }

    // Если не получилось считать данные, возвращаем ошибку о записи файла
    return false;
}

vector<string> splitString(const string& inputData)
{
    vector<string> splitString;
    size_t i = 0;
    size_t n = inputData.length();

    // Для каждого символа строки
    while (i < n)
    {

        // Если символ пробел или табуляция, пропустить
        if (inputData[i] == ' ' || inputData[i] == '\t')
        {
            i++;
            continue;
        }

        // Если символ не пробел
        // Запоминаем индекс начала подстроки
        size_t start = i;

        // Дойти до конца строки или до следующего пробела
        while (i < n && inputData[i] != ' ' && inputData[i] != '\t')
        {
            i++;
        }

        // Взять получившуюся подстроку
        string sub = inputData.substr(start, i - start);

        // Добавить её в контейнер
        splitString.push_back(sub);
    }

    return splitString;
}

bool validateRange(double value,
    const std::vector<Range>& includeRanges,
    const std::vector<Range>& excludeRanges)
{
    bool included = false;
    // Проверяем, входит ли значение хотя бы в один из разрешенных интервалов
    for (const Range& r : includeRanges) {
        if (r.include(value)) { included = true; break; }
    }
    // Если значение не попало ни в один разрешенный интервал, валидация не пройдена
    if (!included) return false;
    // Проверяем, не попадает ли значение в какой-либо из запрещенных интервалов
    for (const Range& r : excludeRanges) {
        if (r.include(value)) return false;
    }
    return true;
}

bool checkSqrtSign(double val1, double val2)
{
    // Если подкоренное выражение неотрицательное, извлечение корня любой степени всегда возможно
    if (val1 >= 0.0) return true;
    // Если подкоренное выражение отрицательное, проверяем степень корня: она должна быть строго целым числом
    if (val2 != static_cast<long long>(val2)) return false;
    // Для отрицательного основания степень корня обязательно должна быть нечетной
    return static_cast<long long>(val2) % 2 != 0;
}

DataErrors parseInputData(const std::string& inputData,
    std::string& operation,
    FractionNumber& first,
    FractionNumber& second)
{
    // Разбиваем входную строку на токены по пробельным символам
    std::vector<std::string> tokens = splitString(inputData);
    // Должно быть ровно 3 токена
    if (tokens.size() != 3)
        return DataErrors::WRONG_INPUT;

    const std::string& op = tokens[0];

    // Проверяем, поддерживает ли программа данную математическую операцию
    if (op != "+" && op != "-" && op != "*" &&
        op != "/" && op != "^" && op != "sqrt")
        return DataErrors::WRONG_OPERATION;

    // Пытаемся распарсить строки операндов в объекты FractionNumber
    FractionNumber num1, num2;
    try {
        num1 = FractionNumber(tokens[1]);
        num2 = FractionNumber(tokens[2]);
    }
    catch (...) {
        // Формат чисел некорректен
        return DataErrors::NO_FRACTION;
    }

    // Для проверки диапазонов приводим длинные числа к типу double
    double val1 = num1.convertToDouble(num1);
    double val2 = num2.convertToDouble(num2);

    bool rangesOk = false;

    // Валидация граничных условий для разных типов операций
    if (op == "^") {
        // Ограничения для возведения в степень:
        rangesOk = validateRange(val1, { Range(-100.0,    100.0) })
            && validateRange(val2, { Range(-5.0,        5.0) })
            && !(val1 == 0.0 && val2 < 0.0);
    }
    else if (op == "sqrt") {
        // Ограничения для извлечения корня:
        rangesOk = validateRange(val1, { Range(-100000.0, 100000.0) })
            && validateRange(val2, { Range(-10.0, 10.0) }, { Range(0.0) })
            && checkSqrtSign(val1, val2);
    }
    else {
        // Ограничения для базовых арифметических операций (+, -, *, /):
        rangesOk = validateRange(std::abs(val1), { Range(0.0, 1000.0) })
            && validateRange(std::abs(val2), { Range(0.0, 1000.0) });
    }

    // Если значение не входит в заданные диапазоны
    if (!rangesOk)
        return DataErrors::INCORRECT_RANGE;

    operation = op;
    first = num1;
    second = num2;
    // Ошибок не обнаружено
    return DataErrors::NO_DATA_ERROR;
}

void writeResultToFile(ofstream& outputFile, const FractionNumber& result)
{
   // Записываем готовую строку в файл
   outputFile << result.toString();
   outputFile.close();
}

int FractionNumber::subDiv(std::vector<uint8_t>& remainder, const FractionNumber& divFn)
{
    // Счетчик, определяющий, сколько раз делитель "поместился" в текущем остатке
    int fitCount = 0;

    const std::vector<uint8_t>& divisorVector = divFn.integerPart;

    // Цикл последовательного вычитания делителя из остатка до тех пор, пока остаток не станет меньше делителя
    while (true)
    {
        bool remainderIsLess = false;

        // Сравниваем текущий остаток (remainder) и делитель (divisorVector)
        // Если количество разрядов разное, то меньше то число, у которого вектор короче
        if (remainder.size() != divisorVector.size())
        {
            remainderIsLess = remainder.size() < divisorVector.size();
        }
        // Если длины векторов одинаковы, сравниваем их поэлементно от старшего разряда к младшему
        else
        {
            remainderIsLess = remainder < divisorVector;
        }
        // Если промежуточный остаток стал строго меньше делителя, подбор текущей цифры завершён
        if (remainderIsLess)
        {
            break;
        }

        // Подготовка текущего объекта к выполнению операции вычитания
        // Инициализируем целую часть текущего объекта значением промежуточного остатка
        this->integerPart = remainder;
        this->fractionPart = {};
        this->isNegative = false;

        // Вызываем метод вычитания sub() у текущего объекта
        FractionNumber subRes = this->sub(divFn);
        // Записываем полученную разность обратно в рабочий вектор remainder
        remainder = subRes.integerPart;
        // Удаляем возможные ведущие нули
        this->removeLeadingZeros(remainder);

        // Увеличиваем счётчик успешных вычитаний на единицу
        fitCount++;
    }
    // Возвращаем итоговое количество вхождений
    return fitCount;
}


void FractionNumber::checkPeriod(FractionNumber& result)
{
    // Обрабатываем случаи с периодическими дробями
    std::string s = result.toString();
    size_t dot = s.find('.');

    // Проверяем, что в строке есть точка и хотя бы два знака после нее
    if (dot != std::string::npos && s.length() > dot + 2)
    {
        char lastChar = s.back();

        // Если последний символ не ноль, ищем зацикливание периода
        if (lastChar != '0')
        {
            size_t zeroCount = 0;
            // Считаем количество подряд идущих нулей перед последней цифрой
            for (int i = (int)s.length() - 2; i > (int)dot; i--)
            {
                if (s[i] == '0') zeroCount++;
                else break;
            }

            // Если обнаружено три или более нуля, фиксируем период дробной части
            if (zeroCount >= 3)
            {
                uint8_t targetDigit = lastChar - '0';
                // Заполняем нули в хвосте вектора нужной цифрой
                fill(result.fractionPart.end() - 1 - zeroCount, result.fractionPart.end(), targetDigit);
            }
        }
    }
}

void FractionNumber::prepareDivVectors(const FractionNumber& other,
    std::vector<uint8_t>& dividendVector,
    std::vector<uint8_t>& divisorVector) const
{
    std::vector<uint8_t> fracA = this->fractionPart;
    std::vector<uint8_t> fracB = other.fractionPart;

    size_t maxFracLen = std::max(fracA.size(), fracB.size());

    // Выравниваем дробные части нулями
    const_cast<FractionNumber*>(this)->appendZerosRight(fracA, maxFracLen);
    const_cast<FractionNumber*>(&other)->appendZerosRight(fracB, maxFracLen);

    // Объединяем целую и дробную части
    dividendVector = this->integerPart;
    dividendVector.insert(dividendVector.end(), fracA.begin(), fracA.end());

    divisorVector = other.integerPart;
    divisorVector.insert(divisorVector.end(), fracB.begin(), fracB.end());

    // Удаляем ведущие нули
    const_cast<FractionNumber*>(this)->removeLeadingZeros(divisorVector);
    const_cast<FractionNumber*>(this)->removeLeadingZeros(dividendVector);
}

void FractionNumber::finalizeResult(FractionNumber& result) const
{
    const_cast<FractionNumber*>(this)->removeLeadingZeros(result.integerPart);

    // Проверяем получившийся хвост на периоды
    const_cast<FractionNumber*>(this)->checkPeriod(result);

    // Убираем хвостовые нули
    const_cast<FractionNumber*>(this)->removeTrailingZeros(result.fractionPart);
}

bool FractionNumber::isFractionPartZero(const FractionNumber& fn)
{
    // Проверяем, является ли дробная часть пустой или состоящей только из нулей
    if (!all_of(fn.fractionPart.begin(), fn.fractionPart.end(), [](uint8_t d) { return d == 0; })) {
        return false;
    }

    return true;
}

bool FractionNumber::checkDegreeSpecialCases(const FractionNumber& exponent, FractionNumber& result, bool& isHandled)
{
    isHandled = true;

    // Если показатель степени равен 0, вернуть 1
    if (exponent.isZero())
    {
        FractionNumber res;
        res.integerPart = { 1 };
        res.fractionPart = {};
        res.isNegative = false;
        result = res;
        return true;
    }

    // Если основание степени равно 0
    if (this->isZero())
    {
        // Если степень положительная, вернуть 0
        if (!exponent.isNegative)
        {
            FractionNumber res;
            res.integerPart = { 0 };
            res.fractionPart = {};
            res.isNegative = false;
            result = res;
            return true;
        }
        // Выводим ошибку
        throw std::invalid_argument("Zero raised to a negative power.");
    }

    // Проверяем, равен ли показатель степени единице
    bool otherIsOne = false;
    if (exponent.integerPart.size() == 1 && exponent.integerPart[0] == 1 && !exponent.isNegative)
    {
        bool onlyZeros = isFractionPartZero(exponent);
        if (onlyZeros) otherIsOne = true;
    }
    // Если степень равна 1, возвращаем основание
    if (otherIsOne)
    {
        result = *this;
        return true;
    }

    isHandled = false;
    return false;
}

FractionNumber FractionNumber::addSameSign(const FractionNumber& other, const std::vector<uint8_t>& frac1, const std::vector<uint8_t>& frac2, size_t maxFracLen)
{
    FractionNumber result;
    // Знак результата такой же, как у слагаемых
    result.isNegative = this->isNegative;
    // Перенос в следующий разряд
    int carry = 0;

    // Складываем дробную часть
    result.fractionPart.resize(maxFracLen);
    for (int i = (int)maxFracLen - 1; i >= 0; i--)
    {
        int sum = frac1[i] + frac2[i] + carry;
        // Записываем последнюю цифру суммы
        result.fractionPart[i] = sum % 10;
        // Вычисляем перенос на следующий шаг
        carry = sum / 10;
    }

    // Складываем целую часть
    int i = (int)this->integerPart.size() - 1;
    int j = (int)other.integerPart.size() - 1;
    std::vector<uint8_t> tempInt;

    // Продолжаем, пока не пройдем все цифры обоих чисел или пока есть остаток от переноса
    while (i >= 0 || j >= 0 || carry > 0)
    {
        int sum = carry;
        if (i >= 0) { sum += this->integerPart[i]; i--; }
        if (j >= 0) { sum += other.integerPart[j]; j--; }

        tempInt.push_back(sum % 10);
        carry = sum / 10;
    }
    // Так как цифры добавлялись в конец, переворачиваем вектор для правильного порядка
    std::reverse(tempInt.begin(), tempInt.end());
    result.integerPart = tempInt;

    return result;
}

void FractionNumber::subtractVectors(const std::vector<uint8_t>& A, const std::vector<uint8_t>& B, std::vector<uint8_t>& result, int& borrow)
{
    result.resize(A.size());
    // Поразрядное вычитание в столбик
    for (int i = (int)A.size() - 1; i >= 0; i--)
    {
        int diff = A[i] - B[i] - borrow;
        if (diff < 0)
        {
            // Занимаем 10 у старшего разряда
            diff += 10;
            // Запоминаем заём
            borrow = 1;
        }
        else
        {
            // Заём не потребовался
            borrow = 0;
        }
        result[i] = diff;
    }
}

FractionNumber FractionNumber::subDifferentSign(const FractionNumber& other, const std::vector<uint8_t>& frac1, const std::vector<uint8_t>& frac2, size_t maxFracLen)
{
   FractionNumber result;

    // Находим, какое из чисел больше по модулю.
    bool firstIsBigger = compareByModule(other, frac1, frac2);

    // Проверяем на равенство модулей через результат сравнения
    if (!firstIsBigger && this->integerPart == other.integerPart && frac1 == frac2)
    {
        result.integerPart = { 0 };
        result.fractionPart = {};
        result.isNegative = false;
        return result;
    }

    // Определяем, какое из чисел уменьшаемое, а какое вычитаемое
    const FractionNumber& A = firstIsBigger ? *this : other;
    const FractionNumber& B = firstIsBigger ? other : *this;
    std::vector<uint8_t> fA = firstIsBigger ? frac1 : frac2;
    std::vector<uint8_t> fB = firstIsBigger ? frac2 : frac1;

    // Определяем знак по числу у которого модуль больше
    result.isNegative = A.isNegative;
    int borrow = 0;

    // Вычитаем дробную часть
    subtractVectors(fA, fB, result.fractionPart, borrow);

    // Выравниваем целые части нулями слева
    std::vector<uint8_t> intA = A.integerPart;
    std::vector<uint8_t> intB = B.integerPart;
    size_t maxIntLen = std::max(intA.size(), intB.size());
    prependZerosLeft(intA, maxIntLen);
    prependZerosLeft(intB, maxIntLen);

    // Вычитаем целые части
    std::vector<uint8_t> tempInt;
    subtractVectors(intA, intB, tempInt, borrow);
    result.integerPart = tempInt;

    // Убираем ведущие нули
    removeLeadingZeros(result.integerPart);

    return result;
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
    if (this->isNegative == other.isNegative)
    {
        result = addSameSign(other, frac1, frac2, maxFracLen);
    }
    // Если знаки разные
    else
    {
        result = subDifferentSign(other, frac1, frac2, maxFracLen);
    }

    // Убираем хвостовые нули
    removeTrailingZeros(result.fractionPart);

    return result;
}

FractionNumber FractionNumber::sub(const FractionNumber& other)
{

    FractionNumber modifiedOther = other;

    // Меняем знак на противоположный
    modifiedOther.isNegative = !other.isNegative;

    // Складываем текущее число с изменённым числом через метод add
    FractionNumber result = this->add(modifiedOther);

    if (result.isZero())
    {
        result.isNegative = false;
    }

    return result;
}

FractionNumber FractionNumber::mul(const FractionNumber& other)
{

    FractionNumber result;

    // Если одно из чисел равно 0, вернуть 0
    if (this->isZero() || other.isZero())
    {
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
    for (int j = (int)num2.size() - 1; j >= 0; j--)
    {
        // Обнуляем перенос
        int carry = 0;

        // Берем цифры первого числа, двигаясь справа налево
        for (int i = (int)num1.size() - 1; i >= 0; i--)
        {
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
            if (i == 0)
            {
                // Записываем оставшийся перенос в ячейку слева
                resDigits[currentPos - 1] += carry;
            }
        }
    }

    // Проверяем, есть ли дробная часть
    if (totalFracLen > 0)
    {
        result.fractionPart.assign(resDigits.end() - totalFracLen, resDigits.end());
        result.integerPart.assign(resDigits.begin(), resDigits.end() - totalFracLen);
    }
    else
    {
        // Если дробной части нет
        result.integerPart = resDigits;
        result.fractionPart = {};
    }

    // Убираем ведущие и хвостовые нули
    removeLeadingZeros(result.integerPart);
    removeTrailingZeros(result.fractionPart);

    return result;
}

FractionNumber FractionNumber::div(const FractionNumber& other)
{
    // Если делитель равен 0, вернуть ошибку
    if (other.isZero())
    {
        throw std::invalid_argument("Division by zero.");
    }

    // Если делимое равно 0, вернуть 0
    if (this->isZero())
    {
        return FractionNumber("0");
    }

    // Определяем знак результата
    bool targetNegative = (this->isNegative != other.isNegative);

    std::vector<uint8_t> dividendVector;
    std::vector<uint8_t> divisorVector;

    // Вызов внешней функции для подготовки векторов (выравнивание и слияние)
    prepareDivVectors(other, dividendVector, divisorVector);

    // Запоминаем исходный размер делимого, чтобы знать, где заканчивается целая часть
    size_t realDividendSize = dividendVector.size();

    FractionNumber result;
    result.isNegative = targetNegative;

    std::vector<uint8_t> remainder;
    size_t currentDigitIdx = 0;

    FractionNumber remFn;
    FractionNumber divFn;
    divFn.integerPart = divisorVector;
    divFn.fractionPart = {};
    divFn.isNegative = false;

    // Цикл деления столбиком
    // Выполняется, пока не закончатся цифры в делимом или пока не наберём 16 знаков в дробной части
    while (currentDigitIdx < dividendVector.size() || result.fractionPart.size() < 16)
    {
        // Определяем, перешли ли мы уже к вычислению дробной части
        bool isFractionNow = (currentDigitIdx >= realDividendSize);

        // Если цифры в делимом ещё есть - берём текущую, если закончились — сносим ноль
        uint8_t nextDigit = 0;
        if (currentDigitIdx < dividendVector.size())
        {
            nextDigit = dividendVector[currentDigitIdx];
        }
        // Сдвигаем указатель разряда вперед
        currentDigitIdx++;

        // Добавляем снесённую цифру в конец текущего остатка и убираем лишние ведущие нули
        remainder.push_back(nextDigit);
        removeLeadingZeros(remainder);

        // Получаем количество успешных вхождений через внешнюю функцию
        int fitCount = remFn.subDiv(remainder, divFn);

        // Добавляем цифру в целую или дробную часть
        if (!isFractionNow)
        {
            result.integerPart.push_back(fitCount);
        }
        else
        {
            result.fractionPart.push_back(fitCount);
        }

        // Выходим из цикла, если число разделилось нацело
        if (currentDigitIdx >= dividendVector.size() &&
            remainder.size() == 1 && remainder[0] == 0)
        {
            break;
        }
    }

    // Обработка пустой целой части, ведущих/хвостовых нулей, точности и периодов
    finalizeResult(result);

    return result;
}

FractionNumber FractionNumber::degree(const FractionNumber& exponent)
{
    FractionNumber result;
    bool isHandled = false;

    if (checkDegreeSpecialCases(exponent, result, isHandled))
    {
        return result;
    }

    // Проверяем, является ли степень целым числом
    bool expIsInteger = isFractionPartZero(exponent);

    if (expIsInteger)
    {
        unsigned long long loopLimit = vectorToInt(exponent.integerPart);

        // Создаем модуль основания
        FractionNumber baseAbs = *this;
        baseAbs.isNegative = false;

        // Вызываем возведение в степень для модуля числа
        result = powInt(baseAbs, loopLimit);

        // Если степень была отрицательной, получаем обратное число для результата
        if (exponent.isNegative)
        {
            result = FractionNumber("1").div(result);
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
    if (base < 0 && exp != (long long)exp)
    {
        throw std::invalid_argument("Negative base with non-integer exponent.");
    }

    // Вычисляем степень по формуле: x^y = e^(y * ln(x))
    double lnBase = calcLn(base);
    double val = calcExp(exp * lnBase);

    // Конвертируем полученный результат обратно в FractionNumber
    result = convertFromDouble(val, 16); // Заменено на convertFromDouble

    // Восстановление знака
    result.isNegative = false;

    removeTrailingZeros(result.fractionPart);
    return result;
}

FractionNumber FractionNumber::sqrt(const FractionNumber& other)
{

    // Если подкоренное выражение равно 0, вернуть 0
    if (this->isZero())
    {
        return FractionNumber("0");
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
    if (wasNegative)
    {

        result.isNegative = true;
    }

    return result;
}

void printParseError(DataErrors parseResult)
{
    // Если строка не соответсвуют заявленным требованиям
    if (parseResult == DataErrors::WRONG_INPUT)
    {
        cerr << "Error: Input characters do not match the required data template." << endl;
    }
    // Если указана неизвестная или неподдерживаемая математическая операция
    else if (parseResult == DataErrors::WRONG_OPERATION)
    {
        cerr << "Error: Unsupported arithmetic operation." << endl;
    }
    // Если переданные токены не получается преобразовать в объекты чисел
    else if (parseResult == DataErrors::NO_FRACTION)
    {
        cerr << "Error: Provided characters do not form a valid fractional number." << endl;
    }
    // Если входные аргументы вышли за рамки ограничений
    else if (parseResult == DataErrors::INCORRECT_RANGE)
    {
        cerr << "Error: Passed arguments are out of the allowed range." << endl;
    }
}

FractionNumber calculateResult(const string& operation, FractionNumber& first, const FractionNumber& second)
{
    FractionNumber result;

    // В зависимости от переданного знака вызываем нужный метод вычисления
    if (operation == "+") result = first.add(second);
    else if (operation == "-") result = first.sub(second);
    else if (operation == "*") result = first.mul(second);
    else if (operation == "/") result = first.div(second);
    else if (operation == "^") result = first.degree(second);
    else if (operation == "sqrt") result = first.sqrt(second);

    return result;
}

/**
 * @brief Главная функция программы для выполнения арифметических операций произвольной точности.
 * @details Функция координирует весь жизненный цикл работы приложения:
 * 1. Проверяет параметры запуска (аргументы командной строки).
 * 2. Считывает математическое выражение из входного текстового файла (строго 1 строка).
 * 3. Выполняет лексический анализ и валидацию данных (парсинг строки).
 * 4. Вычисляет результат операции с помощью класса FractionNumber.
 * 5. Формирует выходной файл "result.txt" в указанной директории и записывает туда ответ.
 *
 * @param[in] argc Количество аргументов командной строки. Ожидается строго 3.
 * @param[in] argv Массив указателей на строки-аргументы:
 * - argv[0]: Путь к исполняемому файлу программы.
 * - argv[1]: Путь к входному текстовому файлу с выражением.
 * - argv[2]: Путь к выходному каталогу для сохранения "result.txt".
 *
 * @return Код завершения программы:
 * - 0: Программа успешно завершила работу, результат сохранен.
 * - 1: Произошла ошибка (неверные аргументы, ошибка чтения/записи файла,
 * неверный формат входных данных или математическая ошибка в ходе вычислений).
 */
int main(int argc, char* argv[])
{
    // Если количество аргументов не равно 3
    if (argc != 3)
    {
        // Вывести ошибку о неправильном указании параметров запуска
        cerr << "Error: Invalid program launch parameters!" << endl;
        cerr << "Usage: " << argv[0] << " <path_to_input_file> <path_to_output_directory>" << endl;
        return 1;
    }

    // Считать входной файл
    ifstream inputFile(argv[1]);

    // Если файл не удалось открыть
    if (!inputFile.is_open())
    {
        // Выводим ошибку о некорректном входном файле
        cerr << "Error: Incorrect input file. Failed to open: " << argv[1] << endl;
        return 1;
    }

    vector<string> fileContent;

    // Если не удалось считать данные из входного файла
    if (!readFile(inputFile, fileContent))
    {
        // Выводим ошибку о невозможности считать данные из файла
        cerr << "Error: Unable to read data from the file or the file is empty." << endl;
        return 1;
    }

    // Если входные данные не соответствуют требованиям
    if (fileContent.size() != 1)
    {
        // Выводим ошибку о неверном количестве строк в файле
        cerr << "Error: Invalid number of lines in the file. Exactly 1 line is expected." << endl;
        return 1;
    }

    string targetLine = fileContent[0];

    string operation;
    FractionNumber first;
    FractionNumber second;

    // Проверяем строку из файла на корректность данных и соответствие диапазону
    DataErrors parseResult = parseInputData(targetLine, operation, first, second);

    if (parseResult != DataErrors::NO_DATA_ERROR)
    {
        // Вызов внешней функции для вывода конкретной ошибки парсинга
        printParseError(parseResult);
        return 1;
    }

    FractionNumber result;
    bool hasRuntimeError = false;

    try
    {
        result = calculateResult(operation, first, second);
    }
    catch (const std::exception& e)
    {
        cerr << "Runtime Error: " << e.what() << endl;
        hasRuntimeError = true; // Запоминаем ошибку, чтобы корректно выйти после скобки
    }

    // Если во время вычислений упало исключение, выходим здесь (скобка выше теперь позеленеет)
    if (hasRuntimeError)
    {
        return 1;
    }

    // Записываем результат в выходной файл
    string outputPath = string(argv[2]) + "/result.txt";
    ofstream outputFile(outputPath);

    if (!outputFile.is_open())
    {
        cerr << "Error: Failed to create or open the output file at: " << outputPath << endl;
        return 1;
    }

    writeResultToFile(outputFile, result);

    cout << "The program completed successfully. The result has been saved." << endl;
    return 0;
}

