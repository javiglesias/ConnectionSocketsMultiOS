#include "Connection.h"

Connection::Connection(std::string _ip,std::string _user, std::string _passwd){
	ip = _ip;
	user = _user;
	passwd = _passwd;
}

bool Connection::init(){
	LOG("LAUNCHING IN CLIENT MODE (Press a key to continue)");
	getchar();
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
	//server=gethostbyname(ip.c_str());
	ZERO(serv_addr)
	/*COPY((char *)&serv_addr.sin_addr.s_addr, (char *)server->h_addr,
		server->h_length)*/
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) < 0 )
	{
		ERR("Cant bind serv address on client!");
		getchar();
		return false;
	}
	if(connect(sock, (SOCKADDR *)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
	{
		ERR("Cant Connect!");
		getchar();
		CLEAR();
		return false;
	}
	ZERO(buffer)
	/*passwd = codification(passwd, user);	
	if(SOCKSEND(sock, passwd.c_str(), 0) < 0){
		ERR("Cannot send auth to server");
		return false;
	*/
	while((c = getchar()) != 'X')
	{
		if (SOCKSEND(sock, &c, 0)>0)
		{
			LOG("Sending...");
		}
		
	}
	
	/*else
		LOG("auth sended to server");
	n = SOCKREAD(sock, buffer, 255, 0);
	if(n < 0){
		ERR("Cant recieve from server.");
		getchar();
		return false;
	}
	else
		LOG("Entering data....");*/
	LOG("EXITING IN CLIENT MODE (Press a key to continue)");
	getchar();
	return true;
}
void Connection::clean(){
	CLEAR();
	CLOSE(sock)
}
std::string Connection::codification(std::string msg, std::string key){
    // Make sure the key is at least as long as the message
    std::string tmp(key);
    while (key.size() < msg.size())
        key += tmp;
    
    // And now for the encryption part
    for (std::string::size_type i = 0; i < msg.size(); ++i)
        msg[i] ^= key[i];
    return msg;
}