#include"BridgePlayer.h"
#include<iostream>
#include<string>
#include<vector>
#include<time.h>
int main()
{
	srand(time(NULL));

	vector<string>mycard;
	BridgePlayer P1(mycard);
	cout<<"Auction_log = 2S"<<endl;
	P1.Bid();
	P1.Shuffle();
	P1.PlayCard();
	P1.PrintTable();
	system("pause");
}