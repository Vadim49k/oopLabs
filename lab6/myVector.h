#pragma once
#include <iostream>
#include <algorithm>


template<class T>
class myVector {
public:
	myVector();
	myVector(size_t count);
	myVector(const myVector &vector);
	myVector(myVector &&vector);
	myVector<T> &operator=(const myVector &vector);
	myVector<T> &operator=(myVector &&vector);
	~myVector();

	void resize(size_t size);
	void reserve(size_t size);
	void push_back(const T &element);
	
	size_t size() const;
	size_t max_size() const;
	size_t capacity() const;
	bool empty() const;

	const T &operator[] (size_t index);
	const T &at(size_t index);

private:
	T *arr;
	size_t _cur_size, _max_size, _arr_size;

	//bool is_reserved = false;
	//bool is_empty = true;

	void change_arr_size(const size_t &size);
};
#include "myVector.cpp.h"