//TCPServer.cpp
//by NerovaRiuzGX 2017.12.30

#include "TCPServer.h"

TCPServer::TCPServer () {

	//basic settings for windwows socket programming
	WORD wVersion;
	WSADATA wsaData;
	wVersion = MAKEWORD(2,2);
	WSAStartup(wVersion, &wsaData);
}

void TCPServer::setup (string tmp, int port) {
	
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
	//cout << "Server started." << endl;	//start msg
	getIP();
}

int TCPServer::acceptConn () { //accepting connections through this function
	char str[20];
	int addrlen = sizeof(clientInfo);
	int conn = accept(serverSocket, (struct sockaddr *)&clientInfo, &addrlen);
	inet_ntop(AF_INET, &(clientInfo.sin_addr), str, INET_ADDRSTRLEN);
	return conn;
}

int TCPServer::sendMessage (string dat, int sock) {
	
	int length =  send(sock, dat.c_str(), dat.length(), 0);

	//if error
	if (length==0 || length==SOCKET_ERROR) {
		cout << "Send failed." << endl;
		return -1;
	}

	return length;
}

void TCPServer::detach() { //close socket
	
	closesocket(serverSocket);
	WSACleanup();
}

string TCPServer::getIP () { //this function returns the IP of your computer (IPv4)
	string IP;
    char hostname[80];
    if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR) {
        cerr << "Error " << WSAGetLastError() <<
                " when getting local host name." << endl;
        return "";
    }
    //cout << "Host name is " << hostname << "." << endl;

    struct hostent *hostip = gethostbyname(hostname);
    if (hostip == 0) {
        cerr << "Bad host lookup." << endl;
        return "";
    }

    for (int i = 0; hostip->h_addr_list[i] != 0; ++i) {
        struct in_addr addr;
        memcpy(&addr, hostip->h_addr_list[i], sizeof(struct in_addr));
		IP = inet_ntoa(addr);
        //cout << "Server IP address: " << IP << endl;
    }
	return IP;
}

string TCPServer::receiveMessage (int sock) {
	
	char buffer[4096];
	int length = recv(sock, buffer, 4096, 0); 

	//if error
	if (length==0 || length==SOCKET_ERROR) {
		cout << "Receive failed." << endl;
		return "";
	}
	else { //transform string into char-array type
		buffer[length] = '\0';
		//cout << "Server response: " << string(buffer) << endl << endl;
	}

	return string(buffer);
}