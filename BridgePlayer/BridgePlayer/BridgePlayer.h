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
	void Shuffle();
	void Bid();
protected:
	int Position;
	int Win_Trick;
	vector<string> TotalCard;
	string playCard;
	char MasterSuits;
	char Suits;
	bool Vulnerable;
	vector <string> MyCard;
	vector <string> DummyCard;
};
#endif