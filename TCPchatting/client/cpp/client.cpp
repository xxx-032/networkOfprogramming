#include"client.h"



Client::Client() {
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 2);
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		//�ж��Ƿ������Ӧ�汾��WinSock.dll.
		exit(0);
	}

	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	//socket������,protocolΪtcp.
																//UDP socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (clientSocket == INVALID_SOCKET)
	{
		//�ж�Socket״̬.
		exit(0);
	}
}

void Client::Receive()
{
	char msg[1024];
	memset(msg, 0, sizeof(msg));
	recv(clientSocket, msg, sizeof(msg), 0);
	if (strlen(msg) > 0)
		std::cout << msg << std::endl;
}




void Client::Send()
{
	if (send(clientSocket, "hello,server", strlen("hello,server"), 0) == SOCKET_ERROR)
	{
		//����ʧ����
	}
}

void Client::Start(unsigned int port) {

	/*��ʼ���ͻ��˽ṹ*/
	clientAddr.sin_family = AF_INET;
	clientAddr.sin_port = htons(port);
	clientAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	
	if (connect(clientSocket, (sockaddr *)&clientAddr, sizeof(sockaddr)) == SOCKET_ERROR) {
		closesocket(clientSocket);
		WSACleanup();
		exit(0);
	}
	Send();
	Receive();
}

