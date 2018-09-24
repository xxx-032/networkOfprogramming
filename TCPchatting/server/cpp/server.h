#pragma once


#include<iostream>
#include <WinSock2.h>
#include<windows.h>
#pragma comment(lib,"ws2_32.lib")


class Server {
private:
	SOCKET serverSocket;
	sockaddr_in serverAddr;
public:
	Server();

	void Accept();
	void Receive(const SOCKET&);
	void Send(const SOCKET&);
	void Start(unsigned int port);
};