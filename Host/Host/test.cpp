#include <iostream>
#include <vector> 
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

//Create a Poker Deck
bool sortCard(string a, string b)
{
	if(a[0] == b[0])
	{
		int _a = 0;
		int _b = 0;
		if(a[1] == 'T')
			_a = 1;
		if(a[1] == 'J')
			_a = 2;
		if(a[1] == 'Q')
			_a = 3;
		if(a[1] == 'K')
			_a = 4;
		if(a[1] == 'A')
			_a = 5;
		if(b[1] == 'T')
			_a = 1;
		if(b[1] == 'J')
			_b = 2;
		if(b[1] == 'Q')
			_b = 3;
		if(b[1] == 'K')
			_b = 4;
		if(b[1] == 'A')
			_b = 5;
	}
	return true;
}

int CardToInt (string card) {
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

string IntToCard (int input) {
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

int main () {
	srand(time(NULL));
	
	vector<string> Deck;
	for (int i=0; i<4; i++) {
		string color;
		switch (i) {
			case 0: color = 'S'; break;
			case 1: color = 'H'; break;
			case 2: color = 'D'; break;
			case 3: color = 'C'; break;
		}
		for (int j=1; j<=13; j++){
			switch(j) {
				case 1: Deck.push_back(color + 'A'); break;
				case 10: Deck.push_back(color + 'T'); break;
				case 11: Deck.push_back(color + 'J'); break;
				case 12: Deck.push_back(color + 'Q'); break;
				case 13: Deck.push_back(color + 'K'); break;
				default: Deck.push_back(color + to_string((long long)j)); break;
			}
		}
	}

	cout << "original deck:" << endl;
	for (int i=0; i<Deck.size(); i++) {
		cout << IntToCard(CardToInt(Deck[i])) << " ";
		if (i%13==12) {
			cout << endl;
		}
	}

	/*vector<string> Card[4];

	for (int i=0; i<52; i++) {
		int number = rand()%(Deck.size());
		Card[i%4].push_back(Deck[number]);
		Deck.erase(Deck.begin()+number); 
	}

	cout << endl << endl << "Card:" << endl;
	sort(Card[0].begin(),Card[0].end());
	sort(Card[1].begin(),Card[1].end());
	sort(Card[2].begin(),Card[2].end());
	sort(Card[3].begin(),Card[3].end());


	for (int i=0; i<4; i++) {
		cout << "Player Card: " << endl;
		for(int j=0; j<13; j++){
			cout << Card[i][j] << " ";
			if (j%13==12) {
				cout << endl;
			}
		}
	}

	sort(Card[0].begin(),Card[0].end(),sortCard);
	sort(Card[1].begin(),Card[1].end(),sortCard);
	sort(Card[2].begin(),Card[2].end(),sortCard);
	sort(Card[3].begin(),Card[3].end(),sortCard);

	cout << endl << endl << "Card:" << endl;
	for (int i=0; i<4; i++) {
		cout << "Player Card: " << endl;
		for(int j=0; j<13; j++){
			cout << Card[i][j] << " ";
			if (j%13==12) {
				cout << endl;
			}
		}
	}*/
	

	system("pause");
	return 0;
	
	
}
