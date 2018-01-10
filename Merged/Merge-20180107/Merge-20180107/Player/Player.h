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

	string decideCard;		//�ǵ�server����T
	string decideBid;		//���ήɬ�"00"
	int decideClaim;        //���ήɬ�-1
	int position;

protected:
	string playcard;
	char Suits;
	bool vulnerable;
	vector <string> myCard;
	vector <string> dummyCard;
};

#endif