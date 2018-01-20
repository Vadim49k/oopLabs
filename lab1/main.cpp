#pragma once
#include <iostream>
#include "../lab1/IniParser.h"
#include <vector>

using namespace std;

int main()
{
	//std::vector<int> a;
	
	string s, section, name;
	IniParser pars("D:\\main\\2 course\\labs\\oop\\lab01\\input_files\\lab01_input_correct_09.ini");
	//IniParser a("D:\\main\\2 course\\labs\\oop\\lab01\\input_files\\lab01_input_correct_09.txt");
	//IniParser b("\lol.ini");
	IniParser c;
	c.loadFile("D:\\main\\2 course\\labs\\oop\\lab01\\input_files\\lab01_input_correct_09.ini");
	
	//cout << b.isLoad() << " " << c.isLoad() << "\n";
	/*
	//pars.getIni();
	//cout << pars.check("DEMODS", "SampleRate");
	//cout << pars.check("SECTION", "RawCacheMaxGapMs");
	//cout << pars.isLoad();
	//pars.~IniParser();
	/*
	while (cin >> s)
	{
		if (s == "exit") break;
		//if (s == "IniParser")
		if (s == "getValString") { cin >> section >> name; cout << pars.getValString(section, name) << "\n"; }
		if (s == "getValInt") { cin >> section >> name; cout << pars.getValInt(section, name) << "\n"; }
		if (s == "getValDouble") { cin >> section >> name; cout << pars.getValDouble(section, name) << "\n"; }
		if (s == "isLoad") { cout << pars.isLoad() << "\n"; }
		if (s == "check") { cin >> section >> name; cout << pars.check(section, name) << "\n"; }
	}
	*/
	//b.checkSection("");

	section ="DEBUG";
	name = "CheckThisParameter";

	cout << pars.checkName("DEBUG", "CheckThisParameter") << "\n";
	cout << pars.checkName(section, name) << "\n";
	cout << pars.checkName("DEBUG", "Chec") << "\n";
	cout << pars.getValue<int>(section, name) << "\n";
	cout << pars.getValue<string>(section, name) << "\n";
	cout << pars.getValue<double>(section, name) << "\n";

	cout << pars.getValue<double>("DEMODS", "FileName") << "\n";
	cout << pars.getValue<string>("DEMODS", "FileName") << "\n";
	cout << pars.isLoad() << "\n";;
	bool x;
	cin >> x;
	return 0;
}