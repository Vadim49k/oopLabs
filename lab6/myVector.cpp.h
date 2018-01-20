template<class T>
myVector<T>::myVector()
	: _max_size(0), _cur_size(0), _arr_size(10)
{
	arr = new T[10];
}

template<class T>
myVector<T>::myVector(size_t count)
	: _max_size(count), _cur_size(0), _arr_size(count + 10)
{
	arr = new T[_arr_size];
}

template<class T>
myVector<T>::myVector(const myVector &vector) {
	*this = vector;
}

template<class T>
myVector<T>::myVector(myVector &&vector) {
	*this = std::move(vector);
}

template<class T>
myVector<T> &myVector<T>::operator=(const myVector & vector)
{
	_cur_size = vector._cur_size;
	_max_size = vector._max_size;
	_arr_size = vector._arr_size;
	arr = new T[_arr_size];
	for (size_t i = 0; i < _cur_size; i++) {
		arr[i] = vector.arr[i];
	}
	return *this;
}

template<class T>
myVector<T> &myVector<T>::operator=(myVector && vector)
{
	arr = std::move(vector.arr);
	vector.arr = nullptr;
	_cur_size = vector._cur_size;
	_max_size = vector._max_size;
	_arr_size = vector._arr_size;

	vector._cur_size = 0;
	vector._max_size = 0;
	vector._arr_size = 0;
	return *this;
}

template<class T>
myVector<T>::~myVector() {
	delete[] arr;
}

template<class T>
void myVector<T>::resize(size_t size) {
	if (size <= _arr_size) {
		_max_size = size;
		if (size < _cur_size) _cur_size = size;
	}
	else {
		change_arr_size(size + 10);
		_max_size = size;
		if (size < _cur_size) _cur_size = size;
	}
}

template<class T>
void myVector<T>::reserve(size_t size) {
	change_arr_size(size);
	if (size <= _max_size) {
		_max_size = size;
		if (size < _cur_size) _cur_size = size;
	}
}

template<class T>
void myVector<T>::push_back(const T &element) {
	if (_max_size + 1 <= _arr_size) {
		_max_size++;
	}
	else {
		change_arr_size(_max_size + 10);
	}
	arr[_cur_size] = element;
	_cur_size++;
}

//--------------------------------------------

template<class T>
size_t myVector<T>::size() const {
	return _cur_size;
}

template<class T>
size_t myVector<T>::max_size() const {
	return _max_size;
}

template<class T>
size_t myVector<T>::capacity() const {
	return _arr_size;
}

template<class T>
bool myVector<T>::empty() const
{
	return !_cur_size;
}

template<class T>
const T &myVector<T>::operator[](size_t index) {
	return arr[index];
}

template<class T>
const T & myVector<T>::at(size_t index) {
	if ((index < 0) || (index >= _cur_size)) {
		throw std::out_of_range("Out of myVector range");
	}
	return arr[index];
}

template<class T>
void myVector<T>::change_arr_size(const size_t & new_arr_size) {
	T *new_arr;
	new_arr = new T[new_arr_size];
	for (size_t i = 0; i < std::min(new_arr_size, _arr_size); i++) {
		new_arr[i] = arr[i];
	}
	delete[] arr;
	arr = new_arr;
	_arr_size = new_arr_size;
}
