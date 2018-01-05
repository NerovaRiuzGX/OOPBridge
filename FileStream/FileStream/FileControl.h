#ifndef FILECONTROL_H
#define FILECONTROL_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//temporary class definition
class Host {};
class Player {};

class FileControl {
	public:
		FileControl (string);
		void read ();
		void write (string, string); 
		// ([variable name], [data])
		void split (string, string, vector<string> &); 
		// ([string source], [delimiter], [output vector])

		void pkgrcv (string, Host &);
		void pkgrcv (string, Player &);
		string pkgsnd ();

		void decode (vector<vector<string>> &, Host &);
		void decode (vector<vector<string>> &, Player &);

		void encode ();

	private:
		ifstream FILE_INPUT;
		ofstream FILE_OUTPUT;
		string FILE_NAME;
};

#endif