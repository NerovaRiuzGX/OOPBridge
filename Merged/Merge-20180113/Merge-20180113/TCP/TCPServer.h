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
		TCPServer();
		virtual void setup (string = "", int = 0);
		
		virtual void detach();
		string getIP();
		int acceptConn();

		virtual int sendMessage (string, int); //from TCPClient
		virtual string receiveMessage (int);

	private:
		int serverSocket;
		struct sockaddr_in serverInfo;
		struct sockaddr_in clientInfo;
};

#endif /* TCPSERVER_H */