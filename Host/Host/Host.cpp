#include "Host.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
#include <algorithm>
using namespace std;

Host::Host()
	:round(1),turn(0),ns_trick(0),ew_trick(0),ns_point(0),ew_point(0)
{
}
void Host::vulner()
{
	switch(round%16)
	{
	  case 0:
		  ns_vulnerable = false;
		  ew_vulnerable = true;
		  break;
	  case 1:
		  ns_vulnerable = false;
		  ew_vulnerable = false;
		  break;
	  case 2:
		  ns_vulnerable = true;
		  ew_vulnerable = false;
		  break;
	  case 3:
		  ns_vulnerable = false;
		  ew_vulnerable = true;
		  break;
	  case 4:
		  ns_vulnerable = true;
		  ew_vulnerable = true;
		  break;
	  case 5:
		  ns_vulnerable = true;
		  ew_vulnerable = false;
		  break;
	  case 6:
		  ns_vulnerable = false;
		  ew_vulnerable = true;
		  break;
	  case 7:
		  ns_vulnerable = true;
		  ew_vulnerable = true;
		  break;
	  case 8:
		  ns_vulnerable = false;
		  ew_vulnerable = false;
		  break;
	  case 9:
		  ns_vulnerable = false;
		  ew_vulnerable = true;
		  break;
	  case 10:
		  ns_vulnerable = true;
		  ew_vulnerable = true;
		  break;
	  case 11:
		  ns_vulnerable = false;
		  ew_vulnerable = false;
		  break;
	  case 12:
		  ns_vulnerable = true;
		  ew_vulnerable = false;
		  break;
	  case 13:
		  ns_vulnerable = true;
		  ew_vulnerable = true;
		  break;
	  case 14:
		  ns_vulnerable = false;
		  ew_vulnerable = false;
		  break;
	  case 15:
		  ns_vulnerable = true;
		  ew_vulnerable = false;
		  break;
	}
}
void Host::shuffle()
{
	vector<string> Deck;
	for (int i=0; i<4; i++) //製造牌堆
	{
		string color;
		switch (i) 
		{
			case 0: color = 'C'; break;
			case 1: color = 'D'; break;
			case 2: color = 'H'; break;
			case 3: color = 'S'; break;
		}
		for (int j=1; j<=13; j++)
		{
			switch(j) 
			{
				case 1: Deck.push_back(color + 'A'); break;
				case 10: Deck.push_back(color + 'T'); break;
				case 11: Deck.push_back(color + 'J'); break;
				case 12: Deck.push_back(color + 'Q'); break;
				case 13: Deck.push_back(color + 'K'); break;
				default: Deck.push_back(color + to_string((long long)j)); break;
			}
		}
	}
	for (int i=0; i<52; i++) //洗牌
	{
		int number = rand()%(Deck.size());
		Card[i%4].push_back(Deck[number]);
		Deck.erase(Deck.begin()+number);
	}
	//四個玩家的牌排序
	sort(Card[0].begin(),Card[0].end(),sortCard);
	sort(Card[1].begin(),Card[1].end(),sortCard);
	sort(Card[2].begin(),Card[2].end(),sortCard);
	sort(Card[3].begin(),Card[3].end(),sortCard);

	//印牌測試
	cout << endl << endl << "Card:" << endl;
	for (int i=0; i<4; i++) {
		cout << "Player Card: " << endl;
		for(int j=0; j<13; j++){
			cout << Card[i][j] << " ";
			if (j%13==12) {
				cout << endl;
			}
		}
	}
}
bool Host::sortCard(const string &a, const string &b)
{
	return CardToInt(a) < CardToInt(b);
}
void Host::auction()
{

}
int Host::CardToInt (string card) {
	int convert = 0;
	switch (card[0]) {
		case 'C': break;
		case 'D': convert += 13; break;
		case 'H': convert += 26; break;
		case 'S': convert += 39; break;
	}
	
	switch (card[1]) {
		case 'T': convert += 8; break;
		case 'J': convert += 9; break;
		case 'Q': convert += 10; break;
		case 'K': convert += 11; break;
		case 'A': convert += 12; break;
		default: convert += card[1]-50; break;
	}

	return convert;
}
string Host::IntToCard (int input) {
	char suit, num;
	switch (input/13) {
		case 0: suit = 'C'; break;
		case 1: suit = 'D'; break;
		case 2: suit = 'H'; break;
		case 3: suit = 'S'; break;
	}
	switch (input%13) {
		case 8: num = 'T'; break;
		case 9: num = 'J'; break;
		case 10: num = 'Q'; break;
		case 11: num = 'K'; break;
		case 12: num = 'A'; break;
		default: num = (input%13) + 50; break;
		
	}
	char convert[3] = {suit, num, '\0'};
	return string(convert);
}