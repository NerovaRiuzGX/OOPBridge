//Player.cpp
//by Ridost

#include"Player.h"

using namespace std;

Player::Player()
	:Host()
{
	decideBid = "00";
	decideCard = "00";
	decideClaim = -1;
}

void Player::bid()
{
	string bid;
	string Maxbid="00";
	/*auction_log;//���]�۵P��T
	auction_log.push_back("PS");
	auction_log.push_back("PS");
	auction_log.push_back("PS");
	auction_log.push_back("2S");*/
	for(int i=auction_log.size()-1;i>=0;i--)
	{

		if(auction_log[i]!="PS" && auction_log[i]!="X" && auction_log[i]!="XX")
		{
			Maxbid=auction_log[i]; break;
		}
	}

	while(true)
	{
		cout<<"Max bidding :"<<Maxbid<<endl;
		cout<<"Please Enter your bid( Pass(PS) , Dbl(X) , Rdbl(XX) )"<<endl
			<<"                       Spades(S) ,Hearts(H) ,Diamonds(D) ,Clubs(C),NoTrump(NT)"<<endl;
		getline(cin,bid);
		transform(bid.begin(),bid.end(),bid.begin(),::toupper);
		if( bid=="PS" || Maxbid=="00")	//�P�_�۵P�O�_�ŦX�W�h 
		{
				cout<<bid<<endl;
				break;
		}
		else if( bid=="X" && Maxbid!="00")	//�P�_�۵P�O�_�ŦX�W�h 
		{
				cout<<bid<<endl;
				break;
		}
		else if( bid=="XX" && ( auction_log[ auction_log.size()-2 ]=="X" || auction_log[ auction_log.size()-4 ]=="X"))	//�P�_�۵P�O�_�ŦX�W�h 
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
	system("cls");
	for(int i=0;i<auction_log.size();i++)
	{
		cout<<"acution_log: "<<auction_log[i]<<endl;
	}
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
	cout<<contract_suit<<"  "<<contract_trick<<"  "<<contract_dbl<<"  "<<declarer_position<<endl;
	
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
	/*ns_trick=1;
	ew_trick=11;
	trick_log[12][0]="00";*/
	if(trick_log[ns_trick+ew_trick][0]!="00")
	{
		cout<<"Front Play :"<<trick_log[ns_trick+ew_trick][0]<<endl;
		Suits=trick_log[ns_trick+ew_trick][0][0];
	}
	else cout<<"You are the first"<<endl;
	vector<string>::iterator it;	
	while (true)
	{
		cout<<"Please enter a card: ";
		getline(cin,playcard);
		transform(playcard.begin(),playcard.end(),playcard.begin(),::toupper);
		it=find(myCard.begin(),myCard.end(),playcard);			//�P�_ myCard �̭����S�� playCard
		if( it!=myCard.end() &&( trick_log[ns_trick+ew_trick][0]=="00" || playcard[0]==Suits || MySuits(Suits)==false) )	{ break; }	//�P�_�i���i�H�X�o�i�P�C 1.���o�i�P 2.���� or ��P���S���o�Ӫ�� or �Ĥ@�ӥX�P
		else if(playcard=="CLAIM")
		{
			cout<<"How many tricks : ";
			int i=1;
			for(i=1;i<=( 13-ns_trick-ew_trick ) ;i++)	cout<<i<<" ";
			cout<<endl;
			cin>>decideClaim;
			claim();
			break;
		}

		cout<<"Error!!!  You can't play this card."<<endl;
	}
}

void Player::claim()
{
	
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
