//TCPServer.cpp
//by NerovaRiuzGX 2017.12.30

#include "TCPServer.h"

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
	getIP();
}

int TCPServer::acceptConn () {
	char str[20];
	int addrlen = sizeof(clientInfo);
	int conn = accept(serverSocket, (struct sockaddr *)&clientInfo, &addrlen);
	inet_ntop(AF_INET, &(clientInfo.sin_addr), str, INET_ADDRSTRLEN);
	return conn;
}

void TCPServer::sendMessage (string dat, int sock) {
	
	send(sock, dat.c_str(), dat.length(), 0);
}

void TCPServer::detach() {
	
	closesocket(serverSocket);
	WSACleanup();
}

void TCPServer::getIP () {
    char hostname[80];
    if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR) {
        cerr << "Error " << WSAGetLastError() <<
                " when getting local host name." << endl;
        return;
    }
    cout << "Host name is " << hostname << "." << endl;

    struct hostent *hostip = gethostbyname(hostname);
    if (hostip == 0) {
        cerr << "Bad host lookup." << endl;
        return;
    }

    for (int i = 0; hostip->h_addr_list[i] != 0; ++i) {
        struct in_addr addr;
        memcpy(&addr, hostip->h_addr_list[i], sizeof(struct in_addr));
		serverIP = inet_ntoa(addr);
        cout << "Server IP address: " << serverIP << endl;
    }
	return;
}