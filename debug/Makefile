CC = g++
CFLAGS = -std=c++11 -pthread
INCLUDE_PATH = ../include/
SRC_PATH = ../src/
EXE = WebServer

ifeq ($(VERBOSE), true)
VFLAGS += -D VERBOSE_ON
endif

all: Utils.o HTTP.o TCPError.o TCP.o WebServer.o
	$(CC) $(CFLAGS) *.o $(SRC_PATH)main.cpp -o $(EXE)

Utils.o: $(INCLUDE_PATH)Utils.h $(SRC_PATH)Utils.cpp
	$(CC) $(CFLAGS) $(VFLAGS) $(SRC_PATH)Utils.cpp -c

HTTP.o: $(INCLUDE_PATH)HTTP.h $(SRC_PATH)HTTP.cpp
	$(CC) $(CFLAGS) $(SRC_PATH)HTTP.cpp -c

TCP.o: $(INCLUDE_PATH)TCP.h $(SRC_PATH)TCP.cpp
	$(CC) $(CFLAGS) $(SRC_PATH)TCP.cpp -c

TCPError.o: $(INCLUDE_PATH)TCPError.h $(SRC_PATH)TCPError.cpp
	$(CC) $(CFLAGS) $(SRC_PATH)TCPError.cpp -c

WebServer.o: $(INCLUDE_PATH)WebServer.h $(SRC_PATH)WebServer.cpp
	$(CC) $(CFLAGS) $(SRC_PATH)WebServer.cpp -c

.PHONY: clean distclean

clean:
	rm -rf *.o

distclean: clean
	rm -rf $(EXE)