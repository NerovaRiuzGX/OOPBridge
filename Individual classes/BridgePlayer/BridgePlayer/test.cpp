#include"Player.h"
#include "Host.h"
#include<iostream>
#include<string>
#include<vector>
#include<time.h>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;
int main()
{
	srand(time(NULL));
	vector<string>myCard;
	Player P1;
	P1.shuffle();
	P1.myCard.resize(13);
	for(int i=0;i<P1.Card[1].size();i++)
	{
		P1.myCard[i] = P1.Card[1][i];
	}
	P1.bid();
	P1.playCard();
	P1.printTable();
	system("pause");
}