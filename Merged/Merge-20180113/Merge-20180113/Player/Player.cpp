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

bool Player::bid (string bid)
{
	//string bid;
	string Maxbid="00", Maxcall="00";
	int Maxcall_pos=0;
	/*auction_log;//假設喊牌資訊
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

	for(int i=auction_log.size()-1;i>=0;i--)
	{
		if(auction_log[i]!="PS")
		{
			Maxcall_pos=auction_log.size()-i;
			Maxcall=auction_log[i]; break;
		}
	}

	//while(true)
	//{	
		//fflush(stdin);
		//cout<<"Max bidding :"<<Maxbid<<endl;
		//cout<<"Please Enter your bid( Pass(PS) , Dbl(X) , Rdbl(XX) )"<<endl
		//	<<"                       Spades(S) ,Hearts(H) ,Diamonds(D) ,Clubs(C),NoTrump(NT)"<<endl;
		//getline(cin,bid);
		transform(bid.begin(),bid.end(),bid.begin(),::toupper);
		
		
		if (bid=="PS") {
			return true;
		}
		else if (bid=="X" || bid=="XX") {
			if (Maxcall_pos%2==1) {
				if (Maxbid=="00") {
					return false;
				}
				else if (Maxcall!="X" && bid=="XX") {
					return false;
				}
				else if (Maxcall=="X" && bid=="X") {
					return false;
				}
				else if (Maxcall=="XX") {
					return false;
				}
				else {
					return true;
				}
			}
			else {
				return false;
			}
		}
		else if( bid[0]<'8' && (bid[1]=='C' || bid[1]=='D' || bid[1]=='H' || bid[1]=='S' || (bid[1]=='N' && bid[2]=='T'))) {
			if (Maxbid[0]>bid[0]) {
				return false;
			}
			else if (Maxbid[0]==bid[0]) {
				bool pass = true;
				switch (bid[1]) {
					case 'C':
						pass = false; break;
					case 'D':
						if (!(Maxbid[1]=='C')) {pass = false;} break;
					case 'H':
						if (!(Maxbid[1]=='C' || Maxbid[1]=='D')) {pass = false;} break;
					case 'S':
						if (Maxbid[1]=='S' || Maxbid[1]=='N') {pass = false;} break;
					case 'N':
						if (Maxbid[1]=='N') {pass = false;} break;
				}
				if (pass) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return true;
			}
		}
		else {
			return false;
		}


		/*if( bid=="PS" || Maxbid=="00")	//判斷喊牌是否符合規則 
		{
				cout<<bid<<endl;
				break;
		}
		if( bid=="X" && Maxbid!="00")	//判斷喊牌是否符合規則 
		{
				cout<<bid<<endl;
				break;
		}
		if( bid=="XX" && ( auction_log[ auction_log.size()-1 ]=="X" || auction_log[ auction_log.size()-3 ]=="X"))	//判斷喊牌是否符合規則 
		{
				cout<<bid<<endl;
				break;
		}
		if(bid[0]<'8' && bid[0]>Maxbid[0])
		{
			cout<<bid<<endl;
			break;
		}
		if(bid[0]<'8' && bid[0]==Maxbid[0] && Maxbid[1]=='C' &&( bid[1]=='S' || bid[1]=='H' || bid[1]=='D' ||(bid[1]=='N' && bid[2]=='T')) )
		{
			cout<<bid<<endl;
			break;
		}
		if(bid[0]<'8' && bid[0]==Maxbid[0] && Maxbid[1]=='D' &&(bid[1]=='H' || bid[1]=='S' ||(bid[1]=='N' && bid[2]=='T')) )
		{
			cout<<bid<<endl;
			break;
		}
		if(bid[0]<'8' && bid[0]==Maxbid[0] && Maxbid[1]=='H' && ( bid[1]=='S' ||(bid[1]=='N' && bid[2]=='T') ))
		{
			cout<<bid<<endl;
			break;
		}
		if(bid[0]<'8' && bid[0]==Maxbid[0] && Maxbid[1]=='S' && bid[1]=='N' && bid[2]=='T')
		{
			cout<<bid<<endl;
			break;
		}
		else
		{
			cout<<bid<<endl<<"You have an error bid  !!!"<<endl;
		}*/
	//}
	//decideBid=bid;
}

void Player::printTable()
{
	system("cls");
	for(int i=0;i<auction_log.size();i++)
	{
		if(i%4==0){
			cout<<endl<<"auction_log: ";
		}
		cout<<auction_log[i]<<" ";
	}
	//position=0;			//等等註解調
	//declarer_position=1;
	char Pos[4]={'N','E','S','W'};
	//cout<<position<<endl;
	cout<<endl<<" ------------"<<Pos[(position+2)%4]<<"------------- "<<endl;
	cout<<"|                          |"<<endl;
	cout<<"|                          |"<<endl;
	cout<<"|                          |"<<endl;
	cout<<"|                          |"<<endl;
	cout<<"|                          |"<<endl;
	cout<<Pos[(position+1)%4]<<"             "<<(playcard==""?"  ":playcard)<<"           "<<Pos[(position+3)%4]<<endl;
	cout<<"|                          |"<<endl;
	cout<<"|                          |"<<endl;
	cout<<"|                          |"<<endl;
	cout<<"|                          |"<<endl;
	cout<<"|                          |"<<endl;
	cout<<"|                          |"<<endl;
	cout<<" -------------"<<Pos[position]<<"------------- "<<endl;

	cout<<"This is myCard !!!"<<endl;
	for ( int i=0;i<Card[position].size();i++ ){
		cout<<Card[position][i]<<" ";
	}
	if(trick_log[0][0]!=""){
		cout<<endl<<endl<<endl<<endl<<endl<<"This is dummyCard"<<endl;
		for ( int i=0;i<Card[(declarer_position+2)%4].size();i++ ){
			cout<<Card[(declarer_position+2)%4][i]<<" ";
		}
	}
	cout<<endl<<endl<<"contract_suit: "<<contract_suit<<endl
					<<"contract_trick: "<<contract_trick<<endl
					<<"contract_dbl: "<<contract_dbl<<endl
					<<"declarer_position: "<<declarer_position<<endl
					<<"ns_trick: "<<ns_trick<<endl
					<<"ew_trick: "<<ew_trick<<endl
					<<"ns_point: "<<ns_point<<endl
					<<"ew_point: "<<ew_point<<endl;
		//cout<<Pos[statement%10]<<" Play Card: \n";
		
		for (int i=0; i<turn; i++) {
			cout << Pos[(statement-turn+i)%4] << ": " << trick_log[ns_trick + ew_trick][i] << endl;
		}
	
}

bool Player::playCard (string playcard)
{
	//cin.clear();
	/*for(int i=0;i<13;i++)
	{
		for(int j=0;j<4;j++)
		{
			trick_log[i][j]="00";
		}
	}
	ns_trick=1;
	ew_trick=11;
	trick_log[12][0]="00";*/
	if(trick_log[ns_trick+ew_trick][0]!="")
	{
		//cout<<"Front Play :"<<trick_log[ns_trick+ew_trick][0]<<endl;
		Suits=trick_log[ns_trick+ew_trick][0][0];
	}
	//else cout<<"You are the first"<<endl;
	vector<string>::iterator it;	
	//while (true)
	//{
		//cout<<"Please enter a card: ";
		//getline(cin,playcard);
		transform(playcard.begin(),playcard.end(),playcard.begin(),::toupper);
		it=find(Card[statement%10].begin(),Card[statement%10].end(),playcard);			//判斷 myCard 裡面有沒有 playCard
		if( it!=Card[statement%10].end() &&( trick_log[ns_trick+ew_trick][0]=="" || playcard[0]==Suits || MySuits(Suits)==false) )	{ return true; }	//判斷可不可以出這張牌。 1.有這張牌 2.花色對 or 手牌中沒有這個花色 or 第一個出牌
		/*else if(playcard=="CLAIM")
		{
			cout<<"How many tricks : ";
			int i=1;
			for(i=1;i<=( 13-ns_trick-ew_trick ) ;i++)	cout<<i<<" ";
			cout<<endl;
			cin>>decideClaim;
			claim();
			//break;
		}*/

		return false;
		//cout<<"Error!!!  You can't play this card."<<endl;
	//}
	//decideCard = playcard;
}

void Player::claim()
{
	
}

bool Player::MySuits(char suits)	//判斷自己有沒有這個花色 有則回傳 true ，否則回傳 false
{
	int check=0;
	for(int i=0;i<Card[statement%10].size();i++)
	{
		if( Card[statement%10][i][0]==suits)
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
