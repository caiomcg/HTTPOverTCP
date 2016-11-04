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
#include "../include/Utils.h"

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

	int backlog;

	socklen_t clientSize;

	struct sockaddr_in serverAddress;
	struct sockaddr_in clientAddress;

	int createSocket(const SocketFamily family, const SocketUser user);
	int bindSocket();
public:
	TCP(const SocketFamily family, SocketUser user, const int port = 5000, const int maxClient = 10);
	~TCP();

	int listenTo();

	int acceptConnection();

	int close(const int identifier);
};

#endif // define TCP_H









