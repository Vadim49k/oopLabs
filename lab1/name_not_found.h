#pragma once

class name_not_found : public std::exception
{
public:
	virtual char* what() throw() {
		return  "Not found a pair (SECTION, PARAMETER) of the Ini file\n";
	}
};