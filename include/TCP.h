#ifndef TCP_H
#define TCP_H

//Networking Headers
//---------------------------------------------------------------------------------------------
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
//---------------------------------------------------------------------------------------------

#include <cstring>

#include "../include/TCPError.h"

typedef int(*CallbackFuction)(char* data, int size, int error);

enum SocketFamily{
	IPV4,
	IPV6
};

enum SocketUser{
	CLIENT,
	SERVER
};

class TCP {
private:
	SocketUser user;

	int serverFileDescriptor;
	int clientFileDescriptor;

	struct sockaddr_in serverAddress;
	struct sockaddr_in clientAddress;

	socklen_t slen;

	int createSocket(SocketFamily family, SocketUser user);
	int bindSocket();
public:
	TCP(SocketFamily family, SocketUser user, int port = 5000);
	~TCP();
};

#endif // define TCP_H









