#pragma once

class invalid_format : public std::exception
{
public:
	virtual char* what() throw() {
		return  "Format error file\n";
	}
};