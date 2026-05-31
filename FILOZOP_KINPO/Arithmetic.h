#pragma once
#include <string>
#include <vector>
using namespace std;

class FractionNumber {
private:
	vector<uint8_t> integerPart;
	vector<uint8_t> fractionPart;
	bool isNegative;

public:
	FractionNumber add(const FractionNumber& other);
	FractionNumber sub(const FractionNumber& other);
	FractionNumber mul(const FractionNumber& other);
	FractionNumber div(const FractionNumber& other);
	FractionNumber sqrt(const FractionNumber& rootDegree);
	FractionNumber degree(const FractionNumber& exponent);
};