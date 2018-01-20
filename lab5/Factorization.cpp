#include "Factorization.h"

Factorization::Factorization(const size_t &size, const std::string &inFile, const std::string &outFile)
	:fileTo(outFile), fileFrom(inFile)
{
	std::unique_lock<std::mutex> read_lock(mutex_read);
	thread_read = std::thread(&Factorization::readLoop, this);
	cv_read.wait(read_lock);

	fout.open(fileTo);
	for (size_t i = 0; i < size; i++) {
		threads_factr.push_back(std::thread(&Factorization::factLoop, this));
		//threads_ready[threads_factr[i].get_id()] = 1;
	}
	
}

Factorization::~Factorization() {
	exit();
}

void Factorization::exit() {
	is_exit = true;
	cv_read.notify_one();
	if (thread_read.joinable())
		thread_read.join();
	for (size_t i = 0; i < threads_factr.size(); i++) {
		if (threads_factr[i].joinable())
			threads_factr[i].join();
	}
	threads_factr.clear();
	//threads_ready.clear();
	if (fout.is_open())
		fout.close();

}

void Factorization::readLoop() {
	uint8_t maxNum = 30;
	uint8_t curNum = 0;
	uint64_t number;

	while (!is_empty) {
		std::unique_lock<std::mutex> read_lock(mutex_read);
		fin.open(fileFrom);
		while ((fin >> number) && (curNum < maxNum)) {
			addNumber(number);
			curNum++;
		}
		if (curNum < maxNum) is_empty = true;
		fin.close();
		curNum = 0;
		cv_read.notify_one();
		cv_read.wait(read_lock);
	}
}

void Factorization::factLoop() {
	std::vector<std::pair<uint64_t, int8_t>> factorization;
	while (!is_empty || numbers.size()) {
		std::unique_lock<std::mutex> queue_lock(mutex_queue);
		if (is_pause) {
			if (fout.is_open())
				fout.close();
			cv_queue.wait(queue_lock);
		}
		else if (is_exit) {
			return;
		}
		else {
			if ((numbers.size() < threads_factr.size()) && !is_empty) {
				std::unique_lock<std::mutex> read_lock(mutex_read);
				cv_read.notify_one();
			}
			if (!numbers.empty()) {
				uint64_t curNumber = numbers.front();
				numbers.pop();
				//std::cout << curNumber << "\n";
				queue_lock.unlock();

				factorize(curNumber, factorization);
				std::string fact = getFactorization(factorization);
				
				queue_lock.lock();
				if (!fout.is_open())
					fout.open(fileTo, std::ios::app);
				fout << curNumber << " = " << fact << "\n";
			}
		}
	}
}

void Factorization::pause() {
	is_pause = true;
}

void Factorization::resume() {
	if (!fout.is_open())
		fout.open(fileTo, std::ios::app);
	is_pause = false;
	cv_queue.notify_all();
}

//-----------------------------------------------

void Factorization::factorize(const uint64_t &number, std::vector<std::pair<uint64_t, int8_t>> &factorization) {
	factorization.clear();
	uint64_t curNumber = number;

	if (number <= 1) return;

	for (short i = 2; i < 6; i++) {
		if (curNumber % i == 0) {
			factorization.push_back(std::make_pair(i, 0));
			while (curNumber % i == 0) {
				curNumber /= i;
				factorization[factorization.size() - 1].second++;
			}
		}
	}
	for (uint64_t i = 12; i <= sqrt(number) + 6; i = i + 6) {
		if (curNumber % (i - 5) == 0) {
			factorization.push_back(std::make_pair(i - 5, 0));
			while (curNumber % (i - 5) == 0) {
				curNumber /= (i - 5);
				factorization[factorization.size() - 1].second++;
			}
		}
		if (curNumber % (i - 1) == 0) {
			factorization.push_back(std::make_pair(i - 1, 0));
			while (curNumber % (i - 1) == 0) {
				curNumber /= (i - 1);
				factorization[factorization.size() - 1].second++;
			}
		}
	}
	if (curNumber > 1) {
		factorization.push_back(std::make_pair(curNumber, 0));
		factorization[factorization.size() - 1].second++;
	}
	//is_counting = false;
	//cv.notify_all();
}

void Factorization::addNumber(const uint64_t &num) {
	std::unique_lock<std::mutex> queue_lock(mutex_queue);
	numbers.push(num);
}

void Factorization::setSignal(Factorization::Signal signal) {
	if (signal == 0)       pause();
	else if (signal == 1)  resume();
	else if (signal == 2)  exit();
}

std::string Factorization::getFactorization(const std::vector<std::pair<uint64_t, int8_t>> &factorization) const {
	std::string res="";
	for (uint64_t i = 0; i < factorization.size(); i++) {
		res += std::to_string(factorization[i].first);
		res += "^";
		res += std::to_string(factorization[i].second);
		if (i != factorization.size() - 1) res += " * ";
	}
	return res;
}

//-----------------------------------------------


//-----------------------------------------------
uint64_t Factorization::countFactorization(const std::vector<std::pair<uint64_t, int8_t>> &factorization) const {
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
