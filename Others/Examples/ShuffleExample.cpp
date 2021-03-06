#include <iostream>
#include <vector> 
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

//Create a Poker Deck
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
		cout << Deck[i] << " ";
		if (i%13==12) {
			cout << endl;
		}
	}

	vector<string> Card[4];

	for (int i=0; i<52; i++) {
		int number = rand()%(Deck.size());
		Card[i%4].push_back(Deck[number]);
		Deck.erase(Deck.begin()+number); 
	}

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
	
	system("pause");
	return 0;
	
	
}
