#pragma once
#include <string>
#include <vector>
using namespace std;

class FractionNumber {
private:
	vector<uint8_t> integerPart;
	vector<uint8_t> fractionPart;
	bool isNegative;

	static void appendZerosRight(std::vector<uint8_t>& vec, size_t targetLen);
	static void prependZerosLeft(std::vector<uint8_t>& vec, size_t targetLen);
	bool compareByModule(const FractionNumber& other,
		const std::vector<uint8_t>& f1,
		const std::vector<uint8_t>& f2) const;
	static void removeLeadingZeros(std::vector<uint8_t>& vec);
	static void removeTrailingZeros(std::vector<uint8_t>& vec);
	bool isZero() const;
	FractionNumber convertFromDouble(double val, int precision);
	static FractionNumber powInt(FractionNumber base, unsigned long long exp);
	static double calcLn(double x);
	static double calcExp(double x);
	static unsigned long long vectorToInt(const std::vector<uint8_t>& vec);
	friend void writeResultToFile(ofstream& output_file, const FractionNumber& result);
	static int subDiv(std::vector<uint8_t>& remainder,
		const std::vector<uint8_t>& divisorVector,
		FractionNumber& remFn,
		const FractionNumber& divFn);
	void checkPeriod(FractionNumber& result);
	void prepareDivVectors(const FractionNumber& other,
		std::vector<uint8_t>& dividendVector,
		std::vector<uint8_t>& divisorVector) const;
	void finalizeResult(FractionNumber& result) const;
	bool checkDegreeSpecialCases(const FractionNumber& exponent, FractionNumber& result, bool& isHandled);
	static bool isFractionPartZero(const FractionNumber& fn);
	FractionNumber addSameSign(const FractionNumber& other,
		const std::vector<uint8_t>& frac1,
		const std::vector<uint8_t>& frac2,
		size_t maxFracLen);
	FractionNumber subDifferentSign(const FractionNumber& other,
		const std::vector<uint8_t>& frac1,
		const std::vector<uint8_t>& frac2,
		size_t maxFracLen);
	static void subtractVectors(const std::vector<uint8_t>& A,
		const std::vector<uint8_t>& B,
		std::vector<uint8_t>& result,
		int& borrow);
	static void handleFloatingArtifacts(std::string& resultStr);
	static void incrementString(std::string& str);

public:
	FractionNumber();
	explicit FractionNumber(const string& str);

	string toString() const;

	FractionNumber add(const FractionNumber& other);
	FractionNumber sub(const FractionNumber& other);
	FractionNumber mul(const FractionNumber& other);
	FractionNumber div(const FractionNumber& other);
	FractionNumber sqrt(const FractionNumber& rootDegree);
	FractionNumber degree(const FractionNumber& exponent);
	static double convertToDouble(const FractionNumber& fn);
};

enum class DataErrors {
	NO_DATA_ERROR, // ошибок нет
	NO_FRACTION, // несоответствие символов нужному шаблону согласно условиям
	WRONG_INPUT, // нужные символы не являются дробным числом
	WRONG_OPERATION, // неподдерживаемая операция
	INCORRECT_RANGE // неверный диапазон 
};