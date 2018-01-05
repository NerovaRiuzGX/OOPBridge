#include "FileControl.h"
#include "Host.h"

int main () {
	FileControl FILE("test.bridge");
	/*while (true) {
		string data;
		getline(cin, data);
		FILE.write("variable", data);
		FILE.read();
	}*/
	Host host;
	host.shuffle();
	cout << FILE.pkgsnd(host) << endl;
	FILE.write(FILE.pkgsnd(host));
	system("pause");
	return 0;
}