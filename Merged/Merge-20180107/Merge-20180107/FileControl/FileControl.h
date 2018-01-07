#ifndef FILECONTROL_H
#define FILECONTROL_H

#include "..\Host\Host.h"
#include "..\Player\Player.h"

#include <fstream>

using namespace std;

class FileControl {
	public:
		FileControl (string = "test.bridge");
		void read ();
		void write (string); 
		// ([variable name], [data])
		void split (string, string, vector<string> &); 
		// ([string source], [delimiter], [output vector])

		void pkgrcv (string, Host &);
		void pkgrcv (string, Player &);
		string pkgsnd (Host &);
		string pkgsnd (Player &);

	private:
		ifstream FILE_INPUT;
		ofstream FILE_OUTPUT;
		string FILE_NAME;
		int PACKAGE_NUMBER;
};

#endif