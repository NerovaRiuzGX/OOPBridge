//TCPClient.cpp
//by NerovaRiuzGX 2018.01.03

#include "TCPClient.h"

TCPClient::TCPClient () {
	sock = -1;
	port = 0;
	address = "";
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
			cout<<"Failed to resolve hostname\n";
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
	
	connect(sock, (struct sockaddr *)&server, sizeof(server));

	return true;
}

bool TCPClient::sendMessage (string data) {
	
	if (send(sock, data.c_str(), strlen(data.c_str()), 0) < 0) {
		cout << "Send failed: " << data << endl;
		return false;
	}

	return true;
}

string TCPClient::receive (int size) {
	
	char buffer[4096];

	if (recv(sock, buffer, size, 0) < 0) {
		cout << "Receive failed." << endl;
	}

	buffer[size] = '\0';
	return string(buffer);
}