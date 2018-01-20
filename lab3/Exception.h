#pragma once

#include <exception>
#include <string>

class WavException : public std::exception {
public:
	WavException(std::string err_msg) : err_msg(err_msg) {};

	//const char *what() const;
	const virtual char* what() const throw()  {
		return err_msg.c_str();
	}
private:
	std::string err_msg;
};