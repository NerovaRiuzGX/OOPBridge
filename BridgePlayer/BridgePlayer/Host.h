#ifndef HOST_H
#define HOST_H
//#include"FileControl.h"
#include<vector>
#include<string>
using namespace std;

class Host
{
public:
	friend class FileControl;
	friend class BridgePlayer;
	Host();
	void vulner();
	void shuffle();
	static bool sortCard(const string &, const string &);
	void auction();
	void play();
	void score();
	static int CardToInt (string);
	static string IntToCard (int);
//protected:
	int round; //round of table
	bool ns_vulnerable;
	bool ew_vulnerable;
	vector<string> Card[4];
	int turn; //player's turn
	vector<string> auction_log;
	int contract_suit;
	int contract_trick;
	int contract_dbl;
	int declarer_position;
	vector<string> trick_log;
	int ns_trick;
	int ew_trick;
	int ns_point;
	int ew_point;
	string statement_name;
	string statement_data;
};
#endif