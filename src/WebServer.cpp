#include "../include/WebServer.h"

WebServer::WebServer(const std::string serverName, const int port) : _tcp(nullptr), keepListening(false) {
	this->_tcp = new TCP(SocketFamily::IPV4, SocketUser::SERVER, port);
}

WebServer::~WebServer() {
	if (_tcp != nullptr) {
		delete _tcp;
		_tcp = nullptr;
	}
}

void WebServer::run() {
	this->keepListening = true;
	int client = 0;

	if (!_tcp->listenTo()) {
		Utils::verbose("INFO", "Socket is listening at port: " + std::to_string(_tcp->getPort()));

		while (keepListening) {
			if ((client = _tcp->acceptConnection()) >= 0) {
				Utils::verbose("INFO", "Accepted connection");
				std::thread(&WebServer::prepareClient, this, client).detach();
			}
		}
	} else {
		Utils::verbose("ERROR", "Failed to listen for connections");
	}
}

void WebServer::prepareClient(const int client) {
	uint8_t* buffer = new uint8_t[MAX_SIZE];
	HTTP* http = new HTTP();

	std::string responseHeader;
	bool validFile = false;
	int response = 0;


	if ((response = TCP::receivedata(client, buffer, MAX_SIZE)) >= 0) {

		std::cerr << "BUFFER: " << "\n" << (char*)buffer << std::endl;

		uint8_t* packet = http->processMessage(buffer, [http](const std::string& path, const std::string type, std::string& buffer) -> uint8_t* {
			bool exists = false;

			Utils::verbose("DEBUG", buffer);

			if (type == "GET") {
				exists = http->fileExistsAndAd(path);

				http->createResponseHeader((!exists ? HTTPStatus::NOT_FOUND : HTTPStatus::OK));
			} else if (type == "POST") {
				buffer = buffer.substr(buffer.find("\r\n\r\n"));
				buffer = buffer.erase(0,2);

				std::cout << "======" << std::endl;
				std::cout << buffer << std::endl;
				std::cout << "======" << std::endl;

				std::ofstream output("." + path, std::ios_base::out | std::ios_base::binary);
				if (output.is_open()) {
					output.write(buffer.c_str(), sizeof(char) * buffer.size());
					http->createResponseHeader(HTTPStatus::OK);
				} else {
					http->createResponseHeader(HTTPStatus::INTERNAL_SERVER_ERROR);
				}
				output.close();
				
			} else if (type == "PUT") {
				buffer = buffer.substr(buffer.find("\r\n\r\n"));
				buffer = buffer.erase(0,2);

				std::cout << "======" << std::endl;
				std::cout << buffer << std::endl;
				std::cout << "======" << std::endl;

				if (http->onlyFileExists("." + path)) {
					std::ofstream output("." + path, std::ios_base::out | std::ios_base::binary);
					if (output.is_open()) {
						output.write(buffer.c_str(), sizeof(char) * buffer.size());
						http->createResponseHeader(HTTPStatus::OK);
					} else {
						http->createResponseHeader(HTTPStatus::INTERNAL_SERVER_ERROR);
					}
					output.close();
				} else {
					http->createResponseHeader(HTTPStatus::BAD_REQUEST);
				}
				
			} else if (type == "DELETE") {
				std::string file = "." + path;

				buffer = buffer.substr(buffer.find("\r\n\r\n"));
				buffer = buffer.erase(0,2);

				if (http->onlyFileExists(file)) {
					if (remove(file.c_str()) != 0) {
						http->createResponseHeader(HTTPStatus::INTERNAL_SERVER_ERROR);
					} else {
						http->createResponseHeader(HTTPStatus::OK);
					}
				} else {
					http->createResponseHeader(HTTPStatus::BAD_REQUEST);
				}

			} else {
				http->createResponseHeader(HTTPStatus::NOT_FOUND);
			}
			return http->preparePacket(); 
		});

		TCP::sendData(client, packet, http->getPacketSize());
	}
	
	if (!TCP::closeWithIdentifier(client)) {
		Utils::verbose("ERROR", "Failed to close client socket");
	} else {
		Utils::verbose("DEBUG", "Closed the socket");
	}

	if (buffer != nullptr) {
		delete [] buffer;
	}
	if (http != nullptr) {
		delete http;
	}
}	