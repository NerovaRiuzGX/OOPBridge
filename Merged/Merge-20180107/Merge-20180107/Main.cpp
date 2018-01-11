//Main.cpp
//Merged with 5 classes, version 20180107

#include "Host\Host.h"
#include "Player\Player.h"
#include "FileControl\FileControl.h"
#include "TCP\TCPServer.h"
#include "TCP\TCPClient.h"

#define MAX_USER_COUNT 4

//these variables are for connections, send positions, check...etc.
int connectCount = 0;
int connectSock[4] = {};
bool* connectCheck = new bool[MAX_USER_COUNT];

//mutex lock
pthread_mutex_t serverMutex, clientMutex;

TCPServer server;
TCPServer *client = new TCPClient;

Host host;
Player player;

void hostTask (int);
void PlayerTask (int &);
bool Check (int);

void * serverLoop (void * new_sock) { //this function handles what server thread react with each client

	string data;
	int sock = (long)new_sock;
	int position = -1;

	//send position
	for (int i=0; i<4; i++) {
		if (connectSock[i] == sock) {
			position = i; break;
		}
	}

	//generates debug data
	char *buffer = new char[5];
	FileControl FILE("Player" + string(itoa(position, buffer, 10)) + "-To-Server.bridge");
	
	//thread self detach
	pthread_detach(pthread_self());

	//initiallize player position
	data = server.receiveMessage(sock);
	server.sendMessage(string(itoa(position, buffer, 10)), sock);
	delete[] buffer; //free memory space

	//receive-send loop
	while ((data = server.receiveMessage(sock)) != "") {
		
		//test line
		//cout << "Received data from Player " << position << endl;

		FILE.write(data);

		//alter Host data in this mutex lock
		pthread_mutex_lock(&serverMutex); 
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

	//thread has to be destroyed after done
	pthread_exit(NULL);
	return 0;
}

void * createServer (void * serverPort) { //this function creates a server that can make multiple threads
	
	pthread_t thread;
	
	//socket setup
	server.setup("",(long)serverPort);
	int new_sock;
	while ( (new_sock = server.acceptConn()) != -1 ) {

		//cout << endl << "===============" << endl;

		//check if the table is full
		if (connectCount < MAX_USER_COUNT) {
			//create a loop thread and pass a socket for it
			connectSock[connectCount] = new_sock;
			pthread_create(&thread, NULL, serverLoop, (void *)new_sock);
			//cout << "User " << new_sock << " online." << endl;
			connectCount++;
		}
		else { //close the connection if the table is full
			closesocket(new_sock);
			cout << "Client connection denied." << endl;
		}

		/*cout << "Online users: " << connectCount << endl;
		cout << "===============" << endl << endl;*/

		//change statement when the table is full
		if (connectCount==MAX_USER_COUNT && host.statement==0) {
			pthread_mutex_lock(&serverMutex);  //alter Host data in this mutex lock
			host.statement = 1;
			//cout << "Server thread access Host" << endl;
			pthread_mutex_unlock(&serverMutex);
		}
		

	}

	//mutex lock has to be destroyed
	pthread_mutex_destroy(&serverMutex);

	server.detach(); //close server
	pthread_exit(NULL);
	return 0;
}

void * clientInterface (void *) { //this function handles how the interface should be showned
	
	//a variable that checks and prevents double input bug
	int curr_state=player.position;
	int print_state=player.statement;

	//thread self detach
	pthread_detach(pthread_self());

	//client interface loop
	while (true) {

		//alter Host data in this mutex lock
		pthread_mutex_lock(&clientMutex); 

		//only print when the statement changes
		if (print_state!=player.statement) { 
			player.printTable();
			print_state=player.statement;
		}
		
		PlayerTask(curr_state);
		pthread_mutex_unlock(&clientMutex);

		//grab information every 500 ms
		Sleep(500);
	}

	//thread has to be destroyed after done
	pthread_exit(NULL);
	return 0;
}

void createClient (string ip) { //this function creates a client and keep doing the send-receive loop

	//client setup, connect to the certain ip and port
	client->setup(ip, 10555);
	/*cout << "===============" << endl;
	cout << "Type \"@\" to close the client." << endl << endl;*/

	//generates debug data
	FileControl FILE ("Server-To-Client.bridge");
	string data = FILE.pkgsnd(player);

	//initiallize player position
	client->sendMessage(data, NULL);
	data = client->receiveMessage(NULL);
	player.position = atoi(data.c_str());
	data = FILE.pkgsnd(player);

	//create a client interface thread
	pthread_t clientThread;
	pthread_create(&clientThread, NULL, clientInterface, NULL);

	//start doing send-receive loop after 1 second
	Sleep(1000);

	//send-receive loop
	while (true) {

		if (client->sendMessage(data, NULL) == SOCKET_ERROR) {
			cout << "Client terminated by server." << endl;
			break;
		}

		//cout << client->receiveMessage(0) << endl;

		data = client->receiveMessage(NULL);
		FILE.write(data);

		//cout << data << '\n';

		//alter Host data in this mutex lock
		pthread_mutex_lock(&clientMutex);
		FILE.pkgrcv(data, player);
		data = FILE.pkgsnd(player);
		pthread_mutex_unlock(&clientMutex);

		//send data package every 500 ms
		Sleep(500);
	}

	//destroy mutex lock
	pthread_mutex_destroy(&clientMutex);
	client->detach();
	system("pause");
	return;
}

void main () {

	//initiallize two mutex locks
	pthread_mutex_init(&serverMutex, NULL);
	pthread_mutex_init(&clientMutex, NULL);
	
	//initiallize the connection check array
	for (int i=0; i<MAX_USER_COUNT; i++) {
		connectCheck[i] = false;
	}

	cout << "(1) I'm a server.\n(2) I'm a client." << endl << "Choose one: ";

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

void hostTask (int position) { //what Host should do whenever it receives a package
	bool found;
	char suit[5] = {'C', 'D', 'H', 'S', 'N'};
	switch (host.statement/10) {
		case 0: //SET
			switch (host.statement%10) {
				case 1:
				case 2:
				case 3:
					if (Check(position)) {
						host.statement++;
						fill(connectCheck, connectCheck + sizeof(connectCheck), false);
					}
					break;
				case 4:
					if (Check(position)) {
						host.reset();
						host.statement = 10 + (host.round-1)%4;
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
					if (host.auction_log.size()>=4) {
						string last_call = *(find_if(host.auction_log.rbegin(), host.auction_log.rbegin()+2, [](string i){return (i!="PS");}));
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
							int your_position, teammate_position;

							for(int i=host.auction_log.size()-1; i>=0; i--)
							{
								if(host.auction_log[i] == last_bid)
								{
									/*for(int j=i-2;j>=0;j-=4)
									{
										if(host.auction_log[j][1] == host.contract_suit)
										{
											host.declarer_position = (((host.round-1)%4) + j)%4;
											break;
										}
									}
									if(host.declarer_position != -1)
										host.declarer_position = ((host.round%4) + i)%4;
									break;*/
									//host.declarer_position = (((host.round-1)%4) + i)%4;
									your_position = i%4;
									teammate_position = (i+2)%4;
									break;
								}
							}

							for(int i=(your_position < teammate_position ? your_position : teammate_position); i<host.auction_log.size(); i+=2) {
								if (host.auction_log[i]!="PS" && host.auction_log[i][1] == suit[host.contract_suit]) {
									if (i%4 == your_position) {
										host.declarer_position = ( your_position + (host.round-1)%4 ) %4 ;
										break;
									}
									else {
										host.declarer_position = ( teammate_position + (host.round-1)%4 ) %4 ;
										break;
									}
								}
							}

						}
					}
					break;
				case 4:
					if (Check(position)) {
						host.statement = 20 + (host.declarer_position+1)%4;
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
					if(host.turn == 4)
					{
						int total_trick = host.ns_trick+host.ew_trick;
						string turn_max = host.trick_log[total_trick][0]; 
						int max_player=0;
						/*char turn_contract_suit = 'C';

						switch(host.contract_suit)
						{
							case 1: turn_contract_suit='D'; break;
							case 2: turn_contract_suit='H'; break;
							case 3: turn_contract_suit='S'; break;
						}*/

						if(host.contract_suit == 4) //NT
						{
							for(int i=1; i<4; i++)
							{
								if( turn_max[0] == host.trick_log[total_trick][i][0] )
								{
									//turn_max = host.CardToInt(turn_max) > host.CardToInt(host.trick_log[total_trick][i]) ? turn_max : host.trick_log[total_trick][i];
									if (host.CardToInt(turn_max) < host.CardToInt(host.trick_log[total_trick][i])) {
										turn_max = host.trick_log[total_trick][i];
										max_player=i;
									}
								}
							}
						}
						else //other contract_suit
						{
							for(int i=1; i<4; i++)
							{
								if( turn_max[0] == host.trick_log[total_trick][i][0] )
								{
									//turn_max = host.CardToInt(turn_max) > host.CardToInt(host.trick_log[total_trick][i]) ? turn_max : host.trick_log[total_trick][i];
									if (host.CardToInt(turn_max) < host.CardToInt(host.trick_log[total_trick][i])) {
										turn_max = host.trick_log[total_trick][i];
										max_player=i;
									}
								}
								else if(host.trick_log[total_trick][i][0] == suit[host.contract_suit])
								{
									turn_max = host.trick_log[total_trick][i];
									max_player = i;
								}
							}
						}
						//set win trick
						switch( (host.statement + max_player)%4 )
						{
							case 0:
							case 2:
								host.ns_trick++;
								break;
							case 1:
							case 3:
								host.ew_trick++;
								break;
						}
						//change statement
						if(total_trick != 13)
						{
							host.turn = 0;
							host.statement = 25 + (host.statement + max_player) %4;
						}
						else
						{
							host.statement = 24;
						}
					}
					break;
				case 4:
					if (Check(position)) {
						host.statement = 20;
						fill(connectCheck, connectCheck + sizeof(connectCheck), false);
					}
					break;
				default:
					if (Check(position)) {
						host.statement-=5;
						fill(connectCheck, connectCheck + sizeof(connectCheck), false);
					}
			}
		case 3: //RESULT
		case 4: //CLAIM
		default: /*exit();*/ break;
	}

	return;
}

void PlayerTask(int & curr_state) //what Players should react when they receive a package
{
	char pos[4] = {'N', 'E', 'S', 'W'};
	if(player.statement/10==1)
	{
		if(player.statement%10==4)
		{
			cout<<"Player "<<player.declarer_position<<"is declarer !!!"<<endl;
			Sleep(2000);
			curr_state = player.position;
		}
		else if ( player.position==player.statement%10 )
		{
			if (curr_state==player.statement%10) {
				player.bid();
				curr_state++;
				//Sleep(200);
			}
		}
		else
		{
			
			cout<<"Waiting for player to bid  "<<pos[player.statement%10]<<" !!";
			player.decideBid="00";
			curr_state = player.position;

		}
	}
	else if(player.statement/10==2)
	{
		if(	player.position==player.statement%10 )
		{
			if ( curr_state==player.statement%10 ) {
				player.playCard(); 
				curr_state++;
			}
			else if (player.turn == 0) {
				curr_state = player.position;
			}
		}
		else if (player.statement%10 >= 5) {
			cout << "Player " << pos[(player.statement-5)%10] << " wins the trick" << endl;
			curr_state = (player.statement-5)%10;
			Sleep(2000);
		}
		else
		{
			cout<<"Waiting for player to play card  "<<pos[player.statement%10]<<" !!";
			player.decideCard="00";
			curr_state = player.position;
		}
	}
}

bool Check (int position) { //check if everyone has received the latest package

	connectCheck[position] = true;
	bool found = false;

	for (int i=0; i<MAX_USER_COUNT; i++) {
		if (!connectCheck[i]) {
			found = !found;
			break;
		}
	}

	return !found;
}