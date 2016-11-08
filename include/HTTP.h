#ifndef HTTP_H
#define HTTP_H

#include <regex>
#include <ctime>
#include "../include/Utils.h"

enum SUCCESS {
	OK=200
};

enum REDIRECTION {
	FOUND = 302,
	NOT_MODIFIED = 304,
	TEMPORARY_REDIRECT = 307
};

enum CLIENT_ERROR {
	BAD_REQUEST = 400,
	UNAUTHORIZED = 401,
	FORBIDDEN = 403,
	NOT_FOUND = 404
};

enum SERVER_ERROR {
	INTERNAL_SERVER_ERROR = 500,
	NOT_IMPLEMENTD = 501,
	SERVICE_UNAVEILABLE = 503,
	PERMISSION_DENIED = 550
};

class HTTP {
private:
	size_t   buffer_size;    
	uint8_t* buffer;

	std::string findPath(std::string& in, std::string message);
	bool findData();
	std::string httpDate();

public:
	HTTP();
	~HTTP();

	std::string processMessage(const uint8_t* buffer);
	std::string createResponseHeader(const size_t length, const std::string path, const int statusCode);
};

#endif // Define HTTP_H