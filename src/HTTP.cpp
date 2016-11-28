#include "../include/HTTP.h"


HTTP::HTTP() : _packetBytes(0), _packetBuffer(nullptr), _fileBytes(0), _fileBuffer(nullptr), _filePath("") {

}

HTTP::~HTTP() {
	if (_packetBuffer != nullptr) {
		delete[] _packetBuffer;
		_packetBuffer = nullptr;
	}
	if (_fileBuffer != nullptr) {
		delete[] _fileBuffer;
		_fileBuffer = nullptr;
	}
}

std::string HTTP::findPath(std::string& in, std::string message) {
	std::string result;
	try {
		std::regex re(message + " (.*) ");
		std::smatch match;
		if (std::regex_search(in, match, re) && match.size() > 1) {
			result = match.str(1);
		} else {
			result = std::string("");
		} 
	} catch (std::regex_error& e) {
		Utils::verbose("ERROR", "Failed to use regex");
	}

	return result;
}

std::string HTTP::httpDate(){
	time_t now = time(0);
	char buf[300];
	struct tm tm = *gmtime(&now);

	strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S %Z", &tm);

	return std::string(buf);
}

uint8_t* HTTP::processMessage(const uint8_t* buffer, std::function<uint8_t* (const std::string&, const std::string, std::string&)> function) {
	std::string message((char*)buffer);

	if (message.find("GET") != std::string::npos) {
		Utils::verbose("INFO", "GET: " + findPath(message, "GET"));
		return function(findPath(message, "GET"), "GET", message);
	} 
	if (message.find("POST") != std::string::npos) {
		Utils::verbose("INFO", "POST: " + findPath(message, "POST"));
		return function(findPath(message, "POST"), "POST", message);
	} 
	if (message.find("PUT") != std::string::npos) {
		Utils::verbose("INFO", "PUT: " + findPath(message, "PUT"));
		return function(findPath(message, "PUT"), "PUT", message);
	} 
	if (message.find("DELETE") != std::string::npos) {
		Utils::verbose("INFO", "DELETE: " + findPath(message, "DELETE"));
		return function(findPath(message, "DELETE"), "DELETE", message);
	}

	return function("", "", message);
}

bool HTTP::fileExists(const std::string filePath) {
	std::ifstream input("." + filePath, std::ios::binary | std::ios::in);
	Utils::verbose("DEBUG", "Searching File: " + filePath);
	if (!input.is_open()) {
		Utils::verbose("DEBUG", "File not found");
		_fileBytes = 0;
		input.close();
		return false;
	}

	input.seekg(0, input.end);
   	_fileBytes = input.tellg();
   	input.seekg(0, input.beg);

   	_fileBuffer = new uint8_t[_fileBytes];

   	input.read((char*)_fileBuffer, _fileBytes);

   	Utils::verbose("DEBUG", "File with size: " + std::to_string(_fileBytes));

	input.close();

	return true;
}

void HTTP::createResponseHeader(const std::string path, const int statusCode){
	_response = "HTTP/1.1 " + std::to_string(statusCode) + "\n";
	std::string message("");
	std::string jump("\n");

	this->_filePath = path;

	if (statusCode == HTTPStatus::NOT_FOUND) {
		message =  "<!DOCTYPE HTML> <html> <head> <title>404 Not Found</title> </head> <body> <h1>Not Found</h1>  <p>The requested URL " + path + " was not found on this server.</p> </body> </html>";
	}
	_response += "Access-Control-Allow-Origin: *" + jump;
	_response += "Access-Control-Allow-Headers: X-Requested-With, Content-Type, X-Codingpedia, X-HTTP-Method-Override" + jump;
	_response += "x-content-type-options: nosniff" + jump;
	_response += "Date: " + httpDate() + jump;
	_response += "Response: " + std::string("SimpleHTTPServerC++/0.0.1 (Unix)") + jump; //Allow to modify the server name.
	_response += "Content-Location: " + path + jump;
	_response += "Connection: " + std::string("close") + jump; //Change close to a var type.
	_response += "Content-Length: " + std::to_string((statusCode == HTTPStatus::NOT_FOUND) ? message.length() : _fileBytes) + jump;
	_response += "Content-Type: " + std::string("/image/jpg") + jump;//std::string("text/html; charset=utf-8") + jump; //Variable type;
	_response += "Cache-Control: public, max-age=0" + jump;
	_response += "Server: " + std::string("SimpleHTTPServerC++/0.0.1 (Unix)") + jump + jump;
	Utils::verbose("DEBUG", _response);

	_response += message;
}
uint8_t* HTTP::preparePacket() {
	size_t len = 0;

	if (_fileBuffer != nullptr) {
		len = _fileBytes;
	}

	_packetBytes = _response.length() + len;
	_packetBuffer = new uint8_t[_packetBytes];

	memcpy(_packetBuffer, _response.c_str(), _response.length());
	if (len > 0) {
		memcpy(_packetBuffer + _response.length(), _fileBuffer, len);
	}

	return _packetBuffer;
}

size_t HTTP::getPacketSize() const {
	return _packetBytes;
}