#pragma once
#include <string>
#include <vector>
using namespace std;

class FractionNumber {
private:
	vector<uint8_t> integerPart;
	vector<uint8_t> fractionPart;
	bool isNegative;
	void appendZerosRight(std::vector<uint8_t>& vec, size_t targetLen) const;
	void prependZerosLeft(std::vector<uint8_t>& vec, size_t targetLen) const;
	bool compareByModule(const FractionNumber& other,
		const std::vector<uint8_t>& f1,
		const std::vector<uint8_t>& f2) const;

public:
	FractionNumber() {
		isNegative = false;
	}
	FractionNumber(const string& str);

	string toString() const;

	FractionNumber add(const FractionNumber& other);
	FractionNumber sub(const FractionNumber& other);
	FractionNumber mul(const FractionNumber& other);
	FractionNumber div(const FractionNumber& other);
	FractionNumber sqrt(const FractionNumber& rootDegree);
	FractionNumber degree(const FractionNumber& exponent);
};

enum class DataErrors {
	NO_DATA_ERROR, // ошибок нет
	NO_FRACTION, // несоответствие символов нужному шаблону согласно условиям
	WRONG_INPUT, // нужные символы не являются дробным числом
	WRONG_OPERATION, // неподдерживаемая операция
	INCORRECT_RANGE // неверный диапазон 
};