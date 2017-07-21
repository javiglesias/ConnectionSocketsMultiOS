#pragma once 

/*this library is gonna provide the sockets connection*/
#include "lib.h"
#include <string>

#if _WIN32
#define WINDOWS 1
#include <Windows.h>
#pragma comment(lib, "ws2_32.lib")
#define ZERO(X) ZeroMemory(X, sizeof X);
#define COPY(X,Y,Z) memcpy(X,Y,Z);
#define STARTDLL(X) WSAStartup(MAKEWORD(2,2), X);
#define SOCKSEND(X,Y,Z) send(X, Y, sizeof Y, Z)
#define CLOSE(X) closesocket(X);
#else
#define WINDOWS 0
#define SOCKET int
#define ZERO(X) bzero(X, sizeof X);
#define COPY(X,Y,Z) bcopy(Y, X, sizeof Y);
#define SOCKSEND(X,Y,Z) write(X, Y, sizeof Y)
#define CLOSE(X) close(X);
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <unistd.h>
#endif
class Connection{
public:
	Connection(std::string _ip, std::string _user, std::string _passwd);
	~Connection();
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
};