#pragma once
#include <string>
#include <vector>
using namespace std;

/**
 * @class FractionNumber
 * @brief Класс для работы с вещественными числами произвольной точности.
 * * Класс представляет число в виде двух векторов динамической точности для целой
 * и дробной частей, а также флага знака. Поддерживает основные арифметические
 * операции, возведение в степень и извлечение корня.
 */
class FractionNumber {
private:
	/** @brief Вектор цифр целой части числа */
	vector<uint8_t> integerPart;
	/** @brief Вектор цифр дробной части числа */
	vector<uint8_t> fractionPart;
	/** @brief Флаг знака числа.
	true, если число отрицательное;
	false, если положительное или ноль. */
	bool isNegative;

     /**
	 * @brief Дополняет вектор нулями справа до заданной длины.
	 * @param[in,out] vec Модифицируемый вектор, дополняемый нулями.
	 * @param[in] targetLen Целевая длина вектора.
	 */
	static void appendZerosRight(std::vector<uint8_t>& vec, size_t targetLen);
	/**
	 * @brief Дополняет вектор нулями слева до заданной длины.
	 * @param[in,out] vec Модифицируемый вектор, дополняемый нулями.
	 * @param[in] targetLen Целевая длина вектора.
	 */
	static void prependZerosLeft(std::vector<uint8_t>& vec, size_t targetLen);
	/**
	*@brief Сравнивает текущее число с другим по модулю с учетом выровненных дробных частей.
	* @param[in] other Другое число для сравнения.
	* @param[in] f1 Выровненная дробная часть текущего числа.
	* @param[in] f2 Выровненная дробная часть другого числа.
	* @return true, если модуль текущего числа меньше модуля other; иначе false.
	*/
	bool compareByModule(const FractionNumber& other,
		const std::vector<uint8_t>& f1,
		const std::vector<uint8_t>& f2) const;
	/**
	 * @brief Удаляет незначащие лидирующие нули из целой части.
	 * @param[in,out] vec Модифицируемый вектор цифр целой части.
	 */
	static void removeLeadingZeros(std::vector<uint8_t>& vec);
	/**
	 * @brief Удаляет незначащие хвостовые нули из дробной части.
	 * @param[in,out] vec Модифицируемый вектор цифр дробной части.
	 */
	static void removeTrailingZeros(std::vector<uint8_t>& vec);
	/**
	 * @brief Проверяет, является ли число строго нулем.
	 * @return true, если число равно нулю.
	 */
	bool isZero() const;
	/**
	 * @brief Конвертирует значение типа double в объект FractionNumber с заданной точностью.
	 * @param[in] val Исходное значение double.
	 * @param[in] precision Количество знаков после запятой.
	 * @return Объект FractionNumber, эквивалентный val.
	 */
	FractionNumber convertFromDouble(double val, int precision);
	/**
	 * @brief Возводит объект FractionNumber в целую степень.
	 * @param[in] base Основание степени.
	 * @param[in] exp Целочисленный показатель степени.
	 * @return Результат возведения в степень.
	 */
	FractionNumber powInt(unsigned long long exp) const;
	/**
	 * @brief Вычисляет натуральный логарифм числа.
	 * @param[in] x Исходное число.
	 * @return Значение ln(x).
	 */
	static double calcLn(double x);
	/**
	 * @brief Вычисляет экспоненту числа.
	 * @param[in] x Показатель экспоненты.
	 * @return Значение e^x.
	 */
	static double calcExp(double x);
	/**
	 * @brief Конвертирует вектор цифр в беззнаковое число типа unsigned long long.
	 * @param[in] vec Вектор цифр.
	 * @return Полученное числовое значение.
	 */
	static unsigned long long vectorToInt(const std::vector<uint8_t>& vec);
	/**
	 * @brief Дружественная функция для форматированного вывода результата в файл.
	 * @param[in,out] output_file Поток вывода в файл.
	 * @param[in] result Выводимый объект FractionNumber.
	 */
	friend void writeResultToFile(ofstream& output_file, const FractionNumber& result);
	/**
	 * @brief Метод поразрядного деления для подбора цифры частного.
	 * @param[in,out] remainder Текущий рабочий остаток деления в виде вектора цифр.
	 * @param[in] divFn Объект делителя для выполнения операции вычитания.
	 * @return int Количество успешных вычитаний.
	 */
	int subDiv(std::vector<uint8_t>& remainder, const FractionNumber& divFn);
	/**
	 * @brief Проверяет дробную часть результата на наличие циклических периодов при делении.
	 */
	void checkPeriod();
	/**
	 * @brief Подготавливает векторы делимого и делителя (выравнивает разряды, убирает точки).
	 * @param[in] other Делитель.
	 * @param[out] dividendVector Выходной вектор делимого.
	 * @param[out] divisorVector Выходной вектор делителя.
	 */
	void prepareDivVectors(const FractionNumber& other,
		std::vector<uint8_t>& dividendVector,
		std::vector<uint8_t>& divisorVector) const;
	/**
	 * @brief Выполняет финальную очистку и нормализацию структуры числа.
	 * @param[in,out] result Модифицируемый объект результата.
	 */
	void finalizeResult(FractionNumber& result) const;
	/**
	 * @brief Проверяет пограничные и специальные случаи при возведении в степень.
	 * @param[in] exponent Показатель степени.
	 * @param[out] result Объект для записи результата в случае успеха.
	 * @param[out] isHandled Флаг: true, если специальный случай обработан, иначе false.
	 * @return true, если это специальный случай; иначе false.
	 */
	bool checkDegreeSpecialCases(const FractionNumber& exponent, FractionNumber& result, bool& isHandled);
	/**
	* @brief Проверяет, является ли дробная часть текущего числа нулевой.
	* @return true, если дробная часть отсутствует или равна нулю, иначе false.
	*/
	bool isFractionPartZero() const;
	/**
	 * @brief Складывает два числа с одинаковыми знаками.
	 * @param[in] other Второе число.
	 * @param[in] frac1 Выровненная дробная часть первого числа.
	 * @param[in] frac2 Выровненная дробная часть второго числа.
	 * @param[in] maxFracLen Максимальная длина дробной части среди двух чисел.
	 * @return Результат сложения.
	 */
	FractionNumber addSameSign(const FractionNumber& other,
		const std::vector<uint8_t>& frac1,
		const std::vector<uint8_t>& frac2,
		size_t maxFracLen);
	/**
	 * @brief Вычитает два числа с разными знаками.
	 * @param[in] other Второе число.
	 * @param[in] frac1 Выровненная дробная часть первого числа.
	 * @param[in] frac2 Выровненная дробная часть второго числа.
	 * @param[in] maxFracLen Максимальная длина дробной части среди двух чисел.
	 * @return Результат вычитания.
	 */
	FractionNumber subDifferentSign(const FractionNumber& other,
		const std::vector<uint8_t>& frac1,
		const std::vector<uint8_t>& frac2,
		size_t maxFracLen);
	/**
	 * @brief Поразрядно вычитает вектор B из вектора A с учетом заёма.
	 * @param[in] A Вектор-уменьшаемое.
	 * @param[in] B Вектор-вычитаемое.
	 * @param[out] result Вектор-разность.
	 * @param[in,out] borrow Переменная заёма между разрядами.
	 */
	static void subtractVectors(const std::vector<uint8_t>& A,
		const std::vector<uint8_t>& B,
		std::vector<uint8_t>& result,
		int& borrow);
	/**
	 * @brief Устраняет ошибки округления чисел с плавающей точкой в строке.
	 * @param[in,out] resultStr Строковое представление числа для анализа и модификации.
	 */
	static void handleFloatingArtifacts(std::string& resultStr);
	/**
	 * @brief Инкрементирует числовое значение, записанное в строке.
	 * @param[in,out] str Строка с числом для инкремента.
	 */
	static void incrementString(std::string& str);

public:
	/**
	 * @brief Конструктор по умолчанию. Инициализирует объект значением "0".
	 */
	FractionNumber();
	/**
	 * @brief Конструктор из строкового представления числа.
	 * @param[in] str Строка, содержащая вещественное число.
	 * @throws std::invalid_argument Если строка имеет неверный формат.
	 */
	explicit FractionNumber(const string& str);
	/**
	 * @brief Преобразует объект FractionNumber в строковый формат.
	 * @return Строка с текстовым представлением числа.
	 */
	string toString() const;
	/**
	 * @brief Операция сложения текущего числа с другим числом.
	 * @param[in] other Слагаемое.
	 * @return Новый объект FractionNumber — сумма чисел.
	 */
	FractionNumber add(const FractionNumber& other);
	/**
	 * @brief Операция вычитания другого числа из текущего.
	 * @param[in] other Вычитаемое.
	 * @return Новый объект FractionNumber — разность чисел.
	 */
	FractionNumber sub(const FractionNumber& other);
	/**
	 * @brief Операция умножения текущего числа на другое число.
	 * @param[in] other Множитель.
	 * @return Новый объект FractionNumber — произведение чисел.
	 */
	FractionNumber mul(const FractionNumber& other);
	/**
	 * @brief Операция деления текущего числа на другое число.
	 * @param[in] other Делитель.
	 * @return Новый объект FractionNumber — частное чисел.
	 * @throws std::invalid_argument Если делитель равен нулю.
	 */
	FractionNumber div(const FractionNumber& other);
	/**
	 * @brief Извлечение корня заданной степени из текущего числа.
	 * @param[in] rootDegree Степень корня.
	 * @return Новый объект FractionNumber — результат извлечения корня.
	 */
	FractionNumber sqrt(const FractionNumber& rootDegree);
	/**
	 * @brief Возведение текущего числа в указанную степень.
	 * @param[in] exponent Показатель степени.
	 * @return Новый объект FractionNumber — результат возведения в степень.
	 * @throws std::invalid_argument При попытке возвести отрицательное число в дробную степень.
	 */
	FractionNumber degree(const FractionNumber& exponent);
	/**
	 * @brief Преобразует объект FractionNumber в стандартный тип double.
	 * @return Значение текущего объекта, приведенное к типу double.
	 */
	double convertToDouble() const;
};

/**
 * @enum DataErrors
 * @brief Перечисление кодов ошибок валидации данных и арифметических операций.
 */
enum class DataErrors {
	NO_DATA_ERROR, // ошибок нет
	NO_FRACTION, // несоответствие символов нужному шаблону согласно условиям
	WRONG_INPUT, // нужные символы не являются дробным числом
	WRONG_OPERATION, // неподдерживаемая операция
	INCORRECT_RANGE // неверный диапазон 
};

/**
 * @class Range
 * @brief Класс для представления математического интервала [left, right].
 * @details Используется для проверки вхождения вещественных чисел в заданные границы
 * при валидации входных данных. Поддерживает как полноценные интервалы,
 * так и отдельные изолированные точки (где left == right).
 */
class Range {
	double _left = 0.0; // Левая граница интервала
	double _right = 0.0; // Правая граница интервала
public:

	/**
	 * @brief Конструктор для создания полноценного диапазона.
	 * @param[in] left  Левая граница диапазона.
	 * @param[in] right Правая граница диапазона.
	 */
	Range(double left, double right)
		: _left(left), _right(right) {
	}

	/**
	 * @brief Конструктор для создания диапазона, состоящего из одной точки.
	 * @details Применяется для явного исключения конкретных значений.
	 * @param[in] point Значение изолированной точки.
	 */
	explicit Range(double point)
		: _left(point), _right(point) {
	}

	/**
	 * @brief Проверяет, входит ли переданное значение в текущий интервал включительно.
	 * @param[in] value Проверяемое вещественное число.
	 * @return true, если число находится внутри отрезка [_left, _right]; иначе false.
	 */
	bool include(double value) const {
		return _left <= value && value <= _right;
	}

	/**
	 * @brief Возвращает левую границу диапазона.
	 * @return double Значение левой границы.
	 */
	double left()  const { return _left; }
	/**
	 * @brief Возвращает правую границу диапазона.
	 * @return double Значение правой границы.
	 */
	double right() const { return _right; }
};

/**
 * @brief Проверяет попадание значения в разрешенные диапазоны и отсутствие в запрещенных.
 * @param[in] value Проверяемое вещественное значение (double).
 * @param[in] includeRanges Список интервалов, в которые значение обязано попасть.
 * @param[in] excludeRanges Список интервалов/точек, в которые значение не должно попасть.
 * @return true, если значение успешно прошло валидацию; иначе false.
 */
bool validateRange(double value,
	const std::vector<Range>& includeRanges,
	const std::vector<Range>& excludeRanges = {});

/**
 * @brief Проверяет допустимость извлечения корня заданной степени из подкоренного выражения.
 * @details Исключает получение комплексных результатов. Разрешает операцию, если подкоренное число
 * неотрицательно, либо если корень берется из отрицательного числа, но степень корня является нечетным целым числом.
 * @param[in] val1 Подкоренное выражение (основание).
 * @param[in] val2 Степень корня (показатель).
 * @return true, если операция математически корректна в рамках действительных чисел; иначе false.
 */
bool checkSqrtSign(double val1, double val2);

/**
 * @brief Выполняет лексический анализ, парсинг и комплексную валидацию входной строки.
 * @details Разбивает строку на составные токены, проверяет тип математической операции,
 * парсит операнды в формат FractionNumber и тестирует их на попадание в допустимые лимиты.
 * @param[in]  inputData Исходная текстовая строка из файла конфигурации теста.
 * @param[out] operation Строка для записи успешно распознанной математической операции.
 * @param[out] first Объект для сохранения первого числа.
 * @param[out] second Объект для сохранения второго числа.
 * @return DataErrors Перечисление, содержащее код ошибки парсинга (или NO_DATA_ERROR при полном успехе).
 */
DataErrors parseInputData(const std::string& inputData,
	std::string& operation,
	FractionNumber& first,
	FractionNumber& second);