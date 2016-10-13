#include <iostream>
#include <new>
#include "../include/HTTP.h"
#include "../include/TCP.h"

int main(void) {
	HTTP* http = HTTP::getInstance();
	TCP* tcp = new TCP(SocketFamily::IPV4, SocketUser::SERVER, 5000);


	delete http;
	return 0;
}