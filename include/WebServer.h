#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include "../include/Utils.h"
#include "../include/HTTP.h"
#include "../include/TCP.h"

#include <thread>
#include <error.h>

class WebServer {
private:
	TCP* tcp;

	bool keepListening;
	int newClient;
public:
	WebServer(const std::string serverName, const int port = 5000);
	~WebServer();

	void run();
	void prepareClient(const int client);
};

#endif // define WEB_SERVER_H