//Main.cpp
//Merged with 5 classes, version 20180107

#include "Host\Host.h"
#include "Player\Player.h"
#include "FileControl\FileControl.h"
#include "TCP\TCPServer.h"
#include "TCP\TCPClient.h"

#define MAX_USER_COUNT 4

int connectCount = 0;
int connectSock[4] = {};

pthread_mutex_t serverMutex, clientMutex;

TCPServer server;
TCPServer *client = new TCPClient;

Host host;
Player player;

void * serverLoop (void * new_sock) {

	string data;
	int sock = (long)new_sock;
	int position = -1;

	//get position
	for (int i=0; i<4; i++) {
		if (connectSock[i] == sock) {
			position = i; break;
		}
	}

	char *buffer = new char[5];
	FileControl FILE("Player" + string(itoa(position, buffer, 10)) + "-To-Server.bridge");
	delete[] buffer;

	//thread self detach
	pthread_detach(pthread_self());

	while ((data = server.receiveMessage(sock)) != "") {
		
		//test line
		//cout << "Received data from Player " << position << endl;

		FILE.write(data);

		pthread_mutex_lock(&serverMutex); //alter Host data in this mutex lock
		cout << "Thread of Player " << position << " access Host" << endl;
		FILE.pkgrcv(data, host);
		data = FILE.pkgsnd(host);
		pthread_mutex_unlock(&serverMutex);

		server.sendMessage(data, sock);
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

		if (connectCount < MAX_USER_COUNT) {
			connectSock[connectCount] = new_sock;
			pthread_create(&thread, NULL, serverLoop, (void *)new_sock);
			cout << "User " << new_sock << " online." << endl;
			connectCount++;
		}
		else {
			closesocket(new_sock);
			cout << "Client connection denied." << endl;
		}

		cout << "Online users: " << connectCount << endl;
		cout << "===============" << endl << endl;

		if (connectCount==MAX_USER_COUNT && host.statement==0) {
			pthread_mutex_lock(&serverMutex);  //alter Host data in this mutex lock
			host.statement = 1;
			cout << "Server thread access Host" << endl;
			pthread_mutex_unlock(&serverMutex);
		}
		

	}

	pthread_mutex_destroy(&serverMutex);

	server.detach(); //close server
	pthread_exit(NULL);
	return 0;
}

void createClient (string ip) {

	client->setup(ip, 10555);
	/*cout << "===============" << endl;
	cout << "Type \"@\" to close the client." << endl << endl;*/

	FileControl FILE ("Server-To-Client.bridge");
	string data = FILE.pkgsnd(player);

	Sleep(1000);

	while (true) {

		/*cout << "Send data: ";
		getline(cin, data);
		if (data[0]=='@') {
			cout << "Client closed by user." << endl;
			break;
		}*/

		if (client->sendMessage(data, NULL) == SOCKET_ERROR) {
			cout << "Client terminated by server." << endl;
			break;
		}

		//cout << client->receiveMessage(0) << endl;

		data = client->receiveMessage(NULL);
		FILE.write(data);

		pthread_mutex_lock(&clientMutex);  //alter Host data in this mutex lock
		FILE.pkgrcv(data, player);
		data = FILE.pkgsnd(player);
		pthread_mutex_unlock(&clientMutex);

		Sleep(500);
	}

	pthread_mutex_destroy(&clientMutex);
	client->detach();
	system("pause");
	return;
}

void main () {
	cout << "(1) I'm a server.\n(2) I'm a client." << endl << "Choose one: ";

	pthread_mutex_init(&serverMutex, NULL);
	pthread_mutex_init(&clientMutex, NULL);

	switch (getchar()) {
		case '1':
			pthread_t serverThread;
			pthread_create(&serverThread, NULL, createServer, (void *)10555);
			Sleep(1000);
			createClient("127.0.0.1");
			break;

		case '2':
			fflush(stdin);
			string ip;
			cout << "Enter destination IP: ";
			getline(cin, ip);
			createClient(ip);
			break;
	}
	
}