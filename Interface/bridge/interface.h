#ifndef INTERFACE_H
#define INTERFACE_H

#include<iostream>
#include<conio.h>
#include<Windows.h>
#include<string>
#include<vector>
#include<stdio.h>
#include<MMSystem.h>
#pragma  comment(lib,"WinMM.Lib")

using namespace std;

class Interface
{
public:
	Interface(char,char,char,char,int,int,int);
	void gamemodeoption();
	void multiplayeroption();
	void createtable();
	void jointable();
	void gametable();
	void dummycard();
	void playercard();
	void trick();
	void table();
	void contract();
	void bidding();
	void playcard();
	void card();
	void suit(int,int,char &,char &);
	void scoreboard();
	void gotoxy(int xpos, int ypos)
	{
		COORD scrn;
		HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
		scrn.X = xpos; scrn.Y = ypos;
		SetConsoleCursorPosition(hOuput,scrn);
	}
	void setcolor(unsigned short ForeColor=15,unsigned short BackGroundColor=0)
	{
		HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hCon,ForeColor|BackGroundColor);
	};
	int colorcode(int f,int b)
	{
		return f + 16*b;
	}
private:
	int turn;//testing
	int declarer_position;//testing
	int position;//testing
	char modechoose;
	char modeconfirm;
	char gamechoose;
	char gamestart;

	static string pos[4];
	static int cardcounter;
};


#endif

