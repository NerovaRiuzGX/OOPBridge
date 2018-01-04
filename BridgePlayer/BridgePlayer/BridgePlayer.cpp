#include"BridgePlayer.h"
#include<vector>
#include<time.h>
#include<string>
#include<algorithm>
#include<iostream>
using namespace std;
BridgePlayer::BridgePlayer(vector<string> mycard)
{
	MyCard=mycard;
}
void BridgePlayer::Bid()
{
	string bid;
	string auction_log="2S";		//���]�۵P��T
	while(true)
	{
		cout<<"Please Enter your Bid( Pass(ps) , Dbl(dbl) , Rdbl(rdbl) )"<<endl
			<<"                       Spades(S) ,Hearts(H) ,Diamonds(D) ,Clubs(C)"<<endl;
		getline(cin,bid);
		if( bid=="ps" || bid=="dbl" || bid=="rdbl")	//�P�_�۵P�O�_�ŦX�W�h 
		{
				cout<<bid<<endl;
				break;
		}
		else if(bid[0]<'8' && bid[0]>auction_log[0])
		{
			cout<<bid<<endl;
			break;
		}
		else if(bid[0]<'8' && bid[0]==auction_log[0] && auction_log[1]=='C' &&( bid[1]=='S' || bid[1]=='H' || bid[1]=='D' ||(bid[1]=='N' && bid[2]=='T')) )
		{
			cout<<bid<<endl;
			break;
		}
		else if(bid[0]<'8' && bid[0]==auction_log[0] && auction_log[1]=='D' &&(bid[1]=='H' || bid[1]=='S' ||(bid[1]=='N' && bid[2]=='T')) )
		{
			cout<<bid<<endl;
			break;
		}
		else if(bid[0]<'8' && bid[0]==auction_log[0] && auction_log[1]=='H' && ( bid[1]=='S' ||(bid[1]=='N' && bid[2]=='T') ))
		{
			cout<<bid<<endl;
			break;
		}
		else if(bid[0]<'8' && bid[0]==auction_log[0] && auction_log[1]=='S' && bid[1]=='N' && bid[2]=='T')
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
void BridgePlayer::Shuffle()
{
	char totalCard[52][3]={"SA","S2","S3","S4","S5","S6","S7","S8","S9","ST","SJ","SQ","SK",
				"HA","H2","H3","H4","H5","H6","H7","H8","H9","HT","HJ","HQ","HK",																	
				 "DA","D2","D3","D4","D5","D6","D7","D8","D9","DT","DJ","DQ","DK",																	
				  "CA","C2","C3","C4","C5","C6","C7","C8","C9","CT","CJ","CQ","CK"
					};
	vector<string>TotalCard(totalCard+0,totalCard+52);
	MyCard.resize(13);
	vector<string>::iterator it;	
		for(int i=0;i<13;i++)
		{
			int R=rand()%TotalCard.size();

			it=find(MyCard.begin(),MyCard.end(),TotalCard[R]);	
			if( it==MyCard.end() )
			{
				MyCard[i]=TotalCard[R];				
			}
			else i--;
		}
		sort(MyCard.begin(),MyCard.end());
		for(int i=0;i<MyCard.size();i++)
		{
			cout<<MyCard[i]<<endl;
		}
}
void BridgePlayer::PrintTable()
{
	cout<<" ------------N------------- "<<endl;
	cout<<"|                          |"<<endl;
	cout<<"|                          |"<<endl;
	cout<<"|                          |"<<endl;
	cout<<"|                          |"<<endl;
	cout<<"|                          |"<<endl;
	cout<<"W             "<<playCard<<"           E"<<endl;
	cout<<"|                          |"<<endl;
	cout<<"|                          |"<<endl;
	cout<<"|                          |"<<endl;
	cout<<"|                          |"<<endl;
	cout<<"|                          |"<<endl;
	cout<<"|                          |"<<endl;
	cout<<" ------------S------------- "<<endl;
}
void BridgePlayer::PlayCard()
{
	Suits='C';
	vector<string>::iterator it;	
	while (true)
	{
		cout<<"Please enter a card: ";
		getline(cin,playCard);
		it=find(MyCard.begin(),MyCard.end(),playCard);			//�P�_ MyCard �̭����S�� playCard
		if( it!=MyCard.end() &&( playCard[0]==Suits || MySuits(Suits)==false) )	{ break; }	//�P�_�i���i�H�X�o�i�P�C 1.���o�i�P 2.���� or ��P���S���o�Ӫ��
		cout<<"Error!!!  You can't play this card."<<endl;
	}
}
bool BridgePlayer::MySuits(char suits)	//�P�_�ۤv���S���o�Ӫ�� ���h�^�� true �A�_�h�^�� false
{
	int check=0;
	for(int i=0;i<MyCard.size();i++)
	{
		if( MyCard[i][0]==suits)
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