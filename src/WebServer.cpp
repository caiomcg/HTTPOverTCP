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
		Utils::verbose("INFO", "Socket is listening");

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
	uint8_t* buffer = new uint8_t[200];
	int response = 0;

	if((response = TCP::receivedata(client, buffer, 200)) >= 0) {
		Utils::verbose("DEBUG", "Text received");
		std::clog << buffer << std::endl;
	} else {
		Utils::verbose("ERROR", "Could not receive data.");
	}
	
	//PROCESS
	
	//GET DATA
	//
	//PROCESS
	//
	//

	delete [] buffer;
}	