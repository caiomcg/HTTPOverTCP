#ifndef TCP_ERROR_H
#define TCP_ERROR_H

#include <stdexcept>
#include <exception>
#include <string>

class TCPError:  public std::runtime_error{
public:
	TCPError();
	TCPError(std::string msg);
};

#endif // define TCP_ERROR_H