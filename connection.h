#pragma once
#ifndef C__CONNECTION_H
#define C__CONNECTION_H
/*this library is gonna provide the sockets connection for the Client*/
#include <string>
#include "Definitions.hpp"

class Connection{
public:
	Connection() {}
	Connection(std::string _ip){ ip = _ip;};
	Connection(std::string _ip, std::string _user, std::string _passwd);
	~Connection(){}
	bool init();
	void clean();
	std::string codification(std::string user, std::string passw);

private:
	std::string user, passwd;
	std::string ip;
	const int port = 51717;
	SOCKET sock = 0, n = 0;
	struct sockaddr_in serv_addr;
	struct hostent *server = NULL;
	char buffer[250];
	char c;
};
#endif
