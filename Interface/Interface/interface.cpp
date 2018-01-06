#include "interface.h"
using namespace std;

Interface::Interface(char a=72,char b=0,char c=72,char d=0,int e=0,int f=0)
	:modechoose(a),modeconfirm(b),gamechoose(c),gamestart(d),declarer_position(e),position(f)
{
}

void Interface::gamemodeoption()
{
	cout<<"\n\n\n\n\n\n\n\n                             Welcome to bridge game!!\n\n\n"
		<<"                              >> single player\n                                  multi player\n\n\n\n\n\n\n\n\n"<<endl;
	while(1)
	{
		modeconfirm=modechoose;
		modechoose=getch();
		if(modechoose==72)
		{
			gotoxy(30,11);
			cout<<">>";
			gotoxy(31,12);
			cout<<"  ";
			gotoxy(0,22);
		}
		if(modechoose==80)
		{
			gotoxy(31,12);
			cout<<">>";
			gotoxy(30,11);
			cout<<"  ";
			gotoxy(0,22);
		}
		if(modechoose==13)
		{
			break;	
		}
	}
	if(modechoose==13&&modeconfirm==80)
	{
		multiplayeroption();
	}
	else
	{
		game();
	}
}

void Interface::multiplayeroption()
{
	system("cls");
	if(modechoose==13&&modeconfirm==80)
	{
		cout<<"\n\n\n\n\n\n\n\n                               Multi player mode\n\n\n"
				<<"                            >> create a new table\n                                 join a table\n\n\n\n\n\n\n\n\n"<<endl;
		while(1)
		{
			gamestart=gamechoose;
			gamechoose=getch();
			if(gamechoose==72)
			{
				gotoxy(28,11);
				cout<<">>";
				gotoxy(30,12);
				cout<<"  ";
				gotoxy(0,22);
			}
			if(gamechoose==80)
			{
				gotoxy(30,12);
				cout<<">>";
				gotoxy(28,11);
				cout<<"  ";
				gotoxy(0,22);
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
		createtable();
	}
	if(gamechoose==13&&gamestart==80)
	{
		jointable();
	}
}

void Interface::createtable()
{
	system("cls");
	if(gamechoose==13&&gamestart==72)
	{
		cout<<"\n\n\n\n\n\n\n\n                             Your IP is "<<serverIP
			<<"\n\n                              waiting for players"<<endl;
		gotoxy(0,22);
	}
	else
	{
		cout<<"error"<<endl;
	}
}

void Interface::jointable()
{
	system("cls");
	if(gamechoose==13&&gamestart==80)
	{
		cout<<"\n\n\n\n\n\n\n\n                              Enter the table's IP"<<endl;
		gotoxy(35,10);
		cin>>connectIP;
		gotoxy(0,22);
	}
	else
	{
		cout<<"error";
	}
}

void Interface::game()
{
	system("cls");
	if(declarer_position==position)
	{
		switch(position)
		{
		case 0:
			cout<<"  S ";
			for(int i=0;i++;i<sCard.size())
			{
				cout<<sCard[i][1];
				if(i==sCard.size()-1)
				{
					break;
				}
				if(sCard[i][0]!=sCard[i+1][0])
				{
					cout<<"  "<<sCard[i+1][0]<<" ";
				}
			}
			cout<<"\n\n   --------------S----------------\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  E                               W\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"   --------------N----------------"
				<<endl;
			cout<<"  S ";
			for(int i=0;i++;i<nCard.size())
			{
				cout<<nCard[i][1];
				if(i==nCard.size()-1)
				{
					break;
				}
				if(nCard[i][0]!=nCard[i+1][0])
				{
					cout<<"  "<<nCard[i+1][0]<<" ";
				}
			}
			break;
		case 1:
			cout<<"  S ";
			for(int i=0;i++;i<wCard.size())
			{
				cout<<wCard[i][1];
				if(i==wCard.size()-1)
				{
					break;
				}
				if(wCard[i][0]!=wCard[i+1][0])
				{
					cout<<"  "<<wCard[i+1][0]<<" ";
				}
			}
			cout<<"\n\n   --------------W----------------\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  S                               N\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"   --------------E----------------"
				<<endl;
			cout<<"  S ";
			for(int i=0;i++;i<eCard.size())
			{
				cout<<eCard[i][1];
				if(i==eCard.size()-1)
				{
					break;
				}
				if(eCard[i][0]!=eCard[i+1][0])
				{
					cout<<"  "<<eCard[i+1][0]<<" ";
				}
			}
			break;
		case 2:
			cout<<"  S ";
			for(int i=0;i++;i<nCard.size())
			{
				cout<<nCard[i][1];
				if(i==nCard.size()-1)
				{
					break;
				}
				if(nCard[i][0]!=nCard[i+1][0])
				{
					cout<<"  "<<nCard[i+1][0]<<" ";
				}
			}
			cout<<"\n\n   --------------N----------------\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  W                               E\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"   --------------S----------------"
				<<endl;
			cout<<"  S ";
			for(int i=0;i++;i<sCard.size())
			{
				cout<<sCard[i][1];
				if(i==sCard.size()-1)
				{
					break;
				}
				if(sCard[i][0]!=sCard[i+1][0])
				{
					cout<<"  "<<sCard[i+1][0]<<" ";
				}
			}
			break;
		case 3:
			cout<<"  S ";
			for(int i=0;i++;i<eCard.size())
			{
				cout<<eCard[i][1];
				if(i==eCard.size()-1)
				{
					break;
				}
				if(eCard[i][0]!=eCard[i+1][0])
				{
					cout<<"  "<<eCard[i+1][0]<<" ";
				}
			}
			cout<<"\n\n   --------------E----------------\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  N                               S\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"  |                               |\n"
				<<"   --------------W----------------"
				<<endl;
			cout<<"  S ";
			for(int i=0;i++;i<wCard.size())
			{
				cout<<wCard[i][1];
				if(i==wCard.size()-1)
				{
					break;
				}
				if(wCard[i][0]!=wCard[i+1][0])
				{
					cout<<"  "<<wCard[i+1][0]<<" ";
				}
			}
			break;
		}
	}
	bidding();
}

void Interface::bidding()
{
	gotoxy(40,1);
	cout<<"  N E S W";
	gotoxy(40,2);
	cout<<"1\n";
	gotoxy(40,3);
	cout<<"2\n";
	gotoxy(40,4);
	cout<<"3\n";
	gotoxy(40,5);
	cout<<"4\n";
	gotoxy(40,6);
	cout<<"5\n";
	gotoxy(40,7);
	cout<<"6\n";
	gotoxy(40,8);
	cout<<"7";
	int count=1;
	int count2=42;
	while()
	{
		gotoxy(count2,count);
		cout<<;
		count2+=3;
		if(count2==54)
		{
			count2=42;
			count+=1;
		}
	}
}

void Interface::scoreboard()
{
	gotoxy(40,10);
	cout<<"Round: ";
	gotoxy(40,11);
	cout<<"Vulnerable: ";
	gotoxy(40,12);
	cout<<"Contract:";
	gotoxy(40,13);
	cout<<"NS points:";
	gotoxy(40,14);
	cout<<"EW points:";
	gotoxy(40,15);
	cout<<"NS win trick:";
	gotoxy(40,16);
	cout<<"EW win trick:";
	
	gotoxy(47,10);
	cout<<;
	gotoxy(52,11);
}