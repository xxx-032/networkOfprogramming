#include"server.h"


Server::Server() {
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 2);
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		//�ж��Ƿ������Ӧ�汾��WinSock.dll.
		exit(0);
	}
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	//socket������,protocolΪtcp.
	//UDP socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (serverSocket == INVALID_SOCKET)
	{
		//�ж�Socket״̬.
		exit(0);
	}


}


void Server::Receive(const SOCKET& client) {
	char msg[1024];
	memset(msg, 0, sizeof(msg));
	/*����жϽ����Ƿ����*/
	recv(client, msg, sizeof(msg), 0);

	if (strlen(msg) > 0)
		std::cout << msg << std::endl;
}

void Server::Send(const SOCKET& client) {
	if (send(client, "hello,client", strlen("hello,client"), 0) == SOCKET_ERROR)
	{
		//����ʧ��
	}
}

void Server::Accept() {
	sockaddr_in client_Address;
	SOCKET client = accept(serverSocket, (sockaddr *)&client_Address, NULL);
	if (client == INVALID_SOCKET) 
	{
		//�Ƿ��û�����
	}
	else 
	{
		std::cout << "ip: " << inet_ntoa(client_Address.sin_addr) << "ͨ��[" << ntohs(client_Address.sin_port) << "]�������˷�����." << std::endl;
		Server::Receive(client);
		Server::Send(client);

		//Server::Accept();

	}


}



void Server::Start(unsigned int port) {
	/*serverAddr */
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.S_un.S_addr = INADDR_ANY;	/*��������IP*/

	/*��socket;*/
	if (bind(serverSocket, (sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		//��socketʧ�����ͷ���Դ�˳�
		closesocket(serverSocket);
		WSACleanup();
		exit(0);
	}

	if (listen(serverSocket, 1024) == SOCKET_ERROR)
	{
		//�������ض˿�ʧ�����ͷ���Դ�˳�
		closesocket(serverSocket);
		WSACleanup();
		exit(0);
	}

	std::cout << "�������ѿ���,�ȴ�����..."<< std::endl;

	Server::Accept();
}