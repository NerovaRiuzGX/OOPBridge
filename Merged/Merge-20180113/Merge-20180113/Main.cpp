//Main.cpp
//Merged with 5 classes, version 20180107

#include "Host\Host.h"
#include "Player\Player.h"
#include "FileControl\FileControl.h"
#include "Interface\Interface.h"
#include "TCP\TCPServer.h"
#include "TCP\TCPClient.h"

#define MAX_USER_COUNT 4

//these variables are for connections, send positions, check...etc.
int connectCount = 0;
int connectSock[4] = {};
bool* connectCheck = new bool[MAX_USER_COUNT];
bool all_refresh = false;

//mutex lock
pthread_mutex_t serverMutex, clientMutex;

TCPServer server;
TCPServer *client = new TCPClient;

Host host;
Player player;

Interface UI;

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

		FILE.write(data);

		//alter Host data in this mutex lock
		pthread_mutex_lock(&serverMutex); 

		FILE.pkgrcv(data, host);
		hostTask(position);
		data = FILE.pkgsnd(host);

		pthread_mutex_unlock(&serverMutex);

		server.sendMessage(data, sock);
	}

	closesocket(sock);
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

		//check if the table is full
		if (connectCount < MAX_USER_COUNT) {
			connectSock[connectCount] = new_sock;
			pthread_create(&thread, NULL, serverLoop, (void *)new_sock);
			connectCount++;
		}
		else { //close the connection if the table is full
			closesocket(new_sock);
			cout << "Client connection denied." << endl;
		}

		//change statement when the table is full
		if (connectCount==MAX_USER_COUNT && host.statement==0) {
			pthread_mutex_lock(&serverMutex);  //alter Host data in this mutex lock
			host.statement = 1;
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
	
	//thread self detach
	pthread_detach(pthread_self());

	//a variable that checks and prevents double input bug
	int curr_state=player.position;
	int print_state=player.statement;

	//client interface loop
	while (true) {

		//alter Host data in this mutex lock
		pthread_mutex_lock(&clientMutex); 

		//only print when the statement changes
		if (print_state!=player.statement) { 
			switch (player.statement/10) {
				case 0:
					break;
				case 1:
					system("cls");
					UI.table(player);
					UI.playercard(player);
					UI.biddingtable(player);
					UI.scoreboard(player);			
					UI.nowturn(player); 
					break;
				case 2:
					UI.table(player);
					UI.playercard(player);
					UI.dummycard(player);	 
					UI.biddingtable(player);
					UI.scoreboard(player);
					UI.contract(player);
					UI.trick(player);
					UI.card(player);
					UI.nowturn(player);
					break;
				case 3:
					UI.scoreboard(player);
					break;
			}

			print_state=player.statement;
		} // end if

		pthread_mutex_unlock(&clientMutex);

		PlayerTask(curr_state);

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

		data = client->receiveMessage(NULL);
		FILE.write(data);

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

	//output codepage 951
	SetConsoleOutputCP(951);

	//initiallize two mutex locks
	pthread_mutex_init(&serverMutex, NULL);
	pthread_mutex_init(&clientMutex, NULL);
	
	//initiallize the connection check array
	for (int i=0; i<MAX_USER_COUNT; i++) {
		connectCheck[i] = false;
	}

	int choice = UI.gamemodeoption();

	if (choice == 1) {
		switch (UI.multiplayeroption()) {
			case 0: //create
				UI.createtable(server);

				//open another thread for server
				pthread_t serverThread;
				pthread_create(&serverThread, NULL, createServer, (void *)10555);
				Sleep(1000);
				createClient("127.0.0.1");
				break;

			case 1: //join
				createClient(UI.jointable());
				break;
		}
	}
	else {
		UI.gametable(player);
		system("pause");
	}
}

void hostTask (int position) { //what Host should do whenever it receives a package
	char suit[5] = {'C', 'D', 'H', 'S', 'N'};

	//requirements for PLAY
	int total_trick = host.ns_trick+host.ew_trick;
	string turn_max = host.trick_log[total_trick][0]; 
	int max_player=0;

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
					if (host.auction_log.size()==4 && host.auction_log[0]=="PS") { //if all pass
						if(host.auction_log[0] == "PS" && host.auction_log[1] == "PS" && host.auction_log[2] == "PS" && host.auction_log[3] == "PS") {
							host.statement = 4;
							break;
						}
					}
					if (host.auction_log.size()>=4) {
						string last_call = *(find_if(host.auction_log.rbegin(), host.auction_log.rbegin()+2, [](string i){return (i!="PS");}));
						if (last_call=="PS") {
							host.statement = 14;
							last_call = host.auction_log[host.auction_log.size()-4];
							string last_bid = *(find_if(host.auction_log.rbegin(), (host.auction_log.size()>10 ? host.auction_log.rbegin()+10 : host.auction_log.rend() ), [](string i){return (i!="XX" && i!="X" && i!="PS");}));
							
							//set contract_suit
							switch (last_bid[1]) {
								case 'C': host.contract_suit = 0; break;
								case 'D': host.contract_suit = 1; break;
								case 'H': host.contract_suit = 2; break;
								case 'S': host.contract_suit = 3; break;
								default: host.contract_suit = 4; break;
							}
							
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
			break;
		case 2: //PLAY
			switch (host.statement%10){
				case 0:
				case 1:
				case 2:
				case 3:
					//initial checks
					if (host.turn != 4) {break;}
					if (!Check(position)) {break;}

					if (host.contract_suit == 4) { //for NT
						for (int i=1; i<4; i++) {
							if ( turn_max[0] == host.trick_log[total_trick][i][0] ) {
								if (host.CardToInt(turn_max) < host.CardToInt(host.trick_log[total_trick][i])) {
									turn_max = host.trick_log[total_trick][i];
									max_player = i;
								}
							}
						}
					}
					else { //other contract_suit
						for (int i=1; i<4; i++) {
							if ( turn_max[0] == host.trick_log[total_trick][i][0] ) {
								if (host.CardToInt(turn_max) < host.CardToInt(host.trick_log[total_trick][i])) {
									turn_max = host.trick_log[total_trick][i];
									max_player=i;
								}
							}
							else if (host.trick_log[total_trick][i][0] == suit[host.contract_suit]) {
								turn_max = host.trick_log[total_trick][i];
								max_player = i;
							}
						}
					}

					//set win trick
					switch ( (host.statement + max_player)%4 ) {
						case 0:
						case 2: host.ns_trick++; break;

						case 1:
						case 3: host.ew_trick++; break;
					}

					//change statement
					if (total_trick != 13) {
						host.turn = 0;
						host.statement = 25 + (host.statement + max_player) %4;
					}
					break;
				case 4:
					if (Check(position)) {
						host.statement = 30;
						fill(connectCheck, connectCheck + sizeof(connectCheck), false);
					}
					break;
				case 5:
				case 6:
				case 7:
				case 8:
					if (Check(position)) {
						if (host.ns_trick+host.ew_trick==13) {
							host.statement = 29;
						}
						else {
							host.statement-=5;
						}
						
						fill(connectCheck, connectCheck + sizeof(connectCheck), false);
					}
					break;
				case 9:
					if (Check(position)) {
						host.statement=24;
						fill(connectCheck, connectCheck + sizeof(connectCheck), false);
					}
					break;
			}
			break;
		case 3: //RESULT
			switch (host.statement%10) {
				case 0:
					host.score();
					host.statement++;
					break;
				case 1:
					host.statement++;
					break;
				case 2:
					if (Check(position)) {
						host.statement = 4;
						fill(connectCheck, connectCheck + sizeof(connectCheck), false);
					}
					break;
			}
			break;
		case 4: //CLAIM
		default: /*exit();*/ break;
	}

	return;
}

void PlayerTask(int & curr_state) //what Players should react when they receive a package
{	
	int dummy = (player.declarer_position+2)%4;
	char pos[4] = {'N', 'E', 'S', 'W'};
	if(player.statement/10==1) { //AUCTION
		if(player.statement-10==4) {
			player.decideBid="00";
			curr_state = player.position;
		}
		else if ( player.position==player.statement-10 ) {
			if (curr_state==player.statement-10) {
				do {
					player.decideBid = UI.bidding();
				} while (!player.bid(player.decideBid));
				Sleep(500);
				curr_state++;
			}
			else {
				curr_state = player.position;
				Sleep(1000);
			}
		}
		else {
			player.decideBid="00";
			curr_state = player.position;
		}
	} //end of AUCTION
	else if(player.statement/10==2) //PLAY
	{
		if (player.turn > 3 || player.statement == 29) {
			player.decideCard="00";
			curr_state = player.position;
		}
		else if ( player.position == player.statement-20 && player.statement-20 != dummy) {

			//my turn, not dummy
			if ( curr_state==player.statement-20 ) {
				do {
					player.decideCard = UI.playcard();
				} while (!player.playCard(player.decideCard));
				Sleep(500);
				curr_state++;
			}
			else {
				curr_state = player.position;
				Sleep(1000);
			}
		}
		else if ( (player.statement-20 == dummy) && (player.position == player.declarer_position) ) {

			//dummy's turn, im declarer
			if ( curr_state==player.statement-20 ) {
				do {
					player.decideCard = UI.playcard();
				} while (!player.playCard(player.decideCard));
				Sleep(500);
				curr_state++;
			}
			else {
				curr_state = ((player.position+2)%4);
				Sleep(1000);
			}
		}
		else if ( player.statement-20 >= 5 ) {
			player.decideCard="00";
			curr_state = player.statement-25;
		}
		else {
			player.decideCard="00";
			curr_state = player.position;
		}
	} // end of PLAY
	else if (player.statement/10==3) { //RESULT

	} // end of RESULT
}

bool Check (int position) { //check if everyone has received the latest package

	connectCheck[position] = true;
	bool found = false;

	for (int i=0; i<MAX_USER_COUNT; i++) {
		if (!connectCheck[i]) {
			found = !found; break;
		}
	}

	if (!found) {
		all_refresh = !all_refresh;

		if (all_refresh) {return false;}
		else {return true;}
	}
	else {
		return false;
	}
}