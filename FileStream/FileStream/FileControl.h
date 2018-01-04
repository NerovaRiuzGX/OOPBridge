#ifndef FILECONTROL_H
#define FILECONTROL_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class FileControl {
	public:
		FileControl (string);
		void read ();
		void write (string);

	private:
		ifstream FILE_INPUT;
		ofstream FILE_OUTPUT;
		string FILE_NAME;
};

#endif