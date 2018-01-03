//TCPServer.cpp
//by NerovaRiuzGX 2017.12.30

#include "TCPServer.h"

string TCPServer::Message;

void * TCPServer::Task (void *arg) {
	
	int n;
	int clientSocket = (long)arg;
	char data[4096];
	pthread_detach(pthread_self());
	
	while (true) {
		n = recv(clientSocket, data, 4096, 0);
		if (n==0) {
			closesocket(clientSocket);
			break;
		}
		data[n]=0;
		Message = string(data);
	}
	return 0;
}

void TCPServer::setup (int port) {
	WORD wVersion;
	WSADATA wsaData;
	wVersion = MAKEWORD(2,2);
	WSAStartup(wVersion, &wsaData);
	
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	
	if (serverSocket == -1) {
		cout << "Failed to create socket." << endl;	//err
	}
	
	//server socket settings
	memset(&serverInfo, 0, sizeof(serverInfo));
	serverInfo.sin_family = PF_INET;
	serverInfo.sin_addr.s_addr = INADDR_ANY;
	serverInfo.sin_port = htons(port);
	
	bind(serverSocket, (struct sockaddr *)&serverInfo, sizeof(serverInfo));
	listen(serverSocket, 5);
	cout << "Server started." << endl;	//start msg
}

string TCPServer::receive() {
	
	char str[20];
	while (true) {
		int addrlen = sizeof(clientInfo);
		clientSocket = accept(serverSocket, (struct sockaddr *)&clientInfo, &addrlen);
		inet_ntop(AF_INET, &(clientInfo.sin_addr), str, INET_ADDRSTRLEN);
		pthread_create(&serverThread, NULL, &Task, (void *)clientSocket);
	}
	return string(str);
}

string TCPServer::getMessage() {
	
	return Message;
}

void TCPServer::sendMessage (string dat) {
	
	send(clientSocket, dat.c_str(), dat.length(), 0);
}

void TCPServer::clean() {
	
	Message = "";
	memset(data, 0, sizeof(data));
}

void TCPServer::detach() {
	
	closesocket(serverSocket);
	closesocket(clientSocket);
	WSACleanup();
}