#include"BridgePlayer.h"
#include<vector>
#include<string>
#include<algorithm>
#include<iostream>
using namespace std;
BridgePlayer::BridgePlayer(vector<string> mycard)
{
	MyCard=mycard;
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