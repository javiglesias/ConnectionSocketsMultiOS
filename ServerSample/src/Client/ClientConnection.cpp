#include "ClientConnection.h"

bool ClientConnection::init(){
	if(WINDOWS){
		int win_result;
		WSADATA wsadat;
		win_result = STARTDLL(&wsadat)
		if(win_result != 0)
			return false;
	}
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0){
		ERR("Fail socket creation");
		return false;
	}
	else
		LOG("Socket creation Succesfull");
	ZERO(serv_addr)
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	if(inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr) < 0)
	{
		ERR("Cant bind serv address on client!");
		return false;
	}
	else
		LOG("Bind creation Succesfull");
	if(connect(sock, (SOCKADDR *)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
	{
		ERR("Cant Connect!");
		CLEAR();
		return false;
	}
	else
		LOG("Client Connection creation Succesfull");
	ZERO(buffer)
	while(true)
	{
		while ((n = SOCKREAD(sock, buffer, 0)) > 0)
		{
			LOG(buffer);
			fprintf(stdout, "Write a message: ");
			if (fscanf(stdin, "%s", &out_buffer))
			{
				if (SOCKSEND(sock, out_buffer, 0) == SOCKET_ERROR)
				{
					ERR("Error sending data.");
					break;
				}
			}
			n = -1;
			ZERO(out_buffer)
			ZERO(buffer)
		}
	}
	return true;
}
void ClientConnection::Clean() const{
	CLEAR();
	CLOSE(sock)
}
std::string ClientConnection::codification(std::string msg, std::string key){
    // Make sure the key is at least as long as the message
    std::string tmp(key);
    while (key.size() < msg.size())
        key += tmp;
    
    // And now for the encryption part
    for (std::string::size_type i = 0; i < msg.size(); ++i)
        msg[i] ^= key[i];
    return msg;
}