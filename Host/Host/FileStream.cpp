#include "FileControl.h"

int main () {
	FileControl FILE("test.bridge");
	while (true) {
		string data;
		getline(cin, data);
		FILE.write("variable", data);
		FILE.read();
	}
	system("pause");
	return 0;
}