#ifndef HTTP_H
#define HTTP_H

#include <regex>
#include <functional>
#include <fstream>
#include <ctime>
#include <string>
#include <iostream>
#include "../include/Utils.h"

#define MAX_SIZE 10142330 //10MB

enum HTTPStatus{
	OK=200,
	PARTIAL_CONTENT=206,
	FOUND = 302,
	NOT_MODIFIED = 304,
	TEMPORARY_REDIRECT = 307,
	BAD_REQUEST = 400,
	UNAUTHORIZED = 401,
	FORBIDDEN = 403,
	NOT_FOUND = 404,
	INTERNAL_SERVER_ERROR = 500,
	NOT_IMPLEMENTD = 501,
	SERVICE_UNAVEILABLE = 503,
	PERMISSION_DENIED = 550
};

class HTTP {
private:

	size_t   _packetBytes;
	uint8_t*  _packetBuffer;

	size_t   _fileBytes;
	uint8_t* _fileBuffer;

	std::string _httpType;

	std::string _requestedFile;
	std::string _requestedFileType;

	std::string _filePath;
	std::string _response;

	std::string findPath(std::string& in, std::string message);
	std::string httpDate();

public:
	HTTP();
	~HTTP();

	bool fileExists(const std::string filePath);
	uint8_t* processMessage(const uint8_t* buffer, std::function<uint8_t* (const std::string&, const std::string, std::string&)> function);
	void createResponseHeader(const int statusCode);
	uint8_t* preparePacket();
	size_t getPacketSize() const;
	std::string getHTTPHeader() const;
};

#endif // Define HTTP_H