#include"Player.h"
#include"Host.h"
#include<vector>
#include<time.h>
#include<string>
#include<algorithm>
#include<iostream>
#include<locale>
using namespace std;
Player::Player()
	:Host()
{
}
void Player::bid()
{
	string bid;
	string Maxbid="00";
	auction_log;//假設喊牌資訊
	auction_log.push_back("PS");
	auction_log.push_back("PS");
	auction_log.push_back("PS");
	auction_log.push_back("2S");
	for(int i=auction_log.size()-1;i>0;i--)
	{

		if(auction_log[i]!="PS" && auction_log[i]!="X" && auction_log[i]!="XX")
		{
			Maxbid=auction_log[i];
		}
	}

	while(true)
	{
		cout<<"Max bidding :"<<Maxbid<<endl;
		cout<<"Please Enter your bid( Pass(PS) , Dbl(X) , Rdbl(XX) )"<<endl
			<<"                       Spades(S) ,Hearts(H) ,Diamonds(D) ,Clubs(C),NoTrump(NT)"<<endl;
		getline(cin,bid);
		transform(bid.begin(),bid.end(),bid.begin(),::toupper);
		if( bid=="PS" || bid=="X" || bid=="XX" || Maxbid=="00")	//判斷喊牌是否符合規則 
		{
				cout<<bid<<endl;
				break;
		}
		else if(bid[0]<'8' && bid[0]>Maxbid[0])
		{
			cout<<bid<<endl;
			break;
		}
		else if(bid[0]<'8' && bid[0]==Maxbid[0] && Maxbid[1]=='C' &&( bid[1]=='S' || bid[1]=='H' || bid[1]=='D' ||(bid[1]=='N' && bid[2]=='T')) )
		{
			cout<<bid<<endl;
			break;
		}
		else if(bid[0]<'8' && bid[0]==Maxbid[0] && Maxbid[1]=='D' &&(bid[1]=='H' || bid[1]=='S' ||(bid[1]=='N' && bid[2]=='T')) )
		{
			cout<<bid<<endl;
			break;
		}
		else if(bid[0]<'8' && bid[0]==Maxbid[0] && Maxbid[1]=='H' && ( bid[1]=='S' ||(bid[1]=='N' && bid[2]=='T') ))
		{
			cout<<bid<<endl;
			break;
		}
		else if(bid[0]<'8' && bid[0]==Maxbid[0] && Maxbid[1]=='S' && bid[1]=='N' && bid[2]=='T')
		{
			cout<<bid<<endl;
			break;
		}
		else
		{
			cout<<bid<<endl<<"You have an error bid  !!!"<<endl;
		}
	}
	decideBid=bid;
}

void Player::printTable()
{
	cout<<" ------------N------------- "<<endl;
	cout<<"|                          |"<<endl;
	cout<<"|                          |"<<endl;
	cout<<"|                          |"<<endl;
	cout<<"|                          |"<<endl;
	cout<<"|                          |"<<endl;
	cout<<"W             "<<playcard<<"           E"<<endl;
	cout<<"|                          |"<<endl;
	cout<<"|                          |"<<endl;
	cout<<"|                          |"<<endl;
	cout<<"|                          |"<<endl;
	cout<<"|                          |"<<endl;
	cout<<"|                          |"<<endl;
	cout<<" ------------S------------- "<<endl;
}
void Player::playCard()
{
	for(int i=0;i<13;i++)
	{
		for(int j=0;j<4;j++)
		{
			trick_log[i][j]="00";
		}
	}
	ns_trick=1;
	ew_trick=3;
	trick_log[5][0]="C8";
	int check=0;
	for(int i=3;i>=0;i--)
	{
		if(trick_log[ns_trick+ew_trick+1][i]!="00")
		{
			cout<<"Front Play :"<<trick_log[ns_trick+ew_trick+1][i]<<endl;
			check=1;
			Suits=trick_log[ns_trick+ew_trick+1][i][0];
			break;
		}
	}
	if(check=0) cout<<"You is the first"<<endl;
	vector<string>::iterator it;	
	while (true)
	{
		cout<<"Please enter a card: ";
		getline(cin,playcard);
		transform(playcard.begin(),playcard.end(),playcard.begin(),::toupper);
		it=find(myCard.begin(),myCard.end(),playcard);			//判斷 myCard 裡面有沒有 playCard
		if( it!=myCard.end() &&( trick_log[ns_trick+ew_trick+1][0]=="00" || playcard[0]==Suits || MySuits(Suits)==false) )	{ break; }	//判斷可不可以出這張牌。 1.有這張牌 2.花色對 or 手牌中沒有這個花色 or 第一個出牌
		cout<<"Error!!!  You can't play this card."<<endl;
	}
}
bool Player::MySuits(char suits)	//判斷自己有沒有這個花色 有則回傳 true ，否則回傳 false
{
	int check=0;
	for(int i=0;i<myCard.size();i++)
	{
		if( myCard[i][0]==suits)
		{
			check=1;				//找到相同花色 check改變為1
			return true;
			break;
		}
	}
	if(check==0)				//找不到相同花色
		{
			return false;
		}
}
