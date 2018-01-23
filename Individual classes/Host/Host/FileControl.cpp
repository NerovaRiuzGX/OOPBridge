#include "FileControl.h"

FileControl::FileControl (string name) {
	FILE_NAME = name;
	PACKAGE_NUMBER = 0;
}

void FileControl::read () {
	FILE_INPUT.open (FILE_NAME);
	if (FILE_INPUT.is_open()) {
		string buffer;
		while (getline(FILE_INPUT, buffer)) {
			vector<string> buff;
			split(buffer, "=", buff);
			cout << buff[0] << ". " << buff[1] << ": " << buff[2] << endl;
			//cout << buffer << '\n';
		}
	}
	FILE_INPUT.close();
	return;
}

void FileControl::write (string data) {
	FILE_OUTPUT.open (FILE_NAME, ios::app);
	if (FILE_OUTPUT.is_open()) {
		FILE_OUTPUT << data;
	}
	FILE_OUTPUT.close();
	return;
}

void FileControl::split(string phrase, string delim, vector<string> &data) {
	char* str = &phrase[0];
	char * pch;
	pch = strtok (str, delim.c_str());
	while (pch != NULL) {
		//printf ("%s\n",pch);
		data.push_back(string(pch));
		pch = strtok (NULL, delim.c_str());
	}
	return;
}

void FileControl::pkgrcv (string pkg, Host & host) {
	vector<string> variable;
	vector<vector<string>> list;
	split(pkg, "\n", variable);

	for (int i=0; i<variable.size(); i++) {
		split(variable[i], ">", list[i]);
	}

	for (int i=0; i<list.size(); i++) {
		switch(atoi(list[i][0].c_str())){
			//From Player
			case 15: //position: int
				break;
			case 16: //bid(): string
				break;
			case 17: //playCard(): string
				break;
			case 18: //claim(): string
				break;

			//Data information
			case 19: //pkgnum: int
				PACKAGE_NUMBER = atoi(list[i][3].c_str());
				break;
			case 20: //statement
			default: break;
		}
	}
}

void FileControl::pkgrcv (string pkg, Player & player) {
	vector<string> variable;
	vector<vector<string>> list;
	split(pkg, "\n", variable);

	for (int i=0; i<variable.size(); i++) {
		split(variable[i], ">", list[i]);
	}

	for (int i=0; i<list.size(); i++) {
		switch(atoi(list[i][0].c_str())){
			//From Host
			case 1: //round: int
				break;
			case 2: //ns_vulnerable: bool
				break;
			case 3: //ew_vulnerable: bool
				break;
			case 4: //Card[4]: vector<string>
				break;
			case 5: //turn: int
				break;
			case 6: //auction_log: vector<string>
				break;
			case 7: //contract_suit: int
				break;
			case 8: //contract_trick: int
				break;
			case 9:	//declarer_positon: int
				break;
			case 10: //trick_log: vector<string>
				break;
			case 11: //ns_trick: int
				break;
			case 12: //ew_trick: int
				break;
			case 13: //ns_point: int
				break;
			case 14: //ew_point: int
				break;
			case 31: //contract_dbl: int
				break;

			//Data information
			case 19: //pkgnum: int

				break;
			case 20: //statement
			default: break;
		}
	}
}

string FileControl::pkgsnd (Host& host) {
	string pkg = "";
	char buffer[11];
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
			pkg += (host.Card[i][j] + ' ');
		}
		pkg += '-';
	}
	pkg += '\n';
	//case 5: turn: int
	pkg += ("5>turn>" + string(itoa(host.turn, buffer, 10)) + '\n');
	//case 6: auction_log: vector<string>
	pkg += ("6>auction_log>");
	for (int i=0; i<host.auction_log.size(); i++) {
		pkg += (host.auction_log[i] + ' ');
	}
	pkg += '\n';
	//case 7: contract_suit: int
	pkg += ("7>contract_suit>" + string(itoa(host.contract_suit, buffer, 10)) + '\n');
	//case 8: contract_trick: int
	pkg += ("8>contract_trick>" + string(itoa(host.contract_trick, buffer, 10)) + '\n');
	//case 9: declarer_positon: int
	pkg += ("9>declarer_position>" + string(itoa(host.declarer_position, buffer, 10)) + '\n');
	//case 10: trick_log: vector<string>
	pkg += ("10>trick_log>");
	for (int i=0; i<host.trick_log.size(); i++) {
		pkg += (host.trick_log[i] + ' ');
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
		

	//Data information
	//case 19: pkgnum: int
	pkg += ("19>pkgnum>" + string(itoa(PACKAGE_NUMBER, buffer, 10)) + '\n');
		
	//case 20: statement
	
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