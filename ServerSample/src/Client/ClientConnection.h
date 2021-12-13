#pragma once
#ifndef C__ClientConnection_H
#define C__ClientConnection_H
/*this library is gonna provide the sockets ClientConnection for the Client*/
#include <string>
#include "../Definitions.hpp"

class ClientConnection{
public:
	ClientConnection() {}
	ClientConnection(char* _ip, unsigned int _port) { ip = std::string(_ip); port = _port; }
	~ClientConnection(){}
	bool init();
	void Clean() const;
	std::string codification(std::string user, std::string passw);

private:
	std::string user, passwd;
	std::string ip;
	unsigned int port = 51717;
	SOCKET sock = 0, n = 0;
	struct sockaddr_in serv_addr;
	struct hostent *server = NULL;
	char buffer[4096];
	char out_buffer[4096];
	std::string c;
};
#endif
