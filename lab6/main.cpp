#include <iostream>
#include <vector>
#include "myVector.h"

using namespace std;

int main() {
	myVector<int> a(5);
	myVector<int> b;
	//cout << a.size() << " " << a.max_size() << " " << a.empty() << " " << a.capacity() << "\n";
	//cout << b.size() << " " << b.max_size() << " " << b.empty() << " " << b.capacity() << "\n";
	//cout << sizeof(size_t);
	b.push_back(3);
	b.push_back(6);
	b.push_back(5);
	b.resize(5);
	//cout << b.size() << " " << b.max_size() << " " << b.empty() << " " << b.capacity() << "\n";
	cout << "======\n";
	myVector<int> d(b);
	cout << "======\n";
	//cout << d.size() << " " << d.max_size() << " " << d.empty() << " " << d.capacity() << "\n";
	myVector<int> aa = a;
	cout << "======\n";
	aa = a;
	cout << "======\n";
	myVector<int> i(a);
	cout << "======\n";
	myVector<int> c(std::move(b));
	cout << "======\n";
	myVector<int> f = std::move(d);
	cout << "======\n";
	i = std::move(f);
	//cout << b.size() << " " << b.max_size() << " " << b.empty() << " " << b.capacity() << "\n";
	//cout << d.size() << " " << d.max_size() << " " << d.empty() << " " << d.capacity() << "\n";

	//cout << c.size() << " " << c.max_size() << " " << c.empty() << " " << c.capacity() << "\n";
	//cout << f.size() << " " << f.max_size() << " " << f.empty() << " " << f.capacity() << "\n";

	//c.at(5);
	//cout << c.at(5) << endl;;
	system("pause");
	return 0;
}

