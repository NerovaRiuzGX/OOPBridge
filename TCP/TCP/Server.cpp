//Server.cpp
//by NerovaRiuzGX 2017.12.30

#include <conio.h>

#include "TCPServer.h"

#include "TCPClient.h"

#define MAXUSERCOUNT 4

int connectCount = 0;

TCPServer server;

//TCPServer *client = new TCPClient;


void * loop (void * new_sock) {

	string data;
	//char data[4096]; //receive data buffer
	int sock = (long)new_sock;

	pthread_detach(pthread_self());

	while ((data = server.receiveMessage(sock)) != "") {
		

		//data[length]='\0';
		cout << "From user " << sock << ", Message: " << data << endl;
		server.sendMessage("received.", sock); //server send back
		
		
	}
	closesocket(sock);
	cout << endl << "===============" << endl;
	cout << "User " << sock << " disconnect." << endl;
	cout << "===============" << endl << endl;
	connectCount--;
	pthread_exit(NULL);
	return 0;
}

void * createServer (void * serverPort) {
	
	pthread_t thread;
	
	server.setup("",(long)serverPort);
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
	pthread_exit(NULL);
	return 0;
}

void main () {
	
	cout << "(1) I'm a server.\n(2) I'm a client." << endl << "Choose one: ";
	
	switch (getch()) {
		case '1':
			pthread_t gameThread;
			pthread_create(&gameThread, NULL, createServer, (void *)10555);
			int a;
			cin >> a;
			break;

		case '2':
			TCPServer *client = new TCPClient;

			string ip;
			cout << "Enter destination IP: ";
			getline(cin, ip);
			client->setup(ip, 10555);
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

				if (!client->sendMessage(data, 0)) {
					cout << "Client terminated by server." << endl;
					break;
				}

				cout << client->receiveMessage(0) << endl;
		
			}
			client->detach();
			system("pause");
			break;
	}
	return;
}