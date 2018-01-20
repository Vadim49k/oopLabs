#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <map>
#include "math.h"

class Factorization {
public:
	enum Signal { Pause, Resume, Exit };
	Factorization(const size_t &size, const std::string &inFile, const std::string &outFile);
	~Factorization();

	void addNumber(const uint64_t &num);
	void setSignal(enum Factorization::Signal signal);

private:
	std::string fileTo, fileFrom;
	std::ofstream fout;
	std::ifstream fin;

	//bool is_load =     false;
	//bool is_running =  false;
	//bool is_counting = false;
	bool is_empty                 = false;
	bool is_send                  = false;
	bool is_pause                 = false;
	bool is_exit                  = false;

	std::queue<uint64_t>            numbers;
	//std::map<std::thread::id, bool> threads_ready;
	std::vector<std::thread>        threads_factr;
	std::thread                     thread_read;
	mutable std::mutex              mutex_queue;
	mutable std::mutex              mutex_read;
	mutable std::condition_variable cv_queue;
	mutable std::condition_variable cv_read;

	void readLoop();
	void factLoop();
	void pause();
	void resume();
	void exit();
	
	void factorize(const uint64_t &number, std::vector<std::pair<uint64_t, int8_t>> &factorization);
	std::string getFactorization(const std::vector<std::pair<uint64_t, int8_t>> &factorization) const;

	uint64_t countFactorization(const std::vector<std::pair<uint64_t, int8_t>>&) const;
	bool Prime(uint64_t) const;
};

