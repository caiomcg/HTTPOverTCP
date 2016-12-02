/**
 * @file main.cpp
 *
 * @brief The file containing the main function.
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

#include "../include/WebServer.h"
#include <csignal>

WebServer* server = nullptr; // Global server instance.

void usage(void) {
	std::cout << "\033[1;37mNAME\033[0m" << std::endl;
    std::cout << "        WebServer - A simple C++ HTTP server." << std::endl;
	std::cout << "\033[1;37mSYNOPSIS\033[0m" << std::endl;
    std::cout << "        WebServer [SERVER_PORT]" << std::endl;
    std::cout << "\033[1;37mEXIT STATUS\033[0m" << std::endl;
    std::cout << "        0 - If ok" << std::endl;
    std::cout << "        1 - If a problem occured" << std::endl;
    std::cout << "\033[1;37mUSE EXAMPLE\033[0m" << std::endl;
    std::cout << "        \033[0;35m./WebServer 8080\033[0m" << std::endl;
}

void signalHandler( int signum ) {
	if (server != nullptr) {
		server->keepListening = false; //Stop server;
		delete server;
		server = nullptr;
	};
}

int main(int argc, char** argv) {
	if (argc == 1) {
		usage();
		return 1;
	}

	std::signal(SIGINT, signalHandler);

	try {
		server = new WebServer("LP3", atoi(argv[1]));
		server->run();
	} catch (TCPError error) {
		std::cerr << "What(): " << error.what() << std::endl;
	}

	if (server != nullptr) {
		server->keepListening = false; //Stop server;
		delete server;
	}
	return 0;
}