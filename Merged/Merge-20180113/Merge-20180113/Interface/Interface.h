#ifndef INTERFACE_H
#define INTERFACE_H

#include <conio.h>

#include "../Player/Player.h"
#include "../TCP/TCPServer.h"

class Interface
{
public:
	
	Interface();
	int gamemodeoption();//�����H�Ҧ����
	int multiplayeroption();//�[�Jor�}����
	void createtable(TCPServer &);//���server��ip
	string jointable();//�^�Ǫ��a��J��ip
	//void gametable();//�ڦۤv���եΪ� ���n�z�L
	void dummycard(Player &);//�L�X�ڮa���P
	void playercard(Player &);//�L�X���a���P
	void trick(Player &);//�L�X�ثe�ⶤ�Y�쪺�[��
	void table(Player &);//�L�X�P�઺�خ�
	void contract(Player &);//�L�X�ۨ쪺�X��
	void biddingtable(Player &);//�۵P
	string bidding();//�^�Ǫ��a���۵P���e
	string playcard();//�^�Ǫ��a���X���P
	void card(Player &);//���H���P���ɭ� �P��W�L�X�P
	void suit(int,int,char ,char );//�ڦۤvfunction�Ϊ� ���n�z�L
	void scoreboard(Player &);//�L�X�ⶤ�ثe����
	void nowturn(Player &);//����ֽ֮y��|�G�G
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

