#include "..\lab1\IniParser.h"
#include <exception>

IniParser::IniParser() {
	//is_load = 0;
}
IniParser::IniParser(const std::string& file) {
	loadFile(file);
}
IniParser::~IniParser() {
	iniFile.clear();
}

void IniParser::loadFile(const std::string& file) {
	is_load = 0;
	iniFile.clear();

	if (!((file[file.length() - 4] == '.') &&
		(file[file.length() - 3] == 'i') &&
		(file[file.length() - 2] == 'n') &&
		(file[file.length() - 1] == 'i'))) throw invalid_format();
	std::ifstream fin(file);
	if (!fin.is_open()) throw file_not_found();

	is_load = true;
	std::string str, temp, name, val;
	std::string curSection;
	/*
	while (fin >> str) {
		if (str == "") {}
		else if (str[0] == ';') { getline(fin, temp); }
		else if (str[0] == '[') { curSection = str.substr(1, str.length() - 2); }
		else {
			fin >> temp >> val;
			if (temp != "=") continue;
			iniFile[curSection][str] = val;
		}
	}
	*/
	while (getline(fin, str)) {
		for (int i = 0; i < str.length(); i++) {
			if (str[i] == '\n') break;
			else if (str[i] == ' ') continue;
			else if (str[i] == ';') break;
			else if (str[i] == '[') {
				curSection = "";
				i++;
				while (str[i] != ']') {
					curSection += str[i];
					i++;
				}
				break;
			}
			else {
				name = "";
				val = "";
				while (str[i] != '=' && str[i] != ' ') {
					name += str[i];
					i++;
				}
				if (str[i] == ' ')
					while (str[i] != '=')
						i++;
				if (str[i] == '=') i++;
				while (str[i] == ' ')
					i++;
				while ((str[i] != ' ') && (str[i] != ';') && (str[i] != '\n') && (i < str.length())) {
					val += str[i];
					i++;
				}
				iniFile[curSection][name] = val;

				break;
			}
		}
	}
	fin.close();
}
bool IniParser::isLoad() const {
	return is_load;
}
bool IniParser::checkSection(const std::string& section) const {
	if (!is_load) throw file_not_loaded();
	for (auto it = iniFile.begin(); it != iniFile.end(); it++)
		if (it->first == section)
			return true;
	return false;
}
bool IniParser::checkName(const std::string& section, const std::string& name) const {
	if (!is_load) throw file_not_loaded();
	for (auto it = iniFile.begin(); it != iniFile.end(); it++)
		if (it->first == section)
			for (auto jt = it->second.begin(); jt != it->second.end(); jt++)
				if (jt->first == name)
					return true;
	return false;
}
/*void IniParser::getFile() const
{
	for (auto it = iniFile.begin(); it != iniFile.end(); ++it)
	{
		std::cout << it->first << "\n";
		for (auto jt = it->second.begin(); jt != it->second.end(); jt++)
		{
			std::cout << jt->first << " = " << jt->second << "\n";
		}
		std::cout << "\n";
	}
}*/
