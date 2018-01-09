//FileControl.cpp
//by NerovaRiuzGX 2018.01.03

#include "FileControl.h"

FileControl::FileControl (string name) {
	FILE_NAME = name;
	PACKAGE_NUMBER = 0;
}

void FileControl::read () { // not really useful in this game
	FILE_INPUT.open (FILE_NAME);
	if (FILE_INPUT.is_open()) {
		string buffer;
		while (getline(FILE_INPUT, buffer)) {
			/*vector<string> buff;
			split(buffer, "=", buff);
			cout << buff[0] << ". " << buff[1] << ": " << buff[2] << endl;*/
			//cout << buffer << '\n';
		}
	}
	FILE_INPUT.close();
	return;
}

void FileControl::write (string data) {
	FILE_OUTPUT.open (FILE_NAME/*, ios::app*/); // only add app when you want to get multiple packages in file.
	if (FILE_OUTPUT.is_open()) {
		FILE_OUTPUT << data;
	}
	FILE_OUTPUT.close();
	return;
}

void FileControl::split(string phrase, char delim, vector<string> &data) {
	/*char* str = &phrase[0];
	char * pch;
	pch = strtok (str, delim.c_str());
	while (pch != NULL) {
		//printf ("%s\n",pch);	//for test
		data.push_back(string(pch));
		pch = strtok (NULL, delim.c_str());
	}
	return;*/

	istringstream iss(phrase);
	string token;
	while (getline(iss, token, delim)) {
		data.push_back(token);
	}
}

void FileControl::pkgrcv (string pkg, Host & host) {
	vector<string> variable;
	vector<vector<string>> list;
	split(pkg, '\n', variable);

	list.resize(variable.size());

	for (int i=0; i<variable.size(); i++) {
		split(variable[i], '>', list[i]);
	}

	int pos = host.statement%10;
	int position;

	for (int i=0; i<list.size(); i++) {
		switch(atoi(list[i][0].c_str())){
			//From Player
			case 15: //position: int
				//do nothing, actually
				position = atoi(list[i][2].c_str());
				break;
			case 16: //decideBid: string
				if (host.statement/10==1) {
					if (pos == position && list[i].size()==3){
						if (list[i][2]!="00") {
							host.auction_log.push_back(list[i][2]);
							host.statement = 10 + (pos+1)%4;
						}
					}
				}
				break;
			case 17: //decideCard: string
				if (host.statement/10==2) {
					if (pos == position && list[i].size()==3){
						if (list[i][2]!="00" && host.turn<4) {
							host.trick_log[host.ns_trick + host.ew_trick][host.turn] = list[i][2];
							//host.Card[pos].erase ( remove ( host.Card[pos].begin(), host.Card[pos].end(), list[i][2] ), host.Card[host.turn].end() );
							for (int j=0; j<host.Card[pos].size(); j++) {
								if (list[i][2]==host.Card[pos][j]) {
									host.Card[pos].erase(host.Card[pos].begin()+j);
									break;
								}
							}
							host.statement = 20 + (pos+1)%4;
							host.turn++;
						}
					}
				}
				
				break;
			case 18: //decideClaim: int
				if (atoi(list[i][2].c_str())!=-1){
					//will work on this later
				}
				break;

			//Data information
			case 19: //pkgnum: int
				PACKAGE_NUMBER = atoi(list[i][2].c_str());
				break;
			case 20: //statement
				//host.statement = atoi(list[i][2].c_str());
				break;

			default: break;
		}
	}
}

void FileControl::pkgrcv (string pkg, Player & player) {
	vector<string> variable, element;
	vector<vector<string>> list;
	split(pkg, '\n', variable);
	list.resize(variable.size());
	for (int i=0; i<variable.size(); i++) {
		split(variable[i], '>', list[i]);
	}

	variable.clear();

	player.decideBid = "00";
	player.decideCard = "00";

	for (int i=0; i<list.size(); i++) {
		switch(atoi(list[i][0].c_str())){
			//From Host
			case 1: //round: int
				player.round = atoi(list[i][2].c_str());
				break;
			case 2: //ns_vulnerable: bool
				if (list[i][2][0]=='1') {player.ns_vulnerable = true;}
				else {player.ns_vulnerable = false;}
				break;
			case 3: //ew_vulnerable: bool
				if (list[i][2][0]=='1') {player.ew_vulnerable = true;}
				else {player.ew_vulnerable = false;}
				break;
			case 4: //Card[4]: vector<string>
				split(list[i][2], '-', variable);
				for (int j=0; j<variable.size(); j++) {
					split(variable[j], ' ', element);
					player.Card[j].clear();
					for (int k=0; k<element.size(); k++) {
						player.Card[j].push_back(element[k]);
					}
					element.clear();
				}
				variable.clear();
				break;
			case 5: //turn: int
				player.turn = atoi(list[i][2].c_str());
				break;
			case 6: //auction_log: vector<string>
				if (list[i].size()==3) {
					split(list[i][2], ' ', variable);
				}
				
				player.auction_log.clear();
				for (int j=0; j<variable.size(); j++) {
					player.auction_log.push_back(variable[j]);
				}
				variable.clear();
				break;
			case 7: //contract_suit: int
				player.contract_suit = atoi(list[i][2].c_str());
				break;
			case 8: //contract_trick: int
				player.contract_trick = atoi(list[i][2].c_str());
				break;
			case 9:	//declarer_positon: int
				player.declarer_position = atoi(list[i][2].c_str());
				break;
			case 10: //trick_log: string[13][4]
				split(list[i][2], '-', variable);
				for (int j=0; j<variable.size(); j++) {
					split(variable[j], ' ', element);
					for (int k=0; k<element.size(); k++) {
						player.trick_log[j][k] = element[k];
					}
					element.clear();
				}
				variable.clear();
				break;
			case 11: //ns_trick: int
				player.ns_trick = atoi(list[i][2].c_str());
				break;
			case 12: //ew_trick: int
				player.ew_trick = atoi(list[i][2].c_str());
				break;
			case 13: //ns_point: int
				player.ns_point = atoi(list[i][2].c_str());
				break;
			case 14: //ew_point: int
				player.ew_point = atoi(list[i][2].c_str());
				break;
			case 31: //contract_dbl: int
				player.contract_dbl = atoi(list[i][2].c_str());
				break;

			//Data information
			case 19: //pkgnum: int
				if (atoi(list[i][2].c_str()) == PACKAGE_NUMBER) {
					PACKAGE_NUMBER++;
				}
				break;
			case 20: //statement
				player.statement = atoi(list[i][2].c_str());
				break;

			default: break;
		}
	}
}

string FileControl::pkgsnd (Host & host) {
	string pkg = "0>EMPTY_PACKAGE>0\n";
	char buffer[11] = {};
	//To Player
	//case 1: round: int
	pkg += ("1>round>" + string(itoa(host.round, buffer, 10)) + '\n');
	//case 2: ns_vulnerable: bool
	pkg += ("2>ns_vulnerable>");
	if (host.ns_vulnerable) {pkg += ("1\n");}
	else {pkg += ("0\n");}
	//case 3: ew_vulnerable: bool
	pkg += ("3>ew_vulnerable>");
	if (host.ew_vulnerable) {pkg += ("1\n");}
	else {pkg += ("0\n");}
	//case 4: Card[4]: vector<string>
	pkg += ("4>Card>");
	for (int i=0; i<4; i++) {
		for (int j=0; j<host.Card[i].size(); j++) {
			pkg += (host.Card[i][j] + ((j==host.Card[i].size()-1)?"":" "));
		}
		pkg += ((i==3)?"":"-");
	}
	pkg += '\n';
	//case 5: turn: int
	pkg += ("5>turn>" + string(itoa(host.turn, buffer, 10)) + '\n');
	//case 6: auction_log: vector<string>
	pkg += ("6>auction_log>");
	for (int i=0; i<host.auction_log.size(); i++) {
		pkg += (host.auction_log[i] + ((i==host.auction_log.size()-1)?"":" "));
	}
	pkg += '\n';
	//case 7: contract_suit: int
	pkg += ("7>contract_suit>" + string(itoa(host.contract_suit, buffer, 10)) + '\n');
	//case 8: contract_trick: int
	pkg += ("8>contract_trick>" + string(itoa(host.contract_trick, buffer, 10)) + '\n');
	//case 9: declarer_positon: int
	pkg += ("9>declarer_position>" + string(itoa(host.declarer_position, buffer, 10)) + '\n');
	//case 10: trick_log: string[13][4]
	pkg += ("10>trick_log>");
	for (int i=0; i<13; i++) {
		for (int j=0; j<4; j++) {
			pkg += (host.trick_log[i][j] + ((j==3)?"":" "));
		}
		pkg += ((i==12)?"":"-");
	}
	pkg += '\n';
	//case 11: ns_trick: int
	pkg += ("11>ns_trick>" + string(itoa(host.ns_trick, buffer, 10)) + '\n');
	//case 12: ew_trick: int
	pkg += ("12>ew_trick>" + string(itoa(host.ew_trick, buffer, 10)) + '\n');
	//case 13: ns_point: int
	pkg += ("13>ns_point>" + string(itoa(host.ns_point, buffer, 10)) + '\n');
	//case 14: ew_point: int
	pkg += ("14>ew_point>" + string(itoa(host.ew_point, buffer, 10)) + '\n');
	//case 31: contract_dbl: int
	pkg += ("31>contract_dbl>" + string(itoa(host.contract_dbl, buffer, 10)) + '\n');

	//Data information
	//case 19: pkgnum: int
	pkg += ("19>pkgnum>" + string(itoa(PACKAGE_NUMBER, buffer, 10)) + '\n');
		
	//case 20: statement
	pkg += ("20>statement>" + string(itoa(host.statement, buffer, 10)) + '\n');

	return pkg;
}

string FileControl::pkgsnd (Player & player) {
	string pkg = "0>EMPTY_PACKAGE>0\n";
	char buffer[11] = {};

	//To Host
	//case 15: position: int
	pkg += ("15>position>" + string(itoa(player.position, buffer, 10)) + '\n');
	//case 16: decideBid: string
	pkg += ("16>decideBid>" + player.decideBid + '\n');
	//case 17: decideCard: string
	pkg += ("17>decideCard>" + player.decideCard + '\n');
	//case 18: decideClaim: int
	pkg += ("18>decideClaim>" + string(itoa(player.decideClaim, buffer, 10)) + '\n');

	//Data information
	//case 19: pkgnum: int
	pkg += ("19>pkgnum>" + string(itoa(PACKAGE_NUMBER, buffer, 10)) + '\n');
	//case 20: statement
	pkg += ("20>statement>" + string(itoa(player.statement, buffer, 10)) + '\n');
	
	return pkg;
}

// the encoded string uses the format below:
// 
// || 0>EMPTY_PACKAGE>0\n
// || 1>[variable name]>[variable data]\n
// || 2>[array/vector name]>[content01] [content02] [content03]...\n
// || 3>[statement name]>[statement data]\n...
// 
// which are all stored with type string.
