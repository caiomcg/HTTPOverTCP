/**
 * @file WebServer.h
 * 
 * @class WebServer
 *
 * @brief Server manager
 *        
 * This Class manages the connections with the help
 * of the HTTP and TCP classes.
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

#ifndef WEB_SERVER_H
#define WEB_SERVER_H

// C++ Headers
//---------------------------------------------------------------------------------------------
#include <thread>			  // STD thread.
#include <fstream>			  // File manipulation.
//---------------------------------------------------------------------------------------------

// Unix Headers
//---------------------------------------------------------------------------------------------
#include <error.h>			  // Unix error.
//---------------------------------------------------------------------------------------------

// Custom Headers
//---------------------------------------------------------------------------------------------
#include "../include/Utils.h" // Utility class.
#include "../include/HTTP.h"  // HTTP class.
#include "../include/TCP.h"   // TCP class.
//---------------------------------------------------------------------------------------------


class WebServer {
private:
	TCP* _tcp; // TCP instance.

	bool _keepListening; // Keep the server running.

public:
	/**
	 * @brief Server constructor.
	 * @details Initiates the server and calls the TCP constructor.
	 * 
	 * @param serverName The name of the server.
	 * @param port The port to run the server
	 */
	WebServer(const std::string serverName, const int port = 8888);
	/**
	 * @brief Default destructor.
	 * @details Release alloced memory.
	 */
	~WebServer();

	/**
	 * @brief Run the server.
	 */
	void run();

	/**
	 * @brief Callback for the client threads.
	 * 
	 * @param client The client descriptor.
	 */
	void prepareClient(const int client);
};

#endif // define WEB_SERVER_H