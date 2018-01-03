//Client.cpp
//by NerovaRiuzGX 2018.01.03

#include <iostream>

#include "TCPClient.h"

int main (int argc, char *argv[]) {

	TCPClient tcp;
	string ip;
	cout << "Enter IP: ";
	cin >> ip;
	while (true) {
		tcp.setup(ip, 10555);
		string data;
		cout << "Send data: ";
		getline(cin, data);
		if (data[0]=='\'') {
			break;
		}
		tcp.sendMessage(data);
		string rec = tcp.receive();

		if (rec != "") {
			cout << rec << endl;
		}
	}

	closesocket(tcp.sock);
	WSACleanup();
	exit(0);
	return 0;
	
}
