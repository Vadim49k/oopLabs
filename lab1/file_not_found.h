#pragma once

class file_not_found : public std::exception
{
public:
	//invalid_format(char const* const message)throw() {}
	virtual char* what() throw() {
		return  "File not found\n";
	}
};