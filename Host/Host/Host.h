#ifndef HOST_H
#define HOST_H
#include<vector>
#include<string>
using namespace std;

class Host
{
public:
	Host();
	void vunler();
	void shuffle();
	void auction();
	void play();
	void score();
	void pkgrcv();
	void pkgsnd();
protected:
	int round; //round of table
	bool ns_vulnerable;
	bool ew_vulnerable;
	vector<string> Card[4];
	int turn; //player's turn
	vector<string> auction_log;
	int contract_suit;
	int contract_trick;
	int declarer_position;
	vector<string> trick_log;
	int ns_trick;
	int ew_trick;
	int ns_point;
	int ew_point;
};
#endif