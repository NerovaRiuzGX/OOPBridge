#ifndef BRIDGEPLAYER
#define BRIDGEPLAYER
#include<vector>
#include<string>
using namespace std;

class BridgePlayer
{
public:
	  BridgePlayer(vector<string>);
	void PrintTable();
	void Undo();
	void PlayCard();
	bool  MySuits(char);	
protected:
	string playCard;
	char MasterSuits;
	char Suits;
	vector <string> MyCard;
};
#endif