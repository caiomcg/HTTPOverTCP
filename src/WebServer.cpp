#include "../include/WebServer.h"

WebServer::WebServer(const std::string serverName, const int port) : _tcp(nullptr), _keepListening(false), _fileRequested("") {
	this->_tcp = new TCP(SocketFamily::IPV4, SocketUser::SERVER, port);
}

WebServer::~WebServer() {
	if (_tcp != nullptr) {
		delete _tcp;
		_tcp = nullptr;
	}
}

void WebServer::run() {
	this->_keepListening = true;
	int client = 0;

	if (!_tcp->listenTo()) {
		Utils::verbose("INFO", "Socket is listening at port: " + std::to_string(_tcp->getPort()));

		while (_keepListening) {
			if ((client = _tcp->acceptConnection()) >= 0) {
				Utils::verbose("INFO", "Accepted connection");
				std::thread ([=](){ 
					WebServer::prepareClient(client); 
				}).detach();
			}
		}
	} else {
		Utils::verbose("ERROR", "Failed to listen for connections");
	}
}

void WebServer::prepareClient(const int client) {
	uint8_t* buffer = new uint8_t[65535];
	HTTP* http = new HTTP();

	std::string responseHeader;
	bool validFile = false;
	int response = 0;


	if ((response = TCP::receivedata(client, buffer, 65535)) >= 0) {
		Utils::verbose("DEBUG", "Text received");

		uint8_t* packet = http->processMessage(buffer, [http](const std::string& path, const std::string type, std::string& buffer) -> uint8_t* {
			bool exists = false;
				
			exists = http->fileExists(path);

			http->createResponseHeader(path, (!exists ? HTTPStatus::NOT_FOUND : HTTPStatus::OK));
			
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