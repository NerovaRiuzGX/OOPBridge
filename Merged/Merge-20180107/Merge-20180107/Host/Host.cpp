//Host.cpp
//by kkrun

#include "Host.h"

using namespace std;

Host::Host()
	:round(0),turn(0),ns_trick(0),ew_trick(0),ns_point(0),ew_point(0)
{
	auction_log.clear();
	ns_vulnerable=ew_vulnerable=-1;
	contract_suit=-1;
	contract_trick=-1;
	contract_dbl=-1;
	declarer_position=-1;
	srand(time(NULL));
}

void Host::reset()
{
	round++;
	turn = 0;
	ns_trick = ew_trick = 0;
	ns_vulnerable=ew_vulnerable=-1;
	contract_suit=-1;
	contract_trick=-1;
	contract_dbl=-1;
	declarer_position=-1;
	auction_log.clear();
	vulner();
	shuffle();
}

void Host::vulner()
{
	switch(round%16)
	{
	  case 0:
	  case 3:
	  case 6:
	  case 9:
		  ns_vulnerable = false;
		  ew_vulnerable = true;
		  break;
	  case 1:
	  case 8:
	  case 11:
	  case 14:
		  ns_vulnerable = false;
		  ew_vulnerable = false;
		  break;
	  case 2:
	  case 5:
	  case 12:
	  case 15:
		  ns_vulnerable = true;
		  ew_vulnerable = false;
		  break;
	  case 4:
	  case 7:
	  case 10:
	  case 13:
		  ns_vulnerable = true;
		  ew_vulnerable = true;
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
	Card[0].clear();
	Card[1].clear();
	Card[2].clear();
	Card[3].clear();
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
	/*cout << endl << endl << "Card:" << endl;
	for (int i=0; i<4; i++) {
		cout << "Player Card: " << endl;
		for(int j=0; j<13; j++){
			cout << Card[i][j] << " ";
			if (j%13==12) {
				cout << endl;
			}
		}
	}*/
}

bool Host::sortCard(const string &a, const string &b)
{
	return CardToInt(a) < CardToInt(b);
}

void Host::auction()
{
	
}

void Host::play()
{

}

void Host::score()
{
	int BasicScore,RewardScore,DblScore,ExceedScore,Mytrick,PunishScore;
	bool Vulner;
	if(declarer_position%2==0) 
		{
			Vulner=ns_vulnerable;
			Mytrick=ns_trick;
		}	
	else 
	{
		Vulner=ew_vulnerable;
		Mytrick=ew_trick;
	}
	if(Mytrick>= contract_trick)
	{
		if(contract_suit==0 ||contract_suit==1)				//Clubs=0 , Diamonds=1 , Hearts=2 , Spades=3 , NT=4;
		{
			BasicScore=    contract_dbl*( (contract_trick-6)*20 );		//BasicScore 計算牌礅分數
		}
		else if(contract_suit==2 || contract_suit==3)
		{
			BasicScore=    contract_dbl*( (contract_trick-6)*30 );
		}
		else if(contract_suit==4)
		{
			BasicScore=    contract_dbl*( ( 40+(contract_trick-7)*30) );
		}
		cout<<"BasicScore : "<<BasicScore<<endl;
		if(Vulner==false)
		{	
			if(BasicScore>100) RewardScore=300;		//RewardScore 計算線位獎分
			else RewardScore=50;
			if(Mytrick==13 && contract_trick==13)	RewardScore=RewardScore+1000;
			else if(Mytrick==12 && contract_trick==12) RewardScore=RewardScore+500;	
		}
		else
		{
			if(BasicScore>100) RewardScore=500;
			else RewardScore=50;
			if(Mytrick==13 && contract_trick==13)	RewardScore=RewardScore+1500;
			else if(Mytrick==12 && contract_trick==12) RewardScore=RewardScore+750;
		}
		cout<<"RewardScore : "<<RewardScore<<endl;
		if( Mytrick>=contract_trick && contract_dbl==2 )		DblScore=50;		// DblScore計算 Dbl獎分
		else if( Mytrick>=contract_trick && contract_dbl==4 )	DblScore=100;
		else DblScore=0;
		cout<<"DblScore : "<<DblScore<<endl;

		if(Mytrick-contract_trick>0)
		{
			if(contract_dbl==1)
			{
					if(contract_suit==2 || contract_suit==3 || contract_suit==4)
					{
						ExceedScore = 30*(Mytrick-contract_trick);
					}
					else 
					{
						ExceedScore = 20*(Mytrick-contract_trick);
					}
			}
			else if(Vulner==false)							// ExceedScore 計算 超礅分數
			{
				ExceedScore = (Mytrick-contract_trick)*50*contract_dbl;
			}
			else
			{
				ExceedScore = (Mytrick-contract_trick)*100* contract_dbl;
			}
		}
		else ExceedScore=0;
		cout<<"ExceedScore : "<<ExceedScore<<endl;
		if(declarer_position%2==0)	//最後分數計算
		{
			ns_point += BasicScore + RewardScore + DblScore + ExceedScore; 
			ew_point = ns_point*-1;
		}
		else
		{
			ew_point += BasicScore + RewardScore + DblScore + ExceedScore; 
			ns_point = ew_point*-1;
		}
	}
	else
	{
		if(contract_dbl==1)				//PunishScore 計算 罰分
		{
			if(Vulner==true)	PunishScore=(contract_trick-Mytrick)*100;
			else PunishScore=(contract_trick-Mytrick)*50;
		}
		else if (contract_dbl==2)	
		{
			if(Vulner==true)
			{
				if(contract_trick-Mytrick>=1)
				{
					PunishScore=200;
				}
				if(contract_trick-Mytrick>=2)
				{
					PunishScore+=(contract_trick-Mytrick-1)*300;
				}
			}
			else
			{
				if(contract_trick-Mytrick>=1) PunishScore=100;
				if (contract_trick-Mytrick>=2 ) PunishScore+=200;
				if (contract_trick-Mytrick>=3) PunishScore+=200;
				if (contract_trick-Mytrick>=4) PunishScore+=(contract_trick-Mytrick-3)*300;
			}
		}
		else if(contract_dbl==4)
		{
			if(Vulner==true)
			{
				if(contract_trick-Mytrick>=1) PunishScore=400;
				if(contract_trick-Mytrick>=2) PunishScore+=(contract_trick-Mytrick-1)*600;
			}
			else
			{
				if(contract_trick-Mytrick>=1) PunishScore=200;
				if(contract_trick-Mytrick>=2) PunishScore+=400;
				if(contract_trick-Mytrick>=3) PunishScore+=400;
				if(contract_trick-Mytrick>=4) PunishScore+=(contract_trick-Mytrick-3)*600;
			}
		
		}
		if(declarer_position%2==0) 
			{
				ns_point += PunishScore*-1;			//最後分數計算
				ew_point = ns_point*-1;			
			}
		else 
		{
			ew_point+=PunishScore*-1;
			ns_point=ew_point*-1;
		}
	}

	cout<<"NS_Point : "<<ns_point<<endl
		<<"EW_Point : "<<ew_point<<endl;
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