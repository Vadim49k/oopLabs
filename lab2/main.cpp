#include "StatisticMultiset.h"

using namespace std;

int main() {
	cout << "Lab 02" << endl;
	//StatisticMultiset<string> mss;
	//mss.addNum("Hello");

	//cout << mss.getAvg();
	StatisticMultiset<int> ms1;
	ms1.addNum(89);
	ms1.addNum(54);
	ms1.addNum(54);
	ms1.addNum(24);
	StatisticMultiset<int> ms2;
	std::vector<int> somedata = { 10, 40, 6, 87 };
	std::list<int> somedata1 = { 1 };
	std::multiset<int> somedata2 = { 110 };
	ms1.addNum(somedata);
	StatisticMultiset<int> ms3;
	StatisticMultiset<float> ms4;
	std::vector<float> somedata3 = { 10, 40, 6, 87 };
	ms4.addNum(somedata3);
	ms4.addNum(0);
	cout << ms4.getMin() << endl
		<< ms4.getMax() << endl
		<< ms4.getSize() << endl
		<< ms4.getCountAbove(1) << endl
		<< endl;
	ms3.addNum(somedata1);
	ms3.addNum(somedata2);
	ms3.addNum(ms1);
	ms3.addNum(ms2);
	ms3.addNumsFromFile("D:\\main\\2 course\\labs\\oop\\lab02\\numb.txt");
	cout << " Min: " << ms3.getMin()
		<< " Avg: " << ms3.getAvg()
		<< " Max: " << ms3.getMax() << endl
		<< " Count under: " << ms3.getCountUnder(5) << endl
		<< " Count above: " << ms3.getCountAbove(86) << endl
		<< " numbers: " << ms3.getSize()
		<< endl;
	cout << " Count under: " << ms3.getCountUnder(5) << endl;
	system("pause");
	return 0;
}