#include "ServerConnection.h"
#include <random>

bool ServerConnection::init()
{
	if (WINDOWS) {
		int win_result;
		WSADATA wsadat;
		win_result = STARTDLL(&wsadat)
			if (win_result != 0)
				return false;
	}
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		ERR("Fail socket creation");
		return false;
	}
	else
		LOG("Socket creation Succesfull");
	if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt))
	{
		ERR("Duplicated");
		return false;
	}
	ZERO(serv_addr);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);
	if(bind(sock, (struct sockaddr *)&serv_addr, sizeof serv_addr) < 0)
	{
		ERR("Error Binding address");
		return false;
	}
	if(LISTEN(sock, 3) < 0)
	{
		ERR("Error Listening the addres/port");
		return false;
	}
	srand(NULL);
	while(true)
	{
		ZERO(read_fds);
		FD_SET(sock, &read_fds);
		max_sd = sock;
		for (auto sd : concurrent_clients)
		{
			if (sd > 0)
			{
				FD_SET(sd, &read_fds);
			}
			if (sd > max_sd)
			{
				max_sd = sd;
			}
		}
		// incomming connection detected
		active_clients = SELECT(max_sd, read_fds);
		if (active_clients < 0)
		{
			ERR("ERROR on select");
			break;
		}
		if (FD_ISSET(sock, &read_fds))
		{
			new_socket = accept(sock, nullptr, nullptr);
			if (new_socket < 0)
			{
				ERR("ERROR accepting connections");
				break;
			}
			LOG("Connection at");
			LOG(new_socket);
			SOCKSEND(new_socket, "Hola te saluda el servidor", 0);
			ZERO(buffer)
			while ((n = SOCKREAD(new_socket, buffer, 0)) > 0)
			{
				LOG(buffer);
				SOCKSEND(new_socket, m_answers[rand() % 5], 0);
				ZERO(buffer)
				n = -1;
			}
		}
	}
	LOG("EXITING IN SERVER MODE (Press a key to continue)");
	CLEAR();
	return true;
}
