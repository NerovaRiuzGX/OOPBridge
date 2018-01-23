#include"BridgePlayer.h"
#include<iostream>
#include<string>
#include<vector>
int main()
{

	vector<string>mycard;
	mycard.push_back("S1");
	mycard.push_back("D3");
	mycard.push_back("A4");
	BridgePlayer P1(mycard);
	P1.PlayCard();
	P1.PrintTable();
	system("pause");
}