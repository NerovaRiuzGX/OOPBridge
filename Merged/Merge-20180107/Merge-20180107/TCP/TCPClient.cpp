//TCPClient.cpp
//by NerovaRiuzGX 2018.01.03

#include "TCPClient.h"

TCPClient::TCPClient (): TCPServer() {
	sock = -1;
}

void TCPClient::setup (string address, int port) {

	/*WORD wVersion;
	WSADATA wsaData;
	wVersion = MAKEWORD(2,2);
	WSAStartup(wVersion, &wsaData);*/
	
	
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		cout << "Failed to create socket." << endl;
	}
	

	if (inet_addr(address.c_str()) == -1) {
		struct hostent *he;
		struct in_addr **addr_list;
		if ((he = gethostbyname(address.c_str())) == NULL) {
			cout << "Failed to resolve hostname." << endl;
			return;
		}
		addr_list = (struct in_addr **) he->h_addr_list;
		for (int i=0; addr_list[i] != NULL; i++) {
			server.sin_addr = *addr_list[i];
			break;
		}
	}
	else {
		server.sin_addr.s_addr = inet_addr(address.c_str());
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	if ( connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0 ) {
		cout << "Connection failed." << endl;
		return;
	}

	return;
}

int TCPClient::sendMessage (string data, int tmp) {
	
	int length = send(sock, data.c_str(), strlen(data.c_str()), 0);
	if (length==0 || length==SOCKET_ERROR) {
		cout << "Send failed." << endl;
		return -1;
	}

	return length;
}

string TCPClient::receiveMessage (int tmp) {
	
	char buffer[4096];
	int length = recv(sock, buffer, 4096, 0); 

	if (length==0 || length==SOCKET_ERROR) {
		cout << "Receive failed." << endl;
		return "";
	}
	else {
		buffer[length] = '\0';
		//cout << "Server response: " << string(buffer) << endl << endl;
	}

	return string(buffer);
}

void TCPClient::detach () {
	closesocket(sock);
	WSACleanup();
	return;
}