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
		_httpType = "GET";
		Utils::verbose("INFO", "GET: " + findPath(message, "GET"));

		_requestedFile = findPath(message, "GET");

		if (_requestedFile == "/") {
	        _requestedFile = "/index.html";
	        _requestedFileType = "text/html; charset=UTF-8";
	    } else {
	        std::string filetype = _requestedFile.substr(_requestedFile.rfind(".", _requestedFile.length() - 1) + 1, _requestedFile.length() - 1);

	        if(!filetype.compare("html") || !filetype.compare("htm"))
	            _requestedFileType = "text/html; charset=UTF-8";
	        else if(!filetype.compare("jpg"))
	            _requestedFileType = "image/jpg";
	        else if(!filetype.compare("png"))
	            _requestedFileType = "image/png";
	        else if(!filetype.compare("gif"))
	            _requestedFileType = "image/gif";
	        else if(!filetype.compare("ico"))
				_requestedFileType = "image/x-icon";
	        else if(!filetype.compare("mp3"))
	            _requestedFileType = "audio/mpeg";
	        else if(!filetype.compare("wav"))
	            _requestedFileType = "audio/wav";
	        else if(!filetype.compare("mp4"))
	            _requestedFileType = "video/mp4";
	        else if(!filetype.compare("webm"))
	            _requestedFileType = "video/webm";
	        else if(!filetype.compare("ogg"))
	            _requestedFileType = "video/ogg";
	        else if(!filetype.compare("json"))
	            _requestedFileType = "application/json; charset=UTF-8";
	        else if(!filetype.compare("js"))
	            _requestedFileType = "application/javascript; charset=UTF-8";
	        else if(!filetype.compare("css"))
	            _requestedFileType = "text/css";
	        else
	            _requestedFileType = "application/octet-stream";
	    }
		return function(_requestedFile, "GET", message);
	} 
	if (message.find("POST") != std::string::npos) {
		_httpType = "POST";
		Utils::verbose("INFO", "POST: " + findPath(message, "POST"));
		return function(findPath(message, "POST"), "POST", message);
	} 
	if (message.find("PUT") != std::string::npos) {
		_httpType = "PUT";
		Utils::verbose("INFO", "PUT: " + findPath(message, "PUT"));
		return function(findPath(message, "PUT"), "PUT", message);
	} 
	if (message.find("DELETE") != std::string::npos) {
		_httpType = "DELETE";
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

bool HTTP::onlyFileExists(const std::string filePath) {
	std::ifstream input(filePath);
	Utils::verbose("DEBUG", "Searching File: " + filePath);
	if (!input.is_open()) {
		Utils::verbose("ERROR", "Bad file");
		input.close();
		return false;
	}
	input.close();
	return true;
}

void HTTP::createResponseHeader(const int statusCode){
	_response = "HTTP/1.1 " + std::to_string(statusCode) + "\n";
	std::string message("");
	std::string jump("\n");

	if (statusCode == HTTPStatus::NOT_FOUND) {
		_requestedFileType = "text/html; charset=UTF-8";
		message =  "<!DOCTYPE HTML> <html> <head> <title>404 Not Found</title> </head> <body> <h1>Not Found</h1>  <p>The requested URL " + _requestedFile + " was not found on this server.</p> </body> </html>";
	}
	if (_httpType == "POST") {
		_requestedFileType = "application/json; charset=UTF-8";
		if (statusCode == HTTPStatus::OK) {
			message = "{\"Insert\": \"OK\"}";
			_fileBytes = message.size();
		} else {
			message = "{\"Insert\": \"FAIL\"}";
		}
	}
	if (_httpType == "PUT") {
		_requestedFileType = "application/json; charset=UTF-8";
		if (statusCode == HTTPStatus::OK) {
			message = "{\"Insert\": \"OK\"}";
			_fileBytes = message.size();
		} else {
			message = "{\"Insert\": \"FAIL\"}";
		}
	}
	if (_httpType == "DELETE") {
		_requestedFileType = "application/json; charset=UTF-8";
		if (statusCode == HTTPStatus::OK) {
			message = "{\"DELETE\": \"OK\"}";
			_fileBytes = message.size();
		} else {
			message = "{\"DELETE\": \"FAIL\"}";
		}
	}
	_response += "Access-Control-Allow-Origin: *" + jump;
	_response += "Access-Control-Allow-Headers: X-Requested-With, Content-Type, X-Codingpedia, X-HTTP-Method-Override" + jump;
	_response += "x-content-type-options: nosniff" + jump;
	_response += "Date: " + httpDate() + jump;
	_response += "Response: " + std::string("SimpleHTTPServerC++/0.0.1 (Unix)") + jump; //Allow to modify the server name.
	_response += "Content-Location: " + _requestedFile + jump;
	_response += "Connection: " + std::string("close") + jump; //Change close to a var type.
	_response += "Content-Length: " + std::to_string((statusCode != HTTPStatus::OK) ? message.length() : _fileBytes) + jump;
	_response += "Content-Type: " + _requestedFileType + jump;//std::string("text/html; charset=utf-8") + jump; //Variable type;
	_response += "Cache-Control: public, max-age=0" + jump;
	_response += "Server: " + std::string("SimpleHTTPServerC++/0.0.1 (Unix)") + jump + jump;

	_response += message;

	Utils::verbose("DEBUG", _response);
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

std::string HTTP::getHTTPHeader() const {
	return _response;
}