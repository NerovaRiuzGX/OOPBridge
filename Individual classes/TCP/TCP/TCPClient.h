//TCPClient.h
//by NerovaRiuzGX 2018.01.03

#ifndef TCPCLIENT_H
#define TCHCLIENT_H

#include "TCPServer.h"

using namespace std;

class TCPClient: public TCPServer {

	public:
		TCPClient();
		virtual void setup (string, int);
		void detach ();

		int sendMessage (string, int = 0);
		string receiveMessage (int = 0);
		

	private:
		int sock;
		struct sockaddr_in server;
};

#endif /* TCPCLIENT_H */