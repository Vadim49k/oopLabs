#include <iostream>
#include "ThreadPool.h"
using namespace std;
void hello() {
	for (int i = 0; i < 5; i++) {
		cout << i << "Hello\n";
	}
}
int main() {
	ThreadPool pool(5);

	for (int i = 0; i < 10; i++)
		pool.addFunction(hello);

	system("pause");
	return 0;
}