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
#include <functional>

class ThreadPool {
public:
	enum Signal { Pause, Resume, Exit };
	ThreadPool(const size_t &size);
	~ThreadPool();

	void setSignal(enum ThreadPool::Signal signal);
	void addFunction(std::function<void()> const &function);
	size_t sizeWorks() const;

private:
	bool is_empty = false;
	bool is_send = false;
	bool is_pause = false;
	bool is_exit = false;

	std::queue<std::function<void()>> tasks;
	std::vector<std::thread>          threads;
	mutable std::mutex                mutex_queue;
	mutable std::mutex                mutex_read;
	mutable std::condition_variable   cv_queue;
	mutable std::condition_variable   cv_read;

	void workLoop();
	void pause();
	void resume();
	void exit();
};


