#include "../include/HTTP.h"


HTTP::HTTP() {}

HTTP::~HTTP() {}

std::string HTTP::httpDate(){
	time_t now = time(0);
	char buf[300];
	struct tm tm = *gmtime(&now);

	strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S %Z", &tm);

	return std::string(buf);
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

std::string HTTP::processMessage(const uint8_t* buffer) {
	std::string message((char*)buffer);
	if (message.find("GET") != std::string::npos) {
		Utils::verbose("INFO", findPath(message, "GET"));
		return findPath(message, "GET");
	}
	if (message.find("POST") != std::string::npos) {
		Utils::verbose("INFO", findPath(message, "POST"));
		return findPath(message, "POST");
	}
	if (message.find("PUT") != std::string::npos) {
		Utils::verbose("INFO", findPath(message, "PUT"));
		return findPath(message, "PUT");
	}
	if (message.find("DELETE") != std::string::npos) {
		Utils::verbose("INFO", findPath(message, "DELETE"));
		return findPath(message, "DELETE");
	}
	return std::string();
}

std::string HTTP::createResponseHeader(const size_t length, const std::string path, const int statusCode){
	std::string response = "HTTP/1.1 " + std::to_string(statusCode) + "\n";
	std::string message("");
	std::string jump("\n");

	if (statusCode == CLIENT_ERROR::NOT_FOUND || statusCode == SUCCESS::OK) {
		message =  "<!DOCTYPE HTML> <html> <head> <title>404 Not Found</title> </head> <body> <h1>Not Found</h1>  <p>The requested URL " + path + " was not found on this server.</p> </body> </html>";
	}
	
	response += "Date: " + httpDate() + jump;
	response += "Response: " + std::string("SimpleHTTPServerC++/0.0.1 (Unix)") + jump; //Allow to modify the server name.
	response += "Content-Location: " + path + jump;
	response += "Connection: " + std::string("close") + jump; //Change close to a var type.
	response += "Content-Length: " + std::to_string((statusCode == CLIENT_ERROR::NOT_FOUND) ? message.length() : message.length()) + jump;
	response += "Content-Type: " + std::string("text/html; charset=utf-8") + jump; //Variable type;
	response += "Cache-Control: public, max-age=0" + jump;
	response += "Server: " + std::string("SimpleHTTPServerC++/0.0.1 (Unix)") + jump + jump;
	Utils::verbose("DEBUG", response);

	response += message;

	return response;
}