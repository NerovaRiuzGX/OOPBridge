#include "FileControl.h"

FileControl::FileControl (string name) {
	FILE_NAME = name;
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

void FileControl::write (string variable, string data) {
	FILE_OUTPUT.open (FILE_NAME, ios::app);
	if (FILE_OUTPUT.is_open()) {
		FILE_OUTPUT << "0" << "=" << variable << "=" << data << '\n';
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

void FileControl::pkgrcv (string pkg, Host &) {
	vector<string> variable;
	vector<vector<string>> list;
	split(pkg, "\n", variable);

	for (int i=0; i<variable.size(); i++) {
		split(variable[i], "=", list[i]);
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
				break;
			case 20: //
			default: break;
		}
	}
}

void FileControl::pkgrcv (string pkg, Player &) {
	vector<string> variable;
	vector<vector<string>> list;
	split(pkg, "\n", variable);

	for (int i=0; i<variable.size(); i++) {
		split(variable[i], "=", list[i]);
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

			//Data information
			case 19: //pkgnum: int
				break;
			case 20: //
			default: break;
		}
	}
}

string FileControl::pkgsnd () {
	string pkg = "";



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