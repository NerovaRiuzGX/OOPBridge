//Server.cpp
//by NerovaRiuzGX 2017.12.30

#include <iostream>

#include "TCPServer.h"

TCPServer server;

void * loop (void * m) {
	
	pthread_detach(pthread_self());
	while (true) {
		
		string str = server.getMessage();
		if (str != "") {
			
			cout << "From user " << server.clientInfo.sin_addr.s_addr << ", Message: " << str << endl;
			server.sendMessage("received.");
			server.clean();
		}
		_sleep(500);
	}
	server.detach();
}

int main () {
	
	pthread_t thread;
	server.setup(10555);
	if (pthread_create(&thread, NULL, loop, (void *)0) == 0) {
		server.receive();
	}
	return 0;
}