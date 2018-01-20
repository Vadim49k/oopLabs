#pragma once

class invalid_type : public std::exception
{
public:
	virtual char* what() throw() {
		return  "Invalid parameter type\n";
	}
};