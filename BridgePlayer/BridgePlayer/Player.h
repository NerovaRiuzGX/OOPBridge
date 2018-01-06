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
	void bid();
//protected:
	string decideCard;		//�ǵ�server
	string decideBid;				//����T	
	int position;
	string playcard;
	char Suits;
	bool vulnerable;
	vector <string> myCard;
	vector <string> dummyCard;
};
#endif