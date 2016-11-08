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

//C Headers
//---------------------------------------------------------------------------------------------
#include <cstring>
//---------------------------------------------------------------------------------------------

//Custom Headers
//---------------------------------------------------------------------------------------------
#include "../include/TCPError.h"
#include "../include/Utils.h"
//---------------------------------------------------------------------------------------------
//
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
	int port;

	socklen_t clientSize;

	struct sockaddr_in serverAddress;
	struct sockaddr_in clientAddress;

	/**
	 * @brief Create the socket
	 * @details Create a stream socket with IPV4 or IPV6 and client or server mode.
	 * 
	 * @param family The socket family: IPV4 or IPV6
	 * @param user The type of user:  CLIENT or SERVER
	 * 
	 * @return 1 if success
	 */
	int createSocket(const SocketFamily family, const SocketUser user);
	int bindSocket();
public:
	TCP(const SocketFamily family, SocketUser user, const int port = 5000, const int maxClient = 10);
	~TCP();

	int listenTo();

	int acceptConnection();

	int close(const int identifier);

	int getPort() const;

	static int receivedata(const int socketDescriptor, uint8_t* buffer, const size_t bufferLength, const unsigned int timeout = 10);
};

#endif // define TCP_H









