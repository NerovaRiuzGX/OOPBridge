//TCPServer.h
//by NerovaRiuzGX 2017.12.30
#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <WS2tcpip.h>
#include <winsock2.h> //for tcp socket
#include <windows.h> //for tcp socket

#include "pthread.h"

#pragma comment(lib, "Ws2_32.lib") //for tcp socket
#pragma comment(lib, "pthreadVC2.lib")

using namespace std;

class TCPServer {
	public:
		void setup (int port);
		void sendMessage (string, int);
		void detach();
		void getIP();
		int acceptConn();

		int serverSocket;
		struct sockaddr_in serverInfo;
		struct sockaddr_in clientInfo;
};

#endif /* TCPSERVER_H */