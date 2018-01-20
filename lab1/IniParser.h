#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "../lab1/Exception.h"

class IniParser
{
public:
	IniParser();
	IniParser(const std::string& file);
	~IniParser();

	bool isLoad() const;
	void loadFile(const std::string& file)
		throw (invalid_format, file_not_found);

	bool checkSection(const std::string& section) const
		throw (file_not_loaded);
	bool checkName(const std::string& section, const std::string& name) const
		throw (file_not_loaded);
	//void getFile() const;

	template<typename T>
	inline T getValue(const std::string& section, const std::string& name)
		throw (invalid_type, name_not_found, file_not_loaded);

private:
	bool is_load = 0;
	std::map <std::string, std::map<std::string, std::string>> iniFile;
};

/*template<typename T>
T IniParser::getVal(const string& section, const string& name) const 
{
	stringstream ss;
	ss << iniFile[section][name];
	T temp;
	ss >> temp;
	if (ss.eof())
		return temp; //static_cast<T>(iniFile[section][name].c_str());
}*/


template<>
inline int IniParser::getValue<int>(const std::string & section, const std::string & name) {
	if (!is_load) throw file_not_loaded();
	if (checkName(section, name))
		return atoi(iniFile[section][name].c_str());
	throw name_not_found();
}

template<>
inline double IniParser::getValue<double>(const std::string & section, const std::string & name) {
	if (!is_load) throw file_not_loaded();
	if (checkName(section, name))
		return atof(iniFile[section][name].c_str());
	throw name_not_found();
}

template<>
inline std::string IniParser::getValue<std::string>(const std::string & section, const std::string & name) {
	if (!is_load) throw file_not_loaded();
	if (checkName(section, name))
		return iniFile[section][name];
	throw name_not_found();
}
