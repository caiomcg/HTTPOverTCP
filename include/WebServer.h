#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include "../include/Utils.h"
#include "../include/HTTP.h"
#include "../include/TCP.h"

#include <thread>
#include <chrono>
#include <error.h>
#include <fstream>

class WebServer {
private:
	TCP* _tcp;

	bool _keepListening;

	std::string _fileRequested;

public:
	WebServer(const std::string serverName, const int port = 5000);
	~WebServer();

	void run();
	void prepareClient(const int client);
};

#endif // define WEB_SERVER_H