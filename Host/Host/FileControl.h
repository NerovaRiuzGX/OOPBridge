#ifndef FILECONTROL_H
#define FILECONTROL_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Host.h"

using namespace std;

//temporary class definition
//class Host {};
class Player {};

class FileControl {
	public:
		FileControl (string = "test.bridge");
		void read ();
		void write (string); 
		// ([variable name], [data])
		void split (string, string, vector<string> &); 
		// ([string source], [delimiter], [output vector])

		void pkgrcv (string, Host&);
		void pkgrcv (string, Player &);
		string pkgsnd (Host &);

		void decode (vector<vector<string>> &, Host&);
		void decode (vector<vector<string>> &, Player &);

		void encode ();

	private:
		ifstream FILE_INPUT;
		ofstream FILE_OUTPUT;
		string FILE_NAME;
		int PACKAGE_NUMBER;
};

#endif