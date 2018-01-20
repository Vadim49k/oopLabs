#include "Factorization.h"

Factorization::Factorization() {
}

Factorization::Factorization(const uint64_t &num) {
	factorize(num);
}

Factorization::~Factorization() {
	factorization.clear();
}

void Factorization::factorize(uint64_t num) {
	deleteFactorization();
	is_load = true;
	number = num;

	if (num <= 0) return;

	for (short i = 2; i < 6; i++) {
		if (num % i == 0) {
			factorization.push_back(std::make_pair(i, 0));
			while (num % i == 0) {
				num /= i;
				factorization[factorization.size() - 1].second++;
			}
		}
	}
	for (uint64_t i = 12; i <= sqrt(number) + 6; i = i + 6) {
		if (num % (i - 5) == 0) {
			factorization.push_back(std::make_pair(i - 5, 0));
			while (num % (i - 5) == 0) {
				num /= (i - 5);
				factorization[factorization.size() - 1].second++;
			}
		}
		if (num % (i - 1) == 0) {
			factorization.push_back(std::make_pair(i - 1, 0));
			while (num % (i - 1) == 0) {
				num /= (i - 1);
				factorization[factorization.size() - 1].second++;
			}
		}
	}
	if (num > 1) {
		factorization.push_back(std::make_pair(num, 0));
		factorization[factorization.size() - 1].second++;
	}
}

void Factorization::deleteFactorization() {
	is_load = false;
	factorization.clear();
}

void Factorization::factorizeFile(const std::string &fileFrom, const std::string &fileTo) {
	Factorization fact;
	uint64_t num;
	std::ifstream fin(fileFrom);
	std::ofstream fout(fileTo, std::ios::app);

	while (fin >> num) {
		fact.factorize(num);
		fout << fact.getFactorization() << '\n';
	}
	fact.deleteFactorization();
}

uint64_t Factorization::getNumber() const {
	return number;
}

std::string Factorization::getFactorization() const {
	if (number == 0) return "0 = 0";
	if (number == 1) return "1 = 1";
	std::string res = std::to_string(number);
	res += " = ";
	for (uint64_t i = 0; i < factorization.size(); i++) {
		res += std::to_string(factorization[i].first);
		res += "^";
		res += std::to_string(factorization[i].second);
		if (i != factorization.size() - 1) res += " * ";
	}
	return res;
}

bool Factorization::isLoad() const {
	return is_load;
}

uint64_t Factorization::countFactorization() const {
	if (number == 0) return 0;
	uint64_t res = 1;
	for (uint64_t i = 0; i < factorization.size(); i++) {
		if (!Prime(factorization[i].first)) {
			std::cout << "-";
			system("pause");
		}

	}
	for (uint64_t i = 0; i < factorization.size(); i++) {
		res *= pow(factorization[i].first, factorization[i].second);
	}
	return res;
}
bool Factorization::Prime(uint64_t a) const {
	unsigned long i1, i2, i3, i4, i5, i6, i7, i8, bound;
	if (a == 0 || a == 1)
		return 0;
	if (a == 2 || a == 3 || a == 5 || a == 7 || a == 11 || a == 13 || a == 17 || a == 19 || a == 23 || a == 29)
		return 1;
	if (a % 2 == 0 || a % 3 == 0 || a % 5 == 0 || a % 7 == 0 || a % 11 == 0 || a % 13 == 0 || a % 17 == 0 || a % 19 == 0 || a % 23 == 0 || a % 29 == 0)
		return 0;
	bound = sqrt((double)a);
	i1 = 31; i2 = 37; i3 = 41; i4 = 43; i5 = 47; i6 = 49; i7 = 53; i8 = 59;
	while (i8 <= bound && a%i1 && a%i2 && a%i3 && a%i4 && a%i5 && a%i6 && a%i7 && a%i8)
	{
		i1 += 30; i2 += 30; i3 += 30; i4 += 30; i5 += 30; i6 += 30; i7 += 30; i8 += 30;
	}
	if (i8 <= bound ||
		i1 <= bound && a % i1 == 0 ||
		i2 <= bound && a % i2 == 0 ||
		i3 <= bound && a % i3 == 0 ||
		i4 <= bound && a % i4 == 0 ||
		i5 <= bound && a % i5 == 0 ||
		i6 <= bound && a % i6 == 0 ||
		i7 <= bound && a % i7 == 0)
		return 0;
	return 1;
}
