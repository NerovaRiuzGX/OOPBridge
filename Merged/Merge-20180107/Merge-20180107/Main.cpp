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
bool* connectCheck = new bool[MAX_USER_COUNT];

pthread_mutex_t serverMutex, clientMutex;

TCPServer server;
TCPServer *client = new TCPClient;

Host host;
Player player;

void hostTask (int);
void PlayerTask();

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
	
	//thread self detach
	pthread_detach(pthread_self());

	//initiallize player position
	data = server.receiveMessage(sock);
	server.sendMessage(string(itoa(position, buffer, 10)), sock);
	delete[] buffer;

	while ((data = server.receiveMessage(sock)) != "") {
		
		//test line
		//cout << "Received data from Player " << position << endl;

		FILE.write(data);

		pthread_mutex_lock(&serverMutex); //alter Host data in this mutex lock
		//cout << "Thread of Player " << position << " access Host" << endl;
		FILE.pkgrcv(data, host);
		hostTask(position);
		data = FILE.pkgsnd(host);
		pthread_mutex_unlock(&serverMutex);

		server.sendMessage(data, sock);
	}
	closesocket(sock);

	/*cout << endl << "===============" << endl;
	cout << "User " << sock << " disconnect." << endl;
	cout << "===============" << endl << endl;*/
	connectCount--;

	pthread_exit(NULL);
	return 0;
}

void * createServer (void * serverPort) {
	
	pthread_t thread;
	
	server.setup("",(long)serverPort);
	int new_sock;
	while ( (new_sock = server.acceptConn()) != -1 ) {

		//cout << endl << "===============" << endl;

		if (connectCount < MAX_USER_COUNT) {
			connectSock[connectCount] = new_sock;
			pthread_create(&thread, NULL, serverLoop, (void *)new_sock);
			//cout << "User " << new_sock << " online." << endl;
			connectCount++;
		}
		else {
			closesocket(new_sock);
			cout << "Client connection denied." << endl;
		}

		/*cout << "Online users: " << connectCount << endl;
		cout << "===============" << endl << endl;*/

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

void * clientInterface (void *) {
		
	pthread_detach(pthread_self());

	while (true) {
		pthread_mutex_lock(&clientMutex);  //alter Host data in this mutex lock
		player.printTable();
		pthread_mutex_unlock(&clientMutex);

		PlayerTask();
	}
	pthread_exit(NULL);
	return 0;
}

void createClient (string ip) {

	client->setup(ip, 10555);
	/*cout << "===============" << endl;
	cout << "Type \"@\" to close the client." << endl << endl;*/

	FileControl FILE ("Server-To-Client.bridge");
	string data = FILE.pkgsnd(player);

	//initiallize player position
	client->sendMessage(data, NULL);
	data = client->receiveMessage(NULL);
	player.position = atoi(data.c_str());
	data = FILE.pkgsnd(player);

	pthread_t clientThread;
	pthread_create(&clientThread, NULL, clientInterface, NULL);

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
	for (int i=0; i<MAX_USER_COUNT; i++) {
		connectCheck[i] = false;
	}

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

void hostTask (int position) {
	bool found;
	switch (host.statement/10) {
		case 0: //SET
			switch (host.statement%10) {
				case 1:
				case 2:
				case 3:
					connectCheck[position] = true;
					found = false;
					for (int i=0; i<MAX_USER_COUNT; i++) {
						if (!connectCheck[i]) {
							found = !found;
							break;
						}
					}

					if (found) {
						host.statement++;
						fill(connectCheck, connectCheck + sizeof(connectCheck), false);
					}
					break;
				case 4:
					connectCheck[position] = true;
					found = false;
					for (int i=0; i<MAX_USER_COUNT; i++) {
						if (!connectCheck[i]) {
							found = !found;
							break;
						}
					}
					if (!found) {
						host.statement = 20 + (host.round-1)%4;
						fill(connectCheck, connectCheck + sizeof(connectCheck), false);
					}
					break;
			}
			break;
		case 1: //AUCTION
			switch (host.statement%10) {
				case 0:
				case 1:
				case 2:
				case 3:
					if (host.auction_log.size()==4) { //if all pass
						if(host.auction_log[0] == "PS" && host.auction_log[1] == "PS" && host.auction_log[2] == "PS" && host.auction_log[3] == "PS")
							host.statement = 4;
					}
					else if (host.auction_log.size()>4) {
						string last_call = *(find_if(host.auction_log.rbegin(), host.auction_log.rbegin()+3, [](string i){return (i!="XX" && i!="X");}));
						if (last_call=="PS") {
							host.statement = 14;
							last_call = host.auction_log[host.auction_log.size()-4];
							string last_bid = *(find_if(host.auction_log.rbegin(), host.auction_log.rbegin()+10, [](string i){return (i!="XX" && i!="X" && i!="PS");}));
							
							//set contract_suit
							if(last_bid[1] == 'C')
								host.contract_suit = 0;
							else if(last_bid[1] == 'D')
								host.contract_suit = 1;
							else if(last_bid[1] == 'H')
								host.contract_suit = 2;
							else if(last_bid[1] == 'S')
								host.contract_suit = 3;
							else
								host.contract_suit = 4;
							
							//set contract_trick
							host.contract_trick = last_bid[0] - '0' + 6;
							
							//set contract_dbl
							if(last_call != last_bid){
								if(last_call == "XX"){
									host.contract_dbl = 4;
								}
								else if(last_call == "X"){
									host.contract_dbl = 2;
								}
							}
							else
								host.contract_dbl = 1;

							//set declarer_postion
							if(host.auction_log[host.auction_log.size()-6][1] == host.contract_suit)
								host.declarer_position = (host.round%4 + host.auction_log.size() - 6)%4;
							else
								host.declarer_position = (host.round%4 + host.auction_log.size() - 4)%4;
						}
					}
					break;
				case 4:
					connectCheck[position] = true;
					found = false;
					for (int i=0; i<MAX_USER_COUNT; i++) {
						if (!connectCheck[i]) {
							found = !found;
							break;
						}
					}
					if (!found) {
						host.statement = 30 + (host.declarer_position+3)%4;
						fill(connectCheck, connectCheck + sizeof(connectCheck), false);
					}
					break;
			}
		case 2: //PLAY
			switch (host.statement%10){
				case 0:
				case 1:
				case 2:
				case 3:

					break;
				case 4:

					break;
			}
		case 3: //RESULT
		case 4: //CLAIM
		default: /*exit();*/ break;
	}

	return;
}

void PlayerTask()
{
	char pos[4] = {'N', 'E', 'S', 'W'};
	if(player.statement/10==1)
	{
		if(	player.position==player.statement%10	)
		{
			player.bid();		
		}
		else
		{
			cout<<"Waiting for player to bid  "<<pos[player.statement%10]<<" !!";
			player.decideBid="00";
		}
	}
	else if(player.statement/10==2)
	{
		if(	player.position==player.statement%10	)
		{
			player.play();
		}
		else
		{
			cout<<"Waiting for player to play card  "<<pos[player.statement%10]<<" !!";
			player.decideCard="00";
		}
	}
}