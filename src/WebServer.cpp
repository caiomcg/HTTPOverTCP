#include "../include/WebServer.h"

WebServer::WebServer(const std::string serverName, const int port) : tcp(nullptr), keepListening(false), newClient(0) {
	this->tcp = new TCP(SocketFamily::IPV4, SocketUser::SERVER, port);
}

WebServer::~WebServer() {
	if (tcp != nullptr) {
		delete tcp;
	}
}

void WebServer::run() {
	this->keepListening = true;
	int client = 0;

	if (!tcp->listenTo()) {
		Utils::verbose("INFO", "Socket is listening at port: " + std::to_string(tcp->getPort()));

		while (keepListening) {
			if ((client = tcp->acceptConnection()) >= 0) {
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

	int response = 0;

	if ((response = TCP::receivedata(client, buffer, 65535)) >= 0) {
		Utils::verbose("DEBUG", "Text received");
		std::cout << (char*)buffer << std::endl;
		std::string endpoint = http->processMessage(buffer);
		if (!endpoint.empty()) {
			std::string responseHeader = http->createResponseHeader(1, endpoint, SUCCESS::OK);
			TCP::sendData(client, (uint8_t*)responseHeader.c_str(), responseHeader.length());
		}
	} else {
		Utils::verbose("ERROR", "Could not receive data.");
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