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
void Host::vunler()
{
	switch(round%4)
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
	for (int i=0; i<4; i++) //»s³yµP°ï
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
	for (int i=0; i<52; i++) //¬~µP
	{
		int number = rand()%(Deck.size());
		Card[i%4].push_back(Deck[number]);
		Deck.erase(Deck.begin()+number);
	}

}