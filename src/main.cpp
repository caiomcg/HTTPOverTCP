#include "../include/WebServer.h"
#include <signal.h>

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

int main(int argc, char** argv) {
	WebServer* server = nullptr;

	if (argc == 1) {
		usage();
		return 1;
	}

	try {
		server = new WebServer("LP3", atoi(argv[1]));
		server->run();
	} catch (TCPError error) {
		std::cerr << "What(): " << error.what() << std::endl;
	}

	delete server;
	return 0;
}