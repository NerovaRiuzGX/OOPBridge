#include <ctime>

#include "FileControl.h"
//#include "Host.h"

int main () {
	srand(time(NULL));
	FileControl FILE("test.bridge");
	/*while (true) {
		string data;
		getline(cin, data);
		FILE.write("variable", data);
		FILE.read();
	}*/
	Player host;
	host.shuffle();
	cout << FILE.pkgsnd(host) << endl;
	FILE.write(FILE.pkgsnd(host));
	FILE.pkgrcv(FILE.pkgsnd(host), host);
	cout << FILE.pkgsnd(host) << endl;
	system("pause");
	return 0;
}