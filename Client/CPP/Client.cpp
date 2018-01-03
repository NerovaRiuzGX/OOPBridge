//Client.cpp
//by NerovaRiuzGX 2018.01.03

#include "TCPClient.h"

TCPClient tcp;

int main () {

	string ip;
	cout << "Enter destination IP: ";
	getline(cin, ip);
	tcp.setup(ip, 10555);
	cout << "===============" << endl;
	cout << "Type \"@\" to close the client." << endl << endl;
	while (true) {
		
		string data;
		cout << "Send data: ";
		getline(cin, data);
		if (data[0]=='@') {
			cout << "Client closed by user." << endl;
			break;
		}

		if (!tcp.sendMessage(data)) {
			cout << "Client terminated by server." << endl;
			break;
		}

		if (!tcp.receive()) {
			cout << "Client terminated by server." << endl;
			break;
		}
		
	}
	closesocket(tcp.sock);
	WSACleanup();
	system("pause");
	return 0;
}
