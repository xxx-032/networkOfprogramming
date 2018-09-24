#pragma once

#include <stdio.h>
#include <WinSock2.h>
#include<iostream>
#pragma comment(lib,"ws2_32.lib")


class Client {
private:
	SOCKET clientSocket;
	sockaddr_in clientAddr;

public:
	Client();
	void Receive();
	void Send();
	void Start(unsigned int port);

};