#pragma once
#ifndef __DEFINITIONS
#define __DEFINITIONS
#if _WIN32
#define WINDOWS 1
#include <WS2tcpip.h>
#include <Windows.h>
#pragma comment(lib, "ws2_32.lib")
#define ZERO(X) ZeroMemory(&X, sizeof X);
#define COPY(X,Y,Z) memcpy(X,Y,Z);
#define STARTDLL(X) WSAStartup(MAKEWORD(2,2), X);
#define SOCKSEND(X,Y,Z) send(X, Y, sizeof Y, Z)
#define SOCKREAD(X,Y,Z) recv(X, Y, sizeof Y, Z)
#define SETSOCKOPT(X,Y,Z,T) setsockopt(X, Y, Z, &T, sizeof T)
#define BIND(X,Y) bind(X, (struct sockaddr *)Y, sizeof Y) // TODO review this macro
#define LISTEN(X,Y) listen(X, Y)
#define SELECT(X,Y) select(X+1, &Y, nullptr, nullptr, nullptr)
#define ACCEPT(X,Y) accept(X, (struct sockaddr *)Y, (socklen_t *)(sizeof Y))
#define CLEAR()  WSACleanup()
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

#include <iostream>

#define LOG(X) std::cout << X << '\n'
#define ERR(X) std::cerr << X << '\n'
#endif
