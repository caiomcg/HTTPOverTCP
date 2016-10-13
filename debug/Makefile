CC = g++
CFLAGS = -std=c++11
INCLUDE_PATH = ../include/
SRC_PATH = ../src/
EXE = WebServer

all: HTTP.o TCPError.o TCP.o
	$(CC) $(CFLAGS) *.o $(SRC_PATH)main.cpp -o $(EXE)

HTTP.o: $(INCLUDE_PATH)HTTP.h $(SRC_PATH)HTTP.cpp
	$(CC) $(CFLAGS) $(SRC_PATH)HTTP.cpp -c

TCP.o: $(INCLUDE_PATH)TCP.h $(SRC_PATH)TCP.cpp
	$(CC) $(CFLAGS) $(SRC_PATH)TCP.cpp -c

TCPError.o: $(INCLUDE_PATH)TCPError.h $(SRC_PATH)TCPError.cpp
	$(CC) $(CFLAGS) $(SRC_PATH)TCPError.cpp -c

.PHONY: clean distclean

clean:
	rm -rf *.o

distclean: clean
	rm -rf $(EXE)