#ifndef HTTP_H
#define HTTP_H

#include <new>

class HTTP {
private:
	static HTTP* p_instance;
	
	HTTP();
public:
	static HTTP* getInstance();

	~HTTP();
};

#endif // Define HTTP_H