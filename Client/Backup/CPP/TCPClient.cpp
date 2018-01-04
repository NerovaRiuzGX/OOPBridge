//TCPClient.cpp
//by NerovaRiuzGX 2018.01.03

#include "TCPClient.h"

TCPClient::TCPClient () {
	sock = -1;
}

bool TCPClient::setup (string address, int port) {

	WORD wVersion;
	WSADATA wsaData;
	wVersion = MAKEWORD(2,2);
	WSAStartup(wVersion, &wsaData);
	
	if (sock == -1) {
		sock = socket(AF_INET, SOCK_STREAM, 0);
		if (sock == -1) {
			cout << "Failed to create socket." << endl;
		}
	}

	if (inet_addr(address.c_str()) == -1) {
		struct hostent *he;
		struct in_addr **addr_list;
		if ((he = gethostbyname(address.c_str())) == NULL) {
			cout << "Failed to resolve hostname." << endl;
			return false;
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
		return false;
	}

	return true;
}

bool TCPClient::sendMessage (string data) {
	
	int length = send(sock, data.c_str(), strlen(data.c_str()), 0);
	if (length==0 || length==SOCKET_ERROR) {
		cout << "Send failed." << endl;
		return false;
	}

	return true;
}

bool TCPClient::receive (int size) {
	
	char buffer[4096];
	int length = recv(sock, buffer, size, 0); 

	if (length==0 || length==SOCKET_ERROR) {
		cout << "Receive failed." << endl;
		return false;
	}
	else {
		buffer[length] = '\0';
		cout << "Server response: " << string(buffer) << endl << endl;
	}

	return true;
}