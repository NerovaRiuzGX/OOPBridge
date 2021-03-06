#ifndef PLAYER
#define PLAYER
#include<vector>
#include"Host.h"
#include<string>
using namespace std;

class Player :public Host
{
public:
	friend class Interface;
	friend class FileControl;
		 Player();
	void printTable();
	void undo();
	void playCard();
	bool MySuits(char);
	void claim();
	void bid();
//protected:
	string decideCard;		//傳給server的資訊
	string decideBid;		//不用時為"00"
	int decideClaim;        //不用時為-1
	int position;
	string playcard;
	char Suits;
	bool vulnerable;
	vector <string> myCard;
	vector <string> dummyCard;
};
#endif