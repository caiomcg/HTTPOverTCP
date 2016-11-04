#include "../include/Utils.h"

void Utils::verbose(const std::string type, const std::string message) {
	#ifdef VERBOSE_ON

	std::string color;

	if (type == "INFO") {
		color = "\x1b[35m";
	} else if (type == "DEBUG") {
		color = "\x1b[33m";
	} else if (type == "ERROR") {
		color = "\x1b[31m";
	}

	std::clog << color << "[" << type << "] " << message << "\x1b[0m" << std::endl;
	#endif
}