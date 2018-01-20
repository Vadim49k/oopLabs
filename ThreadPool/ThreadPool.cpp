#include "ThreadPool.h"

ThreadPool::ThreadPool(const size_t &size) {
	for (size_t i = 0; i < size; i++) {
		threads.push_back(std::thread(&ThreadPool::workLoop, this));
		//threads_ready[threads_factr[i].get_id()] = 1;
	}

}

ThreadPool::~ThreadPool() {
	exit();
}

void ThreadPool::setSignal(ThreadPool::Signal signal) {
	if (signal == 0)       pause();
	else if (signal == 1)  resume();
	else if (signal == 2)  exit();
}

void ThreadPool::addFunction(std::function<void()> const & function) {
	std::unique_lock<std::mutex> queue_lock(mutex_queue);
	tasks.push(function);
	cv_queue.notify_one();
}

size_t ThreadPool::sizeWorks() const {
	return tasks.size();
}

void ThreadPool::workLoop() {
	//std::vector<std::pair<uint64_t, int8_t>> ThreadPool;
	while (true) {
		std::unique_lock<std::mutex> queue_lock(mutex_queue);
		cv_queue.wait(queue_lock, [this] {return (!tasks.empty() && !is_pause); });
		if (tasks.empty() || is_exit) return;
		std::function<void()> work;
		work = std::move(tasks.front());
		tasks.pop();
		queue_lock.unlock();
		work();
	}
}

void ThreadPool::pause() {
	is_pause = true;
}

void ThreadPool::resume() {
	is_pause = false;
	cv_queue.notify_all();
}

void ThreadPool::exit() {
	is_exit = true;
	is_pause = false;
	cv_queue.notify_all();
	for (size_t i = 0; i < threads.size(); i++) {
		if (threads[i].joinable())
			threads[i].join();
	}
	threads.clear();
	//threads_ready.clear();
}


