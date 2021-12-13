#include "Server/ServerConnection.h"
#include "Client/ClientConnection.h"
#include <cstdio>

int main(int args, char** argv)
{
	// TODO args management
	if (args > 0)
	{
		if (strcmp(argv[1], "SERVER") == 0)
		{
			ServerConnection* serv_conn;
			LOG("LAUNCHING IN SERVER MODE (Press a key to continue)");
			unsigned int port;
			fprintf(stdout, "Enter the port:");
			fscanf(stdin, "%u", &port);
			serv_conn = new ServerConnection(port);
			return serv_conn->init();
		}
		else if (strcmp(argv[1], "CLIENT") == 0)
		{
			ClientConnection* client_conn;
			LOG("LAUNCHING IN CLIENT MODE (Press a key to continue)");
			unsigned int port;
			char ip[32];
			fprintf(stdout, "Ip address:");
			fscanf(stdin, "%s", &ip);
			fprintf(stdout, "Port:");
			fscanf(stdin, "%u", &port);
			client_conn = new ClientConnection(ip, port);
			return client_conn->init();
		}
	}
	return -1;
}
