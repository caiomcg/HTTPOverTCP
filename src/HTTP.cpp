#include "../include/HTTP.h"


HTTP* HTTP::p_instance = nullptr;


HTTP::HTTP() {

}

HTTP::~HTTP() {
}

HTTP* HTTP::getInstance() {
	if (p_instance == nullptr) {
		p_instance = new HTTP();
	}
	return p_instance;
}