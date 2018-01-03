//Server.cpp
//by NerovaRiuzGX 2017.12.30

#include "TCPServer.h"

#define MAXUSERCOUNT 4

int connectCount = 0;

TCPServer server;

void * loop (void * new_sock) {

	char data[4096]; //receive data buffer
	int sock = (long)new_sock;

	pthread_detach(pthread_self());

	while (true) {
		int length = recv(sock, data, 4096, 0);

		if (length==0 || length==SOCKET_ERROR) {
			break;
		}
		else {
			data[length]='\0';
			cout << "From user " << sock << ", Message: " << string(data) << endl;
			server.sendMessage("received.", sock); //server send back
		}
		
	}
	closesocket(sock);
	cout << endl << "===============" << endl;
	cout << "User " << sock << " disconnect." << endl;
	cout << "===============" << endl << endl;
	connectCount--;
	pthread_exit(NULL);
	return 0;
}

int main () {
	
	pthread_t thread;
	server.setup(10555);
	int new_sock;
	while ( (new_sock = server.acceptConn()) != -1 ) {

		cout << endl << "===============" << endl;

		if (connectCount < MAXUSERCOUNT) {
			pthread_create(&thread, NULL, loop, (void *)new_sock);
			cout << "User " << new_sock << " online." << endl;
			connectCount++;
		}
		else {
			closesocket(new_sock);
			cout << "Client connection denied." << endl;
		}

		cout << "Online users: " << connectCount << endl;
		cout << "===============" << endl << endl;

	}
	server.detach(); //close server

	return 0;
}