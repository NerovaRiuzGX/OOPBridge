#include "FileControl.h"

FileControl::FileControl (string name) {
	FILE_NAME = name;
	
	
}

void FileControl::read () {
	FILE_INPUT.open (FILE_NAME);
	if (FILE_INPUT.is_open()) {
		string buffer;
		while (getline(FILE_INPUT, buffer)) {
			cout << buffer << '\n';
		}
	}
	FILE_INPUT.close();
}

void FileControl::write (string data) {
	FILE_OUTPUT.open (FILE_NAME);
	if (FILE_OUTPUT.is_open()) {
		FILE_OUTPUT << data << '\n';
	}
	FILE_OUTPUT.close();
}