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
			cout << buff[0] << ": " << buff[1] << endl;
			//cout << buffer << '\n';
		}
	}
	FILE_INPUT.close();
}

void FileControl::write (string variable, string data) {
	FILE_OUTPUT.open (FILE_NAME, ios::app);
	if (FILE_OUTPUT.is_open()) {
		FILE_OUTPUT << variable << "=" << data << '\n';
	}
	FILE_OUTPUT.close();
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