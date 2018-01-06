#ifndef INTERFACE_H
#define INTERFACE_H

#include<iostream>
#include<conio.h>
#include<Windows.h>
#include<string>
#include<vector>

using namespace std;

class Interface
{
public:
	Interface(char,char,char,char,int,int);
	void gamemodeoption();
	void multiplayeroption();
	void createtable();
	void jointable();
	void game();
	void bidding();
	void scoreboard();
	void gotoxy(int xpos, int ypos)
	{
	  COORD scrn;
	  HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	  scrn.X = xpos; scrn.Y = ypos;
	  SetConsoleCursorPosition(hOuput,scrn);
	}
private:
	int declarer_position;
	int position;
	char modechoose;
	char modeconfirm;
	char gamechoose;
	char gamestart;
};


#endif

