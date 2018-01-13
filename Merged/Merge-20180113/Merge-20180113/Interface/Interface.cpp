#include "Interface.h"
using namespace std;

string Interface::pos[4]={"Ｎ","Ｅ","Ｓ","Ｗ"};
int Interface::cardcounter=0;

Interface::Interface()
{
	modechoose = 72;
	modeconfirm = 0;
	gamechoose = 72;
	gamestart = 0;
}

int Interface::gamemodeoption()
{
	//PlaySound(TEXT("C:\\bridge4.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
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
		//gametable();
	}
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
}

void Interface::createtable(TCPServer & server)
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
}

string Interface::jointable()
{
	string connectIP;//testing
	system("cls");
	cin.clear();
	if(gamechoose==13&&gamestart==80)
	{
		cout<<"\n\n\n\n\n\n\n\n\n                                        ENTER THE TABLE'S IP\n"<<endl;
		gotoxy(43,13);
		cin>>connectIP;
		gotoxy(0,23);
	}
	else
	{
		cout<<"error";
	}

	return connectIP;
}

/*void Interface::gametable()
{
	system("cls");
	setcolor(colorcode(15,2));

	table();
	biddingtable();
	bidding();
	scoreboard();
	trick();
	contract();
	playcard();
	playercard();
	dummycard();
	
	gotoxy(0,23);
}*/

void Interface::dummycard(Player & player)
{
	vector<string> sCard;
	for(int i=0;i<player.Card[2].size();i++)
	{
		sCard.push_back(player.Card[2][i]);
	}
	vector<string> nCard;
	for(int i=0;i<player.Card[0].size();i++)
	{
		nCard.push_back(player.Card[0][i]);
	}
	vector<string> eCard;
	for(int i=0;i<player.Card[1].size();i++)
	{
		eCard.push_back(player.Card[1][i]);
	}
	vector<string> wCard;//testing
	for(int i=0;i<player.Card[3].size();i++)
	{
		wCard.push_back(player.Card[3][i]);
	}
	int s=sCard.size();
	int n=nCard.size();
	int e=eCard.size();
	int w=wCard.size();//testing
	
	gotoxy(6,1);
	if(player.declarer_position==player.position)
	{
		switch(player.position)
		{
		case 2:
			if(nCard[0][0]=='C')
			{
				setcolor(colorcode(0,2));
				cout<<"\5";
				setcolor(colorcode(15,2));
				cout<<" ";
			}
			for(int i=0;i<n;i++)
			{
				cout<<nCard[i][1];
				if(i==n-1)
				{
					break;
				}
				
				if(nCard[i][0]!=nCard[i+1][0])
				{
					
					switch(nCard[i+1][0])
					{
					case 'H':
						setcolor(colorcode(12,2));
						cout<<"  ";
						cout<<"\3";
						setcolor(colorcode(15,2));
						cout<<" ";
						break;
					case 'D':
						setcolor(colorcode(12,2));
						cout<<"  ";
						cout<<"\4";
						setcolor(colorcode(15,2));
						cout<<" ";
						break;
					case 'S':
						cout<<"  ";
						setcolor(colorcode(0,2));
						cout<<"\6";
						setcolor(colorcode(15,2));
						cout<<" ";
						break;
					}
				}
			}
			break;
		case 3:
			if(eCard[0][0]=='C')
			{
				setcolor(colorcode(0,2));
				cout<<"\5";
				setcolor(colorcode(15,2));
				cout<<" ";
			}
			for(int i=0;i<n;i++)
			{
				cout<<eCard[i][1];
				if(i==n-1)
				{
					break;
				}
				
				if(eCard[i][0]!=eCard[i+1][0])
				{
					
					switch(eCard[i+1][0])
					{
					case 'H':
						setcolor(colorcode(12,2));
						cout<<"  ";
						cout<<"\3";
						setcolor(colorcode(15,2));
						cout<<" ";
						break;
					case 'D':
						setcolor(colorcode(12,2));
						cout<<"  ";
						cout<<"\4";
						setcolor(colorcode(15,2));
						cout<<" ";
						break;
					case 'S':
						cout<<"  ";
						setcolor(colorcode(0,2));
						cout<<"\6";
						setcolor(colorcode(15,2));
						cout<<" ";
						break;
					}
				}
			}
			break;
		case 0:
			if(sCard[0][0]=='S')
			{
				setcolor(colorcode(0,2));
				cout<<"\6";
				setcolor(colorcode(15,2));
				cout<<" ";
			}
			for(int i=0;i<n;i++)
			{
				cout<<sCard[i][1];
				if(i==n-1)
				{
					break;
				}

				if(sCard[i][0]!=sCard[i+1][0])
				{
					
					switch(sCard[i+1][0])
					{
					case 'H':
						setcolor(colorcode(12,2));
						cout<<"  ";
						cout<<"\3";
						setcolor(colorcode(15,2));
						cout<<" ";
						break;
					case 'D':
						setcolor(colorcode(12,2));
						cout<<"  ";
						cout<<"\4";
						setcolor(colorcode(15,2));
						cout<<" ";
						break;
					case 'S':
						cout<<"  ";
						setcolor(colorcode(0,2));
						cout<<"\6";
						setcolor(colorcode(15,2));
						cout<<" ";
						break;
					}
				}
			}
			break;
		case 1:
			if(wCard[0][0]=='C')
			{
				setcolor(colorcode(0,2));
				cout<<"\5";
				setcolor(colorcode(15,2));
				cout<<" ";
			}
			for(int i=0;i<n;i++)
			{
				cout<<wCard[i][1];
				if(i==n-1)
				{
					break;
				}
				
				if(wCard[i][0]!=wCard[i+1][0])
				{
					
					switch(wCard[i+1][0])
					{
					case 'H':
						setcolor(colorcode(12,2));
						cout<<"  ";
						cout<<"\3";
						setcolor(colorcode(15,2));
						cout<<" ";
						break;
					case 'D':
						setcolor(colorcode(12,2));
						cout<<"  ";
						cout<<"\4";
						setcolor(colorcode(15,2));
						cout<<" ";
						break;
					case 'S':
						cout<<"  ";
						setcolor(colorcode(0,2));
						cout<<"\6";
						setcolor(colorcode(15,2));
						cout<<" ";
						break;
					}
				}
			}
			break;
		}
	}
	else
	{
		int y=4;
		if(player.declarer_position==player.position-1||player.declarer_position+1==player.position)
		{
			gotoxy(2,3);
			switch(player.position)
			{
			case 0:
				if(eCard[0][0]=='C')
				{
					setcolor(colorcode(0,2));
					cout<<"\5";
					gotoxy(2,y);y++;
					setcolor(colorcode(15,2));
				}
				for(int i=0;i<n;i++)
				{
					cout<<eCard[i][1];
					gotoxy(2,y);y++;
					if(i==n-1)
					{
						break;
					}
				
					if(eCard[i][0]!=eCard[i+1][0])
					{
					
						switch(eCard[i+1][0])
						{
						case 'H':
							setcolor(colorcode(12,2));
							cout<<"\3";
							gotoxy(2,y);y++;
							setcolor(colorcode(15,2));
							break;
						case 'D':
							setcolor(colorcode(12,2));
							cout<<"\4";
							gotoxy(2,y);y++;
							setcolor(colorcode(15,2));
							break;
						case 'S':
							setcolor(colorcode(0,2));
							cout<<"\6";
							gotoxy(2,y);y++;
							setcolor(colorcode(15,2));
							break;
						}
					}
				}
				break;
			case 1:
				if(sCard[0][0]=='S')
				{
					setcolor(colorcode(0,2));
					cout<<"\6";
					gotoxy(2,y);y++;
					setcolor(colorcode(15,2));
				}
				for(int i=0;i<n;i++)
				{
					cout<<sCard[i][1];
					gotoxy(2,y);y++;
					if(i==n-1)
					{
						break;
					}
				
					if(sCard[i][0]!=sCard[i+1][0])
					{
					
						switch(sCard[i+1][0])
						{
						case 'H':
							setcolor(colorcode(12,2));
							cout<<"\3";
							gotoxy(2,y);y++;
							setcolor(colorcode(15,2));
							break;
						case 'D':
							setcolor(colorcode(12,2));
							cout<<"\4";
							gotoxy(2,y);y++;
							setcolor(colorcode(15,2));
							break;
						case 'S':
							setcolor(colorcode(0,2));
							cout<<"\6";
							gotoxy(2,y);y++;
							setcolor(colorcode(15,2));
							break;
						}
					}
				}
				break;
			case 2:
				if(wCard[0][0]=='C')
				{
					setcolor(colorcode(0,2));
					cout<<"\5";
					gotoxy(2,y);y++;
					setcolor(colorcode(15,2));
				}
				for(int i=0;i<n;i++)
				{
					cout<<wCard[i][1];
					gotoxy(2,y);y++;
					if(i==n-1)
					{
						break;
					}
				
					if(wCard[i][0]!=wCard[i+1][0])
					{
					
						switch(wCard[i+1][0])
						{
						case 'H':
							setcolor(colorcode(12,2));
							cout<<"\3";
							gotoxy(2,y);y++;
							setcolor(colorcode(15,2));
							break;
						case 'D':
							setcolor(colorcode(12,2));
							cout<<"\4";
							gotoxy(2,y);y++;
							setcolor(colorcode(15,2));
							break;
						case 'S':
							setcolor(colorcode(0,2));
							cout<<"\6";
							gotoxy(2,y);y++;
							setcolor(colorcode(15,2));
							break;
						}
					}
				}
				break;
			case 3:
				if(nCard[0][0]=='C')
				{
					setcolor(colorcode(0,2));
					cout<<"\5";
					gotoxy(2,y);y++;
					setcolor(colorcode(15,2));
				}
				for(int i=0;i<n;i++)
				{
					cout<<nCard[i][1];
					gotoxy(2,y);y++;
					if(i==n-1)
					{
						break;
					}
				
					if(nCard[i][0]!=nCard[i+1][0])
					{
					
						switch(nCard[i+1][0])
						{
						case 'H':
							setcolor(colorcode(12,2));
							cout<<"\3";
							gotoxy(2,y);y++;
							setcolor(colorcode(15,2));
							break;
						case 'D':
							setcolor(colorcode(12,2));
							cout<<"\4";
							gotoxy(2,y);y++;
							setcolor(colorcode(15,2));
							break;
						case 'S':
							setcolor(colorcode(0,2));
							cout<<"\6";
							gotoxy(2,y);y++;
							setcolor(colorcode(15,2));
							break;
						}
					}
				}
				break;
			}
		}
		else
		{
			gotoxy(41,3);
			switch(player.position)
			{
			case 0:
				if(eCard[0][0]=='C')
				{
					setcolor(colorcode(0,2));
					cout<<"\5";
					gotoxy(41,y);y++;
					setcolor(colorcode(15,2));
				}
				for(int i=0;i<n;i++)
				{
					cout<<eCard[i][1];
					gotoxy(41,y);y++;
					if(i==n-1)
					{
						break;
					}
				
					if(eCard[i][0]!=eCard[i+1][0])
					{
					
						switch(eCard[i+1][0])
						{
						case 'H':
							setcolor(colorcode(12,2));
							cout<<"\3";
							gotoxy(41,y);y++;
							setcolor(colorcode(15,2));
							break;
						case 'D':
							setcolor(colorcode(12,2));
							cout<<"\4";
							gotoxy(41,y);y++;
							setcolor(colorcode(15,2));
							break;
						case 'S':
							setcolor(colorcode(0,2));
							cout<<"\6";
							gotoxy(41,y);y++;
							setcolor(colorcode(15,2));
							break;
						}
					}
				}
				break;
			case 1:
				if(sCard[0][0]=='S')
				{
					setcolor(colorcode(0,2));
					cout<<"\6";
					gotoxy(41,y);y++;
					setcolor(colorcode(15,2));
				}
				for(int i=0;i<n;i++)
				{
					cout<<sCard[i][1];
					gotoxy(41,y);y++;
					if(i==n-1)
					{
						break;
					}
				
					if(sCard[i][0]!=sCard[i+1][0])
					{
					
						switch(sCard[i+1][0])
						{
						case 'H':
							setcolor(colorcode(12,2));
							cout<<"\3";
							gotoxy(41,y);y++;
							setcolor(colorcode(15,2));
							break;
						case 'D':
							setcolor(colorcode(12,2));
							cout<<"\4";
							gotoxy(41,y);y++;
							setcolor(colorcode(15,2));
							break;
						case 'S':
							setcolor(colorcode(0,2));
							cout<<"\5";
							gotoxy(41,y);y++;
							setcolor(colorcode(15,2));
							break;
						}
					}
				}
				break;
			case 2:
				if(wCard[0][0]=='C')
				{
					setcolor(colorcode(0,2));
					cout<<"\5";
					gotoxy(41,y);y++;
					setcolor(colorcode(15,2));
				}
				for(int i=0;i<n;i++)
				{
					cout<<wCard[i][1];
					gotoxy(41,y);y++;
					if(i==n-1)
					{
						break;
					}
				
					if(wCard[i][0]!=wCard[i+1][0])
					{
					
						switch(wCard[i+1][0])
						{
						case 'H':
							setcolor(colorcode(12,2));
							cout<<"\3";
							gotoxy(41,y);y++;
							setcolor(colorcode(15,2));
							break;
						case 'D':
							setcolor(colorcode(12,2));
							cout<<"\4";
							gotoxy(41,y);y++;
							setcolor(colorcode(15,2));
							break;
						case 'S':
							setcolor(colorcode(0,2));
							cout<<"\6";
							gotoxy(41,y);y++;
							setcolor(colorcode(15,2));
							break;
						}
					}
				}
				break;
			case 3:
				if(nCard[0][0]=='C')
				{
					setcolor(colorcode(0,2));
					cout<<"\5";
					gotoxy(41,y);y++;
					setcolor(colorcode(15,2));
				}
				for(int i=0;i<n;i++)
				{
					cout<<nCard[i][1];
					gotoxy(41,y);y++;
					if(i==n-1)
					{
						break;
					}
				
					if(nCard[i][0]!=nCard[i+1][0])
					{
					
						switch(nCard[i+1][0])
						{
						case 'H':
							setcolor(colorcode(12,2));
							cout<<"\3";
							gotoxy(41,y);y++;
							setcolor(colorcode(15,2));
							break;
						case 'D':
							setcolor(colorcode(12,2));
							cout<<"\4";
							gotoxy(41,y);y++;
							setcolor(colorcode(15,2));
							break;
						case 'S':
							setcolor(colorcode(0,2));
							cout<<"\6";
							gotoxy(41,y);y++;
							setcolor(colorcode(15,2));
							break;
						}
					}
				}
				break;
			}
		}
	}
	gotoxy(0,23);
}

void Interface::playercard(Player & player)
{
	vector<string> sCard;
	for(int i=0;i<player.Card[2].size();i++)
	{
		sCard.push_back(player.Card[2][i]);
	}
	vector<string> nCard;
	for(int i=0;i<player.Card[0].size();i++)
	{
		nCard.push_back(player.Card[0][i]);
	}
	vector<string> eCard;
	for(int i=0;i<player.Card[1].size();i++)
	{
		eCard.push_back(player.Card[1][i]);
	}
	vector<string> wCard;//testing
	for(int i=0;i<player.Card[3].size();i++)
	{
		wCard.push_back(player.Card[3][i]);
	}
	int s=sCard.size();
	int n=nCard.size();
	int e=eCard.size();
	int w=wCard.size();//testing
	
	gotoxy(6,21);
	
	switch(player.position)
		{
		case 0:
			if(nCard[0][0]=='C')
			{
				setcolor(colorcode(0,2));
				cout<<"\5";
				setcolor(colorcode(15,2));
				cout<<" ";
			}
			for(int i=0;i<n;i++)
			{
				cout<<nCard[i][1];
				if(i==n-1)
				{
					break;
				}
				
				if(nCard[i][0]!=nCard[i+1][0])
				{
					
					switch(nCard[i+1][0])
					{
					case 'H':
						setcolor(colorcode(12,2));
						cout<<"  ";
						cout<<"\3";
						setcolor(colorcode(15,2));
						cout<<" ";
						break;
					case 'D':
						setcolor(colorcode(12,2));
						cout<<"  ";
						cout<<"\4";
						setcolor(colorcode(15,2));
						cout<<" ";
						break;
					case 'S':
						cout<<"  ";
						setcolor(colorcode(0,2));
						cout<<"\6";
						setcolor(colorcode(15,2));
						cout<<" ";
						break;
					}
				}
			}
			break;
		case 1:
			if(eCard[0][0]=='C')
			{
				setcolor(colorcode(0,2));
				cout<<"\5";
				setcolor(colorcode(15,2));
				cout<<" ";
			}
			for(int i=0;i<n;i++)
			{
				cout<<eCard[i][1];
				if(i==n-1)
				{
					break;
				}
				
				if(eCard[i][0]!=eCard[i+1][0])
				{
					
					switch(eCard[i+1][0])
					{
					case 'H':
						setcolor(colorcode(12,2));
						cout<<"  ";
						cout<<"\3";
						setcolor(colorcode(15,2));
						cout<<" ";
						break;
					case 'D':
						setcolor(colorcode(12,2));
						cout<<"  ";
						cout<<"\4";
						setcolor(colorcode(15,2));
						cout<<" ";
						break;
					case 'S':
						cout<<"  ";
						setcolor(colorcode(0,2));
						cout<<"\6";
						setcolor(colorcode(15,2));
						cout<<" ";
						break;
					}
				}
			}
			break;
		case 2:
			if(sCard[0][0]=='S')
			{
				setcolor(colorcode(0,2));
				cout<<"\6";
				setcolor(colorcode(15,2));
				cout<<" ";
			}
			for(int i=0;i<n;i++)
			{
				cout<<sCard[i][1];
				if(i==n-1)
				{
					break;
				}
				
				if(sCard[i][0]!=sCard[i+1][0])
				{
					
					switch(sCard[i+1][0])
					{
					case 'H':
						setcolor(colorcode(12,2));
						cout<<"  ";
						cout<<"\3";
						setcolor(colorcode(15,2));
						cout<<" ";
						break;
					case 'D':
						setcolor(colorcode(12,2));
						cout<<"  ";
						cout<<"\4";
						setcolor(colorcode(15,2));
						cout<<" ";
						break;
					case 'S':
						cout<<"  ";
						setcolor(colorcode(0,2));
						cout<<"\5";
						setcolor(colorcode(15,2));
						cout<<" ";
						break;
					}
				}
			}
			break;
		case 3:
			if(wCard[0][0]=='C')
			{
				setcolor(colorcode(0,2));
				cout<<"\5";
				setcolor(colorcode(15,2));
				cout<<" ";
			}
			for(int i=0;i<n;i++)
			{
				cout<<wCard[i][1];
				if(i==n-1)
				{
					break;
				}
				
				if(wCard[i][0]!=wCard[i+1][0])
				{
					
					switch(wCard[i+1][0])
					{
					case 'H':
						setcolor(colorcode(12,2));
						cout<<"  ";
						cout<<"\3";
						setcolor(colorcode(15,2));
						cout<<" ";
						break;
					case 'D':
						setcolor(colorcode(12,2));
						cout<<"  ";
						cout<<"\4";
						setcolor(colorcode(15,2));
						cout<<" ";
						break;
					case 'S':
						cout<<"  ";
						setcolor(colorcode(0,2));
						cout<<"\6";
						setcolor(colorcode(15,2));
						cout<<" ";
						break;
					}
				}
			}
			break;
		}
	gotoxy(0,23);
}

void Interface::trick(Player & player)
{
	gotoxy(61,13);
	setcolor(colorcode(0,15));
	cout<<"  trick  ";
	setcolor(colorcode(0,7));
	gotoxy(61,14);
	cout<<"         ";
	gotoxy(61,15);
	cout<<"         ";

	gotoxy(63,14);
	cout<<player.ns_trick;
	gotoxy(63,15);
	cout<<player.ew_trick;

	gotoxy(0,23);
}

void Interface::table(Player & player)
{
	gotoxy(0,3);
		cout<<"     ■■■■■■■■■■■■■■■■■\n"
			<<"     ■                              ■\n"
			<<"     ■                              ■\n"
			<<"     ■                              ■\n"
			<<"     ■                              ■\n"
			<<"     ■                              ■\n"
			<<"     ■                              ■\n"
			<<"     ■                              ■\n"
			<<"     ■                              ■\n"
			<<"     ■                              ■\n"
			<<"     ■                              ■\n"
			<<"     ■                              ■\n"
			<<"     ■                              ■\n"
			<<"     ■                              ■\n"
			<<"     ■                              ■\n"
			<<"     ■                              ■\n"
			<<"     ■■■■■■■■■■■■■■■■■"
			<<endl;
		
		gotoxy(21,19);
		cout<<pos[player.position];
		gotoxy(5,11);
		cout<<pos[(player.position+1)%4];
		gotoxy(21,3);
		cout<<pos[(player.position+2)%4];
		gotoxy(37,11);
		cout<<pos[(player.position+3)%4];

		gotoxy(0,23);
}

void Interface::contract(Player & player)
{
	gotoxy(72,8);
	setcolor(colorcode(0,15));
	cout<<" Contract. ";
	setcolor(colorcode(0,7));
	gotoxy(72,9);
	cout<<"           ";
	gotoxy(72,10);
	cout<<"           ";
	gotoxy(72,11);
	cout<<"           ";

	gotoxy(75,10);
	if(player.contract_dbl!=-1&&player.contract_suit!=-1&&player.contract_trick!=-1)
	{
		cout<<player.contract_trick-6<<player.contract_suit<<player.contract_dbl;
	}
	
	gotoxy(0,23);
}

void Interface::biddingtable(Player & player)
{
	gotoxy(46,3);
	setcolor(colorcode(0,15));
	cout<<"   N     E     S     W  ";
	setcolor(colorcode(0,7));
	int count=4;
	int count2=46;

	for(unsigned int i=0;i<player.auction_log.size();i++)
	{
		gotoxy(count2,count);
		cout<<"  "<<player.auction_log[i]<<"  ";
		count2+=6;
		if(count2>=66)
		{
			count2=46;
			count+=1;
		}
	}
	setcolor(colorcode(15,2));
}

string Interface::bidding()
{
	string bid;
	//cin.clear;

	gotoxy(46,18);
	cout<<"It's your turn,";
	gotoxy(46,19);
	cout<<"enter your bidding:";
	cin>>bid;

	gotoxy(46,18);
	cout<<"                      ";
	gotoxy(46,19);
	cout<<"                      ";

	gotoxy(0,23);

	return bid;
}

string Interface::playcard()
{
	string play;
	//cin.clear;

	setcolor(colorcode(15,2));
	gotoxy(45,18); 
	cout<<"It's your turn,";
	gotoxy(45,19); 
	cout<<"enter the card you play:";
	cin>>play;

	setcolor(colorcode(15,2));
	gotoxy(45,18); 
	cout<<"                          ";
	gotoxy(45,19); 
	cout<<"                          ";
	
	gotoxy(0,23);
	return play;
}

void Interface::card(Player & player)
{
	int i=player.ns_trick+player.ew_trick;

	switch(player.turn)
	{
	case 0:
		setcolor(colorcode(15,2));

		gotoxy(13,10);
		cout<<"   ";
		gotoxy(13,11);
		cout<<"   ";
		gotoxy(13,12);
		cout<<"   ";

		gotoxy(28,10);
		cout<<"   ";
		gotoxy(28,11);
		cout<<"   ";
		gotoxy(28,12);
		cout<<"   ";
		
		gotoxy(20,6);
		cout<<"   ";
		gotoxy(20,7);
		cout<<"   ";
		gotoxy(20,8);
		cout<<"   ";
		
		gotoxy(21,14);
		cout<<"   ";
		gotoxy(21,15);
		cout<<"   ";
		gotoxy(21,16);
		cout<<"   ";
		
		//lead
		suit(21,14,player.trick_log[i][0][0],player.trick_log[i][0][1]);
		break;
	case 1:
		//once right card
		suit(28,10,player.trick_log[i][0][0],player.trick_log[i][0][1]);
		if(player.trick_log[i][1]!="")
		{
			suit(21,14,player.trick_log[i][1][0],player.trick_log[i][1][1]);
		}
		break;
	case 2:
		//once top card + once right card
		suit(28,10,player.trick_log[i][0][0],player.trick_log[i][0][1]);
		if(player.trick_log[i][1]!="")
		{
			suit(20,6,player.trick_log[i][1][0],player.trick_log[i][1][1]);
		}
		if(player.trick_log[i][2]!="")
		{
			suit(21,14,player.trick_log[i][2][0],player.trick_log[i][2][1]);
		}
		break;
	case 3:
		//full
		suit(28,10,player.trick_log[i][0][0],player.trick_log[i][0][1]);
		if(player.trick_log[i][1]!="")
		{
			suit(20,6,player.trick_log[i][1][0],player.trick_log[i][1][1]);
		}
		if(player.trick_log[i][2]!="")
		{			
			suit(13,10,player.trick_log[i][2][0],player.trick_log[i][2][1]);
		}
		if(player.trick_log[i][3]!="")
		{
			suit(21,14,player.trick_log[i][3][0],player.trick_log[i][3][1]);
		}
		break;
	}
}

void Interface::suit(int x,int y,char &s,char &p)
{
	switch(s)
	{
	case 'S':
		gotoxy(x,y);
		setcolor(colorcode(0,15));
		cout<<"\6  ";
		gotoxy(x,y+1);
		cout<<" "<<p<<" ";
		gotoxy(x,y+2);
		cout<<"  \6";
		setcolor(colorcode(15,2));
		break;
	case 'H':
		gotoxy(x,y);
		setcolor(colorcode(12,15));
		cout<<"\3  ";
		gotoxy(x,y+1);
		cout<<" "<<p<<" ";
		gotoxy(x,y+2);
		cout<<"  \3";
		setcolor(colorcode(15,2));
		break;
	case 'D':
		gotoxy(x,y);
		setcolor(colorcode(12,15));
		cout<<"\4  ";
		gotoxy(x,y+1);
		cout<<" "<<p<<" ";
		gotoxy(x,y+2);
		cout<<"  \4";
		setcolor(colorcode(15,2));
		break;
	case 'C':
		gotoxy(x,y);
		setcolor(colorcode(0,15));
		cout<<"\5  ";
		gotoxy(x,y+1);
		cout<<" "<<p<<" ";
		gotoxy(x,y+2);
		cout<<"  \5";
		setcolor(colorcode(15,2));
		break;
	}
	gotoxy(0,23);
}

void Interface::scoreboard(Player & player)
{
	gotoxy(72,3);
	setcolor(colorcode(0,15));
	cout<<"   Round   ";
	setcolor(colorcode(0,7));
	gotoxy(72,4);
	cout<<"           ";
	gotoxy(72,5);
	cout<<"           ";
	gotoxy(72,6);
	cout<<"           ";

	gotoxy(46,13);
	setcolor(colorcode(0,15));
	cout<<" total point ";
	setcolor(colorcode(0,7));
	gotoxy(46,14);
	cout<<"             ";
	gotoxy(46,15);
	cout<<"             ";
	
	gotoxy(77,5);
	cout<<player.round;
	gotoxy(49,14);
	cout<<"NS :"<<player.ns_point;
	gotoxy(49,15);
	cout<<"EW :"<<player.ew_point;
	
	gotoxy(0,23);
}