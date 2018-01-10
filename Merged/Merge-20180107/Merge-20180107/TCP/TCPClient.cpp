//TCPClient.cpp
//by NerovaRiuzGX 2018.01.03

#include "TCPClient.h"

TCPClient::TCPClient (): TCPServer() {
	sock = -1;
}

void TCPClient::setup (string address, int port) {

	//this part is now moved to TCPServer's constructor
	/*WORD wVersion;
	WSADATA wsaData;
	wVersion = MAKEWORD(2,2);
	WSAStartup(wVersion, &wsaData);*/
	
	//create a socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		cout << "Failed to create socket." << endl;
	}
	
	//resolve host ip address
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

	//socket settings: IPv4, port
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	//connect
	if ( connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0 ) {
		cout << "Connection failed." << endl;
		return;
	}

	return;
}

int TCPClient::sendMessage (string data, int tmp) {
	
	int length = send(sock, data.c_str(), strlen(data.c_str()), 0);

	//if error
	if (length==0 || length==SOCKET_ERROR) {
		cout << "Send failed." << endl;
		return -1;
	}

	return length;
}

string TCPClient::receiveMessage (int tmp) {
	
	char buffer[4096];
	int length = recv(sock, buffer, 4096, 0); 

	//iferror
	if (length==0 || length==SOCKET_ERROR) {
		cout << "Receive failed." << endl;
		return "";
	}
	else { //transfrom string into char-array type
		buffer[length] = '\0';
		//cout << "Server response: " << string(buffer) << endl << endl; //debugging
	}

	return string(buffer);
}

void TCPClient::detach () { //close the socket
	closesocket(sock);
	WSACleanup();
	return;
}