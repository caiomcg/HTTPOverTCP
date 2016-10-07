#include <iostream>
#include <new>
#include "../include/HTTP.h"

int main(void) {
	HTTP* http = HTTP::getInstance();
	delete http;
	return 0;
}