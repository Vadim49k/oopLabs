#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "math.h"

class Factorization {
public:
	Factorization();
	Factorization(const uint64_t &number);
	~Factorization();

	void factorize(uint64_t number);
	void deleteFactorization();
	uint64_t getNumber() const;
	std::string getFactorization() const;
	bool isLoad() const;

	static void factorizeFile(const std::string &fileFrom, const std::string &fileTo);

private:
	uint64_t number = 0;
	std::vector<std::pair<uint64_t, uint64_t>> factorization;

	bool is_load = false;
	
	uint64_t countFactorization() const;
	bool Prime(uint64_t) const;
};
