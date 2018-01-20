#pragma once

class file_not_loaded : public std::exception
{
public:
	virtual char* what() throw() {
		return  "Ini file is not loaded\n";
	}
};