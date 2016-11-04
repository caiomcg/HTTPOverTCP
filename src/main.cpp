#include <iostream>
#include <new>
#include "../include/HTTP.h"
#include "../include/TCP.h"
#include "../include/Utils.h"

int main(void) {
	TCP* tcp = new TCP(SocketFamily::IPV4, SocketUser::SERVER, 5000);
	bool keepListening = true;
	int client = 0;

	uint8_t* buffer = new uint8_t[200];

	if (!tcp->listenTo()) {
		Utils::verbose("INFO", "Socket is listening");

		while (keepListening) {
			if ((client = tcp->acceptConnection()) >= 0) {
				Utils::verbose("INFO", "Accepted connection");
				int r = recv(client, buffer, 200, 0);
				Utils::verbose("INFO", "Received message: ");
				std::clog << buffer << std::endl;
			}
		}

	} else {
		Utils::verbose("ERROR", "Failed to listen for connections");
	}

	delete tcp;
	delete [] buffer;
	return 0;
}