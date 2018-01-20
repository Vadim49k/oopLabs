#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <set>

#include "Factorization.h"

using namespace std; 

int main(int argc, char *argv[]) {
	if (argc == 3) {
		Factorization::factorizeFile(argv[1], argv[2]);
		//Factorization::factorizeFile("D:\\main\\2_course\\labs\\oop\\lab04\\numbers.txt", "D:\\main\\2_course\\labs\\oop\\lab04\\result.txt");
		//D:\lab04.exe "D:\main\2_course\labs\oop\lab04\numbers.txt" "D:\main\2_course\labs\oop\lab04\result.txt"
		return 0;
	}

	/*while (true) {
		uint64_t i = rand();
		cout << i;
		f.factorize(i);
		if (i == f.countFactorization()) 
			cout << "+" << endl;
		else {
			cout << "-" << endl;
			system("pause");
		}

	}*/

	Factorization f;
	f.factorize(128);
	cout << f.getFactorization() << "\n";
	f.factorize(129);
	cout << f.getFactorization() << "\n";
	f.factorize(127);
	cout << f.getFactorization() << "\n";
	f.factorize(121);
	cout << f.getFactorization() << "\n";
	f.factorize(122);
	cout << f.getFactorization() << "\n";
	f.factorize(123);
	cout << f.getFactorization() << "\n";
	f.factorize(132);
	cout << f.getFactorization() << "\n";
	f.factorize(133);
	cout << f.getFactorization() << "\n";
	f.factorize(134);
	cout << f.getFactorization() << "\n";
	f.factorize(131);
	cout << f.getFactorization() << "\n";
	
	cout << f.getNumber() << "\n";

	cout << f.isLoad() << endl;
	f.deleteFactorization();
	cout << f.isLoad() << endl;

	uint64_t a = UINT64_MAX;
	cout << a << endl;
	f.factorize(a);
	cout << f.getFactorization() << endl;
	
	system("pause");
	return 0; 
}
