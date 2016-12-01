/**
 * @file TCP.h
 * 
 * @class TCP
 *
 * @brief TCP connection manager.
 *        
 * This Class is responsible for creating and managing TCP connections
 * for clients and servers.
 *
 * @license MIT License
 * 
 * Copyright (c) 2016 Caio Marcelo Campoy Guedes
 * 					  Nycholas de Sousa
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @author Caio Marcelo Campoy Guedes <caiomcg@gmail.com>
 * @author Nycholas de Sousa <nycholas@live.com>
 */

#ifndef TCP_H
#define TCP_H

// Networking Headers
//---------------------------------------------------------------------------------------------
#include <arpa/inet.h>   		 // Networking.
#include <netinet/in.h>  		 // Networking.
#include <sys/types.h>   		 // Networking.
#include <sys/socket.h>  		 // Networking.
#include <sys/stat.h>    		 // Networking.
#include <unistd.h>   	 		 // Networking.
//---------------------------------------------------------------------------------------------

// C Headers
//---------------------------------------------------------------------------------------------
#include <cstring> 				 // C string.
//---------------------------------------------------------------------------------------------

// Custom Headers
//---------------------------------------------------------------------------------------------
#include "../include/TCPError.h" // TCP class.
#include "../include/Utils.h"    // Utility class.
//---------------------------------------------------------------------------------------------

/**
 * @brief Socket Family.
 *
 * The possible socket families.
 */
enum SocketFamily{
	IPV4,
	IPV6
};
/**
 * @brief Socket user.
 *
 * The type of socket user.
 */
enum SocketUser{
	CLIENT,
	SERVER
};

class TCP {
private:
	SocketUser user;        		  // Socket user type

	int serverFileDescriptor; 		  // Server file descriptor.
	int clientFileDescriptor;		  // Client file descriptor.

	int backlog; 					  // The maximum ammount of connected clients.
	int port;	 					  // The server port.

	socklen_t clientSize;			  // Sockaddr_in size.

	struct sockaddr_in serverAddress; // Server structure;
	struct sockaddr_in clientAddress; // Clientstructure;

	/**
	 * @brief Create the socket.
	 * @details Create a stream socket with IPV4 or IPV6 and client or server mode.
	 * 
	 * @param family The socket family: IPV4 or IPV6.
	 * @param user The type of user:  CLIENT or SERVER.
	 * 
	 * @return 1 if success.
	 */
	int createSocket(const SocketFamily family, const SocketUser user);

	/**
	 * @brief Bind the socket to a port. 
	 * @details Only possible in client mode.
	 * 
	 * @return 1 is success.
	 */
	int bindSocket();
public:
	/**
	 * @brief The class constructor
	 * @details Initiates the socket and bind the port if necessary.
	 * 
	 * @param family Socket family.
	 * @param user Socket user.
	 * @param port Server port[If a server is selected].
	 * @param maxClient Maximum ammount of clients[If a server is selected].
	 */
	TCP(const SocketFamily family, SocketUser user, const int port = 5000, const int maxClient = 10);
	/**
	 * @brief Default destructor
	 */
	~TCP();

	/**
	 * @brief Listen to a connection.
	 * @details Prepare the socket to listen to connections.
	 * 
	 * @return 0 if successful.
	 */
	int listenTo();
	/**
	 * @brief Accept a connection.
	 * @details Accept a connection and return the file descriptor.
	 * 
	 * @return The file descriptor.
	 */
	int acceptConnection();

	/**
	 * @brief Close the main socket.
	 * 
	 * @return True if successful.
	 */
	bool closeSocket();

	/**
	 * @brief Get the running port.
	 * 
	 * @return The running port.
	 */
	int getPort() const;

	/**
	 * @brief Close a specific socket.
	 * @details Close a socket by its identifier.
	 * 
	 * @param identifier Socket identifier.
	 * @return true if successfuly closed.
	 */
	static bool closeWithIdentifier(const int identifier = -1);

	/**
 	* @brief Receive data from a socket.
 	* @details Receive the data from a descriptor and stores
 	* its content on the desired buffer.
 	* 
 	* @param socketDescriptor The socket descriptor.
 	* @param buffer The buffer to store the data.
 	* @param bufferLength The size of the buffer.
 	* @param int The timeout for the socket.
 	* 
 	* @return The socket response.
 	*/
	static int receivedata(const int socketDescriptor, uint8_t* buffer, const size_t bufferLength, const unsigned int timeout = 10);
	
	/**
	 * @brief Send data from a socket.
	 * @details Send data from a descriptor.
	 * 
	 * @param socketDescriptor The socket to send the data.
	 * @param buffer The data to send.
	 * @param bufferLength The size of the data.
	 * 
	 * @return The socket response.
	 */
	static int sendData(const int socketDescriptor, const uint8_t* buffer, const size_t bufferLength);
};

#endif // define TCP_H