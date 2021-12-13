#pragma once
#ifndef C__SERVERCONN_H
#define C__SERVERCONN_H
#include "../Definitions.hpp"

class ServerConnection
{
public:
	ServerConnection(){}
	ServerConnection(unsigned int _port) { port = _port; }
	bool init();
private:
	SOCKET sock = 0, new_socket = 0;
	struct sockaddr_in serv_addr;
	struct hostent* server = NULL;
	char buffer[250];
	char opt = 1;
	unsigned int port = 51717;
	int  n = 0, concurrent_clients[30], max_sd, active_clients;
	fd_set read_fds;
};
#endif
