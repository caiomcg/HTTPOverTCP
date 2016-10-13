#include "../include/TCP.h"

TCP::TCP(SocketFamily family, SocketUser user, int port)  : user(user), serverFileDescriptor(0), clientFileDescriptor(0) {
	if (!createSocket(family, user)) {
			throw TCPError("Socket Creation Error.");
	}

	struct sockaddr_in* address = &(user == SocketUser::CLIENT ? clientAddress : serverAddress);

	memset((char*)address, 0, sizeof(*address));
	address->sin_family = (family == SocketFamily::IPV4 ? AF_INET : AF_INET6);
    address->sin_port   = htons(port);
    address->sin_addr.s_addr = INADDR_ANY;

    slen = sizeof(*address);

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















