//TCPClient.h
//by NerovaRiuzGX 2018.01.03

#ifndef TCPCLIENT_H
#define TCHCLIENT_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <WS2tcpip.h>
#include <WinSock.h> //for tcp socket
#include <winsock2.h> //for tcp socket
#include <windows.h> //for tcp socket

#pragma comment(lib, "Ws2_32.lib") //for tcp socket

using namespace std;

class TCPClient {

	public:
		TCPClient();
		bool setup (string, int);
		bool sendMessage (string);
		string receive (int = 4096);
		int sock;

	private:
		string address;
		int port;
		struct sockaddr_in server;
};

#endif /* TCPCLIENT_H */