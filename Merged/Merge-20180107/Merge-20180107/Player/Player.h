#ifndef PLAYER
#define PLAYER

#include"..\Host\Host.h"

#include <locale>

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

	string decideCard;		//傳給server的資訊
	string decideBid;		//不用時為"00"
	int decideClaim;        //不用時為-1
	int position;

protected:
	string playcard;
	char Suits;
	bool vulnerable;
	vector <string> myCard;
	vector <string> dummyCard;
};

#endif