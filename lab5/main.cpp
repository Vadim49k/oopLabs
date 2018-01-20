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
	//std::lock(c1,c2)
	//std::this_thread::sleep_for(std::chrono::seconds(1));

int main(int argc, char *argv[]) {
	
	if (argc == 4) {
		Factorization f((int)(argv[1]-'0'), argv[2], argv[3]);
		//Factorization::factorizeFile("D:\\main\\2_course\\labs\\oop\\lab04\\numbers.txt", "D:\\main\\2_course\\labs\\oop\\lab04\\result.txt");
		//D:\oop5.exe "D:\main\2_course\labs\oop\lab04\numbers.txt" "D:\main\2_course\labs\oop\lab04\result.txt"
		
		std::string str;
		while (true) {
			cin >> str;
			if (str == "exit") {
				f.setSignal(Factorization::Signal::Exit);
			}
			else if (str == "pause") {
				f.setSignal(Factorization::Signal::Pause);
			}
			else if (str == "resume") {
				f.setSignal(Factorization::Signal::Resume);
			}
			else {
				cout << "error" << endl;
			}
		}
		return 0;
	}
	Factorization f(2, "D:\\main\\2_course\\labs\\oop\\lab04\\numbers.txt", "D:\\main\\2_course\\labs\\oop\\lab04\\result.txt");
	this_thread::sleep_for(chrono::seconds(1));
	f.setSignal(Factorization::Signal::Pause);
	this_thread::sleep_for(chrono::seconds(10));
	f.setSignal(Factorization::Signal::Resume);
	this_thread::sleep_for(chrono::seconds(50));
	f.setSignal(Factorization::Signal::Exit);
	this_thread::sleep_for(chrono::seconds(10));
	system("pause");
	return 0;
}
