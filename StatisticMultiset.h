#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <fstream>
#include <string>
#include <typeinfo>

template <class T>
class StatisticMultiset {
public:
	StatisticMultiset();
	~StatisticMultiset();

	void addNum(const T &num);
	void addNum(const std::multiset<T>& numbers);
	void addNum(const std::vector<T>& numbers);
	void addNum(const std::list<T>& numbers);
	void addNum(const StatisticMultiset& a_stat_set);
	void addNumsFromFile(const std::string& file);

	int getSize() const;
	T getMax() const;
	T getMin() const;
	T getAvg() const;
	int getCountUnder(const T &threshold) const;
	int getCountAbove(const T &threshold) const;

private:
	bool isEmpty;
	std::vector<T> numbers;
	mutable std::pair<T, int> last_check_under;
	mutable std::pair<T, int> last_check_above;
	//bool isFirstCheckUnder, isFirstCheckAbove;
	T maxNum, minNum, sum;
};

template <class T>
StatisticMultiset<T>::StatisticMultiset() {
	isEmpty = true;
}

template <class T>
StatisticMultiset<T>::~StatisticMultiset() {
	numbers.clear();
}

template <class T>
void StatisticMultiset<T>::addNum(const T &num) {
	numbers.push_back(num);
	if (isEmpty) {
		maxNum = num;
		minNum = num;
		sum = num;
		isEmpty = false;
	}
	else {
		if (num > maxNum) maxNum = num;
		if (num < minNum) minNum = num;
		sum += num;
	}
}

template <class T>
void StatisticMultiset<T>::addNum(const std::multiset<T>& _numbers) {
	for (auto& i : _numbers) {
		addNum(i);
	}
}

template <class T>
void StatisticMultiset<T>::addNum(const std::vector<T>& _numbers) {
	for (auto& i : _numbers) {
		addNum(i);
	}
}

template <class T>
void StatisticMultiset<T>::addNum(const std::list<T>& _numbers) {
	for (auto& i : _numbers) {
		addNum(i);
	}
}

template <class T>
void StatisticMultiset<T>::addNum(const StatisticMultiset& a_stat_set) {
	for (int i = 0; i < a_stat_set.numbers.size(); i++) {
		addNum(a_stat_set.numbers[i]);
	}
}

template <class T>
void StatisticMultiset<T>::addNumsFromFile(const std::string& file) {
	T _temp;
	std::ifstream fin(file);
	while (fin >> _temp) {
		addNum(_temp);
	}
}

template <class T>
int StatisticMultiset<T>::getSize() const {
	return numbers.size();
}

template <class T>
T StatisticMultiset<T>::getMax() const {
	return maxNum;
}

template <class T>
T StatisticMultiset<T>::getMin() const {
	return minNum;
}

template <class T>
T StatisticMultiset<T>::getAvg() const {
	return sum / numbers.size();
}

template <class T>
int StatisticMultiset<T>::getCountUnder(const T &num) const {
	if (last_check_under.first == num) return last_check_under.second;
	int count = 0;
	for (auto& i : numbers)
		if (i < num) count++;
	last_check_under.first = num;  last_check_under.second = count;
	return count;
}

template <class T>
int StatisticMultiset<T>::getCountAbove(const T &num) const {
	if (last_check_above.first == num) return last_check_above.second;
	int count = 0;
	for (auto& i : numbers)
		if (i > num) count++;
	last_check_above.first = num;  last_check_above.second = count;
	return count;
}