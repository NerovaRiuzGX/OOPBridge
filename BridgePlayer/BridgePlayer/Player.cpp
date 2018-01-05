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
	auction_log;//���]�۵P��T
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
		if( bid=="PS" || bid=="X" || bid=="XX" || Maxbid=="00")	//�P�_�۵P�O�_�ŦX�W�h 
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

	Suits='S';
	cout<<trick_log.empty()<<endl;
	trick_log.push_back("SA");
	cout<<"Front Play :"<<trick_log[trick_log.size()-1]<<endl;
	vector<string>::iterator it;	
	while (true)
	{
		cout<<"Please enter a card: ";
		getline(cin,playcard);
		transform(playcard.begin(),playcard.end(),playcard.begin(),::toupper);
		it=find(myCard.begin(),myCard.end(),playcard);			//�P�_ myCard �̭����S�� playCard
		if( it!=myCard.end() &&( trick_log.empty() || playcard[0]==Suits || MySuits(Suits)==false) )	{ break; }	//�P�_�i���i�H�X�o�i�P�C 1.���o�i�P 2.���� or ��P���S���o�Ӫ�� or �Ĥ@�ӥX�P
		cout<<"Error!!!  You can't play this card."<<endl;
	}
}
bool Player::MySuits(char suits)	//�P�_�ۤv���S���o�Ӫ�� ���h�^�� true �A�_�h�^�� false
{
	int check=0;
	for(int i=0;i<myCard.size();i++)
	{
		if( myCard[i][0]==suits)
		{
			check=1;				//���ۦP��� check���ܬ�1
			return true;
			break;
		}
	}
	if(check==0)				//�䤣��ۦP���
		{
			return false;
		}
}
