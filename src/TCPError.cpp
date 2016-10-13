#include "../include/TCPError.h"

TCPError::TCPError() : runtime_error("TCP socket error.") {}
TCPError::TCPError(std::string msg) : runtime_error(msg.c_str()) {}