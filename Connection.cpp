#include "Connection.h"
Connection::Connection(std::string _ip,std::string _user, std::string _passwd){
	ip = _ip;
	user = _user;
	passwd = _passwd;
}

bool Connection::init(){
	if(WINDOWS){
		int win_result;
		WSADATA wsadat;
		win_result = STARTDLL(&wsadat);
		if(win_result != 0)
			return -1;
	}
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0){
		LOG("Fail socket creation");
		return false;
	}
	else
		LOG("Socket creation Succesfull");
	server=gethostbyname(ip.c_str());
	ZERO(&serv_addr)
	COPY((char *)&serv_addr.sin_addr.s_addr, (char *)server->h_addr,
		server->h_length)
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	if(connect(sock, (struct sockaddr *)&serv_addr, sizeof	serv_addr) < 0){
		LOG("Cant Connect!");
		return false;
	}
	else{
		std::cout << "connection finished";
	}
	ZERO(buffer)
	passwd = codification(passwd, user);
	LOG("passwd_encrypt:");
	LOG(passwd.c_str());	
	
	if(SOCKSEND(sock, passwd.c_str(), 0) < 0){
		LOG("Cannot send auth to server");
		return false;
	}
	else
		LOG("auth sended to server");
	/*n = read(sock, buffer, 255);
	if(n < 0){
		LOG("Cant recieve from server.");
		return false;
	}
	else
		LOG("Entering data....");*/
	return true;
}
void Connection::clean(){
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