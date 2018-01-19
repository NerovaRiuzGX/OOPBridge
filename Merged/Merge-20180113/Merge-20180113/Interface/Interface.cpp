#include "Interface.h"
using namespace std;

string Interface::pos[4]={"Ｎ","Ｅ","Ｓ","Ｗ"};

Interface::Interface()
{
	modechoose = 72;
	modeconfirm = 0;
	gamechoose = 72;
	gamestart = 0;
}

int Interface::gamemodeoption()
{
	PlaySound(TEXT(".\\BGM\\background.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
	system("mode con: cols=100 lines=25");
	system("color 2f");
	cout<<"\n\n\n\n\n\n"             
		<<"	██████╗  ██████╗  ██╗██████╗    █████╗  ██████╗\n"
		<<"	██╔══██╗██╔══██╗██║██╔══██╗██╔═══╝  ██╔═══╝\n"
		<<"	██████╔╝██████╔╝██║██║    ██║██║  ███╗█████╗  \n"
		<<"	██╔══██╗██╔══██╗██║██║    ██║██║    ██║██╔══╝  \n"
		<<"	██████╔╝██║    ██║██║██████╔╝╚█████╔╝██████╗\n"
		<<"	╚═════╝  ╚═╝    ╚═╝╚═╝╚═════╝    ╚════╝  ╚═════╝\n\n"<<endl;
	cout<<"                                        ★  SINGLE PLAYER\n                                            MULTI PLAYERS\n\n\n\n\n\n\n"<<endl;
	while(1)
	{
		modeconfirm=modechoose;
		modechoose=getch();
		if(modechoose==72)
		{
			gotoxy(40,14);
			cout<<"★";
			gotoxy(40,15);
			cout<<"  ";
			gotoxy(0,23);
		}
		if(modechoose==80)
		{
			gotoxy(40,15);
			cout<<"★";
			gotoxy(40,14);
			cout<<"  ";
			gotoxy(0,23);
		}
		if(modechoose==13)
		{
			break;	
		}
	}
	if(modechoose==13&&modeconfirm==80)
	{
		return 1; //multi
	}
	else
	{
		return 0;
	}
	setcolor(colorcode(15,2));
}

int Interface::multiplayeroption()
{
	system("cls");
	if(modechoose==13&&modeconfirm==80)
	{
		cout<<"\n\n\n\n\n\n\n\n\n                                         MULTI PLAYER MODE\n\n\n"
				<<"                                          ★  CREATE\n                                               JOIN\n\n\n\n\n\n\n\n\n"<<endl;
		while(1)
		{
			gamestart=gamechoose;
			gamechoose=getch();
			if(gamechoose==72)
			{
				gotoxy(42,12);
				cout<<"★";
				gotoxy(43,13);
				cout<<"  ";
				gotoxy(0,23);
			}
			if(gamechoose==80)
			{
				gotoxy(43,13);
				cout<<"★";
				gotoxy(42,12);
				cout<<"  ";
				gotoxy(0,23);
			}
			if(gamechoose==13)
			{
				break;
			}
		}
	}
	else
	{
		cout<<"error"<<endl;
	}
	if(gamechoose==13&&gamestart==72)
	{
		return 0; //create
	}
	if(gamechoose==13&&gamestart==80)
	{
		return 1; //join
	}
	setcolor(colorcode(15,2));
}

void Interface::createtable (TCPServer & server)
{
	system("cls");
	if(gamechoose==13&&gamestart==72)
	{
		cout<<"\n\n\n\n\n\n\n\n\n                                     YOUR IP IS "<<server.getIP()
			<<"\n\n                                        WAITING FOR PLAYERS"<<endl;
		gotoxy(0,23);
	}
	else
	{
		cout<<"error"<<endl;
	}
	setcolor(colorcode(15,2));
}

string Interface::jointable()
{
	string connectIP;//testing
	system("cls");
	cin.clear();
	if(gamechoose==13&&gamestart==80)
	{
		cout<<"\n\n\n\n\n\n\n\n\n                                        ENTER THE TABLE'S IP\n"<<endl;
		gotoxy(43,12);
		cin>>connectIP;
		gotoxy(37,15);
		cout<<"NOW LOADING PLEASE WAIT......";
		gotoxy(0,23);
	}
	else
	{
		cout<<"error";
	}
	setcolor(colorcode(15,2));
	return connectIP;
}

void Interface::gametable (Player & player)
{
	system("cls");
	setcolor(colorcode(15,2));

	table(player);
	biddingtable(player);
	scoreboard(player);
	trick(player);
	contract(player);
	playercard(player);
	dummycard(player);
	guide();
	bid_guide();
	
	gotoxy(0,23);
}

void Interface::dummycard (Player & player) { //remake
	if (player.trick_log[0][0]=="") {return;}

	int relative_declarer = (player.declarer_position - player.position + 4) % 4;
	int pos = player.position;
	char curr_suit = '0';
	int coor_y = 3;

	//clean tablesides
	gotoxy(6, 1);	cout << "                                  ";
	for (int i=3; i<20; i++) {
		gotoxy(2, i);	cout << "  ";
		gotoxy(41, i);	cout << "  ";
	}

	switch (relative_declarer) {
		case 0: //print your teammate's card when you're either declarer or dummy
		case 2:
			pos = (pos+2)%4;
			gotoxy(6, 1);
			for (int i=0; i<player.Card[pos].size(); i++) {

				//check if the suit is changed
				if (curr_suit!=player.Card[pos][i][0]) {
					if (curr_suit!='0') {
						cout << " ";
					}
					switch (player.Card[pos][i][0])	{
						case 'H': setcolor(colorcode(12, 2)); cout << " \3 "; break;
						case 'D': setcolor(colorcode(12, 2)); cout << " \4 "; break;
						case 'C': setcolor(colorcode(0, 2)); cout << " \5 "; break;
						case 'S': setcolor(colorcode(0, 2)); cout << " \6 "; break;
					}
					curr_suit=player.Card[pos][i][0];
					setcolor(colorcode(15, 2));
				}

				cout << player.Card[pos][i][1];
			}
			break;
		case 1: //declarer = left, dummy = right
		case 3: //declarer = right, dummy = left
			pos = (pos+4 - relative_declarer) %4;
			int coor_x = (relative_declarer==1 ? 41 : 2);
			for (int i=0; i<player.Card[pos].size(); i++) {
				gotoxy(coor_x, coor_y);

				//check if the suit is changed
				if (curr_suit!=player.Card[pos][i][0]) {
					switch (player.Card[pos][i][0])	{
						case 'H': setcolor(colorcode(12, 2)); cout << "\3"; coor_y++; break;
						case 'D': setcolor(colorcode(12, 2)); cout << "\4"; coor_y++; break;
						case 'C': setcolor(colorcode(0, 2)); cout << "\5"; coor_y++; break;
						case 'S': setcolor(colorcode(0, 2)); cout << "\6"; coor_y++; break;
					}
					curr_suit=player.Card[pos][i][0];
					setcolor(colorcode(15, 2));
				}
				gotoxy(coor_x, coor_y);
				cout << player.Card[pos][i][1];
				coor_y++;
			}
			break;
	} //end of switch (relative_declarer)

	//reset
	setcolor(colorcode(15, 2));
	gotoxy(0, 23);
}

void Interface::playercard (Player & player) //remake
{
	int pos = player.position;
	int curr_suit = '0';

	gotoxy(6, 21);	cout << "                                  ";
	gotoxy(6, 21);
	for (unsigned int i=0; i<player.Card[pos].size(); i++) {

		//check if the suit is changed
		if (curr_suit!=player.Card[pos][i][0]) {
			if (curr_suit!='0') {
				cout << " ";
			}
			switch (player.Card[pos][i][0])	{
				case 'H': setcolor(colorcode(12, 2)); cout << " \3 "; break;
				case 'D': setcolor(colorcode(12, 2)); cout << " \4 "; break;
				case 'C': setcolor(colorcode(0, 2)); cout << " \5 "; break;
				case 'S': setcolor(colorcode(0, 2)); cout << " \6 "; break;
			}
			curr_suit=player.Card[pos][i][0];
			setcolor(colorcode(15, 2));
		}

		cout << player.Card[pos][i][1];
	}
	setcolor(colorcode(15,2));
	gotoxy(0,23);
}

void Interface::trick (Player & player)
{
	setcolor(colorcode(0,15));
	gotoxy(61,13);	cout << "  Trick  ";
	setcolor(colorcode(0,7));
	gotoxy(61,14);	cout << "         ";
	gotoxy(61,15);	cout << "         ";

	gotoxy(63,14);	cout << "NS :" << player.ns_trick;
	gotoxy(63,15);	cout << "EW :" << player.ew_trick;

	//reset
	setcolor(colorcode(15,2));
	gotoxy(0,23);
}

void Interface::table (Player & player)
{
	gotoxy(5,3);cout<<"■■■■■■■■■■■■■■■■■";
	gotoxy(5,19);cout<<"■■■■■■■■■■■■■■■■■";
	for(int i=4;i<19;i++)
	{
		gotoxy(5,i);cout<<"■";
		gotoxy(37,i);cout<<"■";
	}

	setcolor(colorcode(15,2));
	
	gotoxy(21,19);	cout << pos[player.position];
	gotoxy(5,11);	cout << pos[(player.position+1)%4];
	gotoxy(21,3);	cout << pos[(player.position+2)%4];
	gotoxy(37,11);	cout << pos[(player.position+3)%4];

	gotoxy(0,23);
}

void Interface::contract (Player & player)
{
	setcolor(colorcode(0,15));
	gotoxy(72,8);	cout<<" Contract. ";
	setcolor(colorcode(0,7));
	gotoxy(72,9);	cout<<"           ";
	gotoxy(72,10);	cout<<"           ";
	gotoxy(72,11);	cout<<"           ";

	gotoxy(76,10);

	if(player.contract_dbl!=-1 && player.contract_suit!=-1 && player.contract_trick!=-1)
	{
		cout << player.contract_trick-6;

		switch (player.contract_suit) {
			case 0: cout << "\5"; break;
			case 1: setcolor(colorcode(12, 7)); cout << "\4"; break;
			case 2: setcolor(colorcode(12, 7)); cout << "\3"; break;
			case 3: cout << "\6"; break;
			case 4: cout << "NT"; break;
		}

		setcolor(colorcode(0,7));
		switch (player.contract_dbl) {
			case 2: cout << "X"; break;
			case 4: cout << "XX"; break;
		}
	}

	//reset
	setcolor(colorcode(15,2));
	gotoxy(0,23);
}

void Interface::biddingtable (Player & player) //remake
{
	setcolor(colorcode(15,2));

	char seat[4] = {'N', 'E', 'S', 'W'};

	gotoxy(46,3);
	for (int i=0; i<4; i++) {
		setcolor(colorcode(0,15));
		switch (i) {
			case 0:
			case 2: if (player.ns_vulnerable) {setcolor(colorcode(15,12));} break;

			case 1:
			case 3: if (player.ew_vulnerable) {setcolor(colorcode(15,12));} break;
		}

		cout << "   " << seat[i] << "  ";
	}
	
	int table_loop = (player.round-1)%4;
	int coor_x = 46 + table_loop*6;
	int coor_y = 4;

	for (int i=0; i<player.auction_log.size(); i++) {
		setcolor(colorcode(0,7));
		gotoxy(coor_x, coor_y);
		if (player.auction_log[i]=="PS") {
			cout << " PASS ";
		}
		else if (player.auction_log[i]=="XX") {
			cout << "  XX  ";
		}
		else if (player.auction_log[i]=="X") {
			cout << "   X  ";
		}
		else {
			switch (player.auction_log[i][1]) {
				case 'H': cout << "  " << player.auction_log[i][0]; setcolor(colorcode(12,7)); cout << "\3  "; break;
				case 'D': cout << "  " << player.auction_log[i][0]; setcolor(colorcode(12,7)); cout << "\4  "; break;
				case 'C': cout << "  " << player.auction_log[i][0] << "\5  "; break;
				case 'S': cout << "  " << player.auction_log[i][0] << "\6  "; break;
				default: cout << "  " << player.auction_log[i][0] << "NT "; break;
			}
		}

		table_loop = (table_loop+1)%4;
		if (table_loop==0) {coor_y++;}
		coor_x = 46 + table_loop*6;
	}

	//reset
	setcolor(colorcode(15,2));
	gotoxy(0,23);
}

string Interface::bidding()
{
	setcolor(colorcode(15,2));
	string bid;
	cin.clear();

	gotoxy(46,18);	cout<<"It's your turn,";
	gotoxy(46,19);	cout<<"Enter your bidding: ";

	cin >> bid;
	transform(bid.begin(),bid.end(),bid.begin(),::toupper);

	gotoxy(46, 18);	cout << "                                 ";
	gotoxy(46, 19);	cout << "                                 ";
	gotoxy(46, 20);	cout << "                                 ";

	gotoxy(0,23);
	return bid;
}

string Interface::playcard()
{
	setcolor(colorcode(15,2));
	string play;
	cin.clear();

	gotoxy(46,18);	cout<<"It's your turn,";
	gotoxy(46,19);	cout<<"Enter the card you play: ";

	cin>>play;
	transform(play.begin(),play.end(),play.begin(),::toupper);

	gotoxy(46, 18);	cout << "                                 ";
	gotoxy(46, 19);	cout << "                                 ";
	gotoxy(46, 20);	cout << "                                 ";
	
	gotoxy(0,23);
	return play;
}

void Interface::card (Player & player) //remake
{
	char suit_convert[4] = {};
	int printx[4] = {21, 13, 20, 28};
	int printy[4] = {14, 10, 6, 10};
	int suit_color;
	char suit;
	char num;

	int total_trick = player.ns_trick + player.ew_trick;
	int start_pos = (player.statement - player.position - player.turn) % 4;

	if (player.turn == 1) {
		setcolor(colorcode(15, 2));
		for (int i=0; i<4; i++) {
			gotoxy(printx[(start_pos+i)%4], printy[(start_pos+i)%4]);
			cout << "   ";
			gotoxy(printx[(start_pos+i)%4], printy[(start_pos+i)%4]+1);
			cout << "   ";
			gotoxy(printx[(start_pos+i)%4], printy[(start_pos+i)%4]+2);
			cout << "   ";
		}
	}

	for (int i=0; i<player.turn; i++) {

		suit = player.trick_log[total_trick][i][0];
		num = player.trick_log[total_trick][i][1];

		switch (suit) {
			case 'H': suit = '\3'; suit_color = 12; break;
			case 'D': suit = '\4'; suit_color = 12; break;
			case 'C': suit = '\5'; suit_color = 0; break;
			case 'S': suit = '\6'; suit_color = 0; break;
		}

		setcolor(colorcode(suit_color, 15));
		gotoxy(printx[(start_pos+i)%4], printy[(start_pos+i)%4]);
		cout << suit << "  ";
		gotoxy(printx[(start_pos+i)%4], printy[(start_pos+i)%4]+1);
		cout << " " << num << " ";
		gotoxy(printx[(start_pos+i)%4], printy[(start_pos+i)%4]+2);
		cout << "  " << suit;
	}

	//reset
	setcolor(colorcode(15,2));
	gotoxy(0,23);
}

void Interface::scoreboard (Player & player)
{
	setcolor(colorcode(0,15));
	gotoxy(72,3);	cout << "   Round   ";
	setcolor(colorcode(0,7));
	gotoxy(72,4);	cout << "           ";
	gotoxy(72,5);	cout << "           ";
	gotoxy(72,6);	cout << "           ";

	setcolor(colorcode(0,15));
	gotoxy(46,13);	cout << " Total Point ";
	setcolor(colorcode(0,7));
	gotoxy(46,14);	cout << "             ";
	gotoxy(46,15);	cout << "             ";
	
	gotoxy(77,5);	cout<<player.round;
	gotoxy(49,14);	cout << "NS :" << player.ns_point;
	gotoxy(49,15);	cout << "EW :" << player.ew_point;

	setcolor(colorcode(15,2));
	gotoxy(0,23);
}

void Interface::nowturn (Player & player) //remake
{
	int total_trick = player.ns_trick + player.ew_trick;
	int curr_turn = player.statement%10;

	if (curr_turn >=4) {}
	else if (player.trick_log[total_trick][3]!="") {}
	else {
		curr_turn = (curr_turn - player.position + 4) %4;
		setcolor(colorcode(14,2));

		switch (curr_turn) {
			case 0:
			case 2:
				gotoxy(5, 19-8*curr_turn);	cout << "■■■■■■■■";
				gotoxy(23, 19-8*curr_turn);	cout << "■■■■■■■■";
				break;
			case 1:
			case 3:
				for (int i=3; i<20; i++) {
					if (i==11) {continue;}
					gotoxy(-11+16*curr_turn, i);	cout << "■";
				}
				break;
		} //end of switch (curr_turn)
	}

	//reset
	setcolor(colorcode(15,2));
	gotoxy(0,23);
}

void Interface::guide() {
	setcolor(colorcode(0, 15));
	gotoxy(72, 13);	cout << "   Guide   ";
	setcolor(colorcode(0, 7));
	gotoxy(72, 14);	cout << "  C=\5 S=\6  ";
	gotoxy(72, 15);	cout << "  D=";

	setcolor(colorcode(12, 7));
	cout << '\4';
	setcolor(colorcode(0, 7));
	cout << " H=";
	setcolor(colorcode(12, 7));
	cout << "\3  ";

	//reset
	setcolor(colorcode(15,2));
	gotoxy(0,23);
}

void Interface::bid_guide() {

	setcolor(colorcode(0, 15));
	gotoxy(72, 8);	cout << "  Bidding  ";
	setcolor(colorcode(0, 7));
	gotoxy(72, 9);	cout << "  PS=PASS  ";
	gotoxy(72, 10);	cout << "  X = Dbl  ";
	gotoxy(72, 11);	cout << "  XX=Rdbl  ";

	//reset
	setcolor(colorcode(15,2));
	gotoxy(0,23);
}

void Interface::error() {
	gotoxy(46, 20);	cout << "Error. Your input is invalid.";
	
	//reset
	setcolor(colorcode(15,2));
	gotoxy(0,23);
}