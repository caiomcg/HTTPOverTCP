#include "../include/TCP.h"

TCP::TCP(SocketFamily family, SocketUser user, const int port, const int maxClient)  : user(user), serverFileDescriptor(0), clientFileDescriptor(0), backlog(maxClient), port(port), clientSize(0) {
	int identifier = 0;

	if (!createSocket(family, user)) {
		throw TCPError("Socket Creation Error.");
	}

	if (setsockopt((user == SocketUser::CLIENT ? clientFileDescriptor : serverFileDescriptor), SOL_SOCKET, SO_REUSEADDR, &identifier, sizeof(identifier)) < 0)
    	throw TCPError("Could not set socket options");


	struct sockaddr_in* address = &(user == SocketUser::CLIENT ? clientAddress : serverAddress);

	memset((char*)address, 0, sizeof(*address));
	address->sin_family = (family == SocketFamily::IPV4 ? AF_INET : AF_INET6);
    address->sin_port   = htons(port);
    address->sin_addr.s_addr = INADDR_ANY;

	if (user == SocketUser::SERVER) {
		if (!bindSocket()) {
			throw TCPError("Bind Socket Error.");
		}
	}
}

TCP::~TCP() {

}

int TCP::createSocket(SocketFamily family, SocketUser user) {
	if(((user == SocketUser::CLIENT ? clientFileDescriptor : serverFileDescriptor) = socket((family == SocketFamily::IPV4 ? AF_INET : AF_INET6), SOCK_STREAM, 0)) < 0){
		return 0;
	}
	return 1;
}

int TCP::bindSocket() {
	if(bind(serverFileDescriptor, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) < 0){
		return 0;
	}
	return 1;
}

int TCP::listenTo() {
	if (user == SocketUser::CLIENT) {
		Utils::verbose("DEBUG", "Cannot listen. The user is a client.");
		return -1;
	} 
	return listen(serverFileDescriptor, backlog);
	
}

int TCP::acceptConnection() {
	if (user == SocketUser::CLIENT) {
		Utils::verbose("DEBUG", "Cannot accept connection. The user is a client.");
		return -1;
	} 
 	return accept(serverFileDescriptor, (struct sockaddr*) &clientFileDescriptor, &clientSize);
}

int TCP::getPort() const {
	return port;
}

int TCP::receivedata(const int socketDescriptor, uint8_t* buffer, const size_t bufferLength, const unsigned int timeout) {  
	//if (timeout > 0) {
	//	struct timeval tv;
	//	
	//    tv.tv_sec  = timeout;
	//    tv.tv_usec = 0;
//
//	//    setsockopt(socketDescriptor, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
	//}

	return recv(socketDescriptor, buffer, bufferLength, 0);
}