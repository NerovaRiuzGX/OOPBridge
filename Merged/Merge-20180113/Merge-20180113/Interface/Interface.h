#ifndef INTERFACE_H
#define INTERFACE_H

#include <conio.h>

#include "../Player/Player.h"
#include "../TCP/TCPServer.h"

class Interface
{
public:
	
	Interface();
	int gamemodeoption();//單雙人模式選擇
	int multiplayeroption();//加入or開桌選擇
	void createtable(TCPServer &);//顯示server的ip
	string jointable();//回傳玩家輸入的ip
	//void gametable();//我自己測試用的 不要理他
	void dummycard(Player &);//印出夢家的牌
	void playercard(Player &);//印出玩家的牌
	void trick(Player &);//印出目前兩隊吃到的墩數
	void table(Player &);//印出牌桌的框框
	void contract(Player &);//印出喊到的合約
	void biddingtable(Player &);//喊牌
	string bidding();//回傳玩家的喊牌內容
	string playcard();//回傳玩家打出的牌
	void card(Player &);//有人打牌的時候 牌桌上印出牌
	void suit(int,int,char ,char );//我自己function用的 不要理他
	void scoreboard(Player &);//印出兩隊目前分數
	void nowturn(Player &);//換到誰誰座位會亮亮
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
	//int turn;//testing
	//int declarer_position;//testing
	//int position;//testing
	char modechoose;
	char modeconfirm;
	char gamechoose;
	char gamestart;

	static string pos[4];
};


#endif

