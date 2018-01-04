#include "FileControl.h"

int main () {
	FileControl FILE("test.txt");
	while (true) {
		string data;
		getline(cin, data);
		FILE.write(data);
		FILE.read();
	}
	system("pause");
	return 0;
}