#include"server.h"


Server::Server() {
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 2);
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		//判断是否加载相应版本的WinSock.dll.
		exit(0);
	}
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	//socket描述符,protocol为tcp.
	//UDP socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (serverSocket == INVALID_SOCKET)
	{
		//判断Socket状态.
		exit(0);
	}


}


void Server::Receive(const SOCKET& client) {
	char msg[1024];
	memset(msg, 0, sizeof(msg));
	/*如何判断接收是否完成*/
	recv(client, msg, sizeof(msg), 0);

	if (strlen(msg) > 0)
		std::cout << msg << std::endl;
}

void Server::Send(const SOCKET& client) {
	if (send(client, "hello,client", strlen("hello,client"), 0) == SOCKET_ERROR)
	{
		//发送失败
	}
}

void Server::Accept() {
	sockaddr_in client_Address;
	SOCKET client = accept(serverSocket, (sockaddr *)&client_Address, NULL);
	if (client == INVALID_SOCKET) 
	{
		//非法用户处理
	}
	else 
	{
		std::cout << "ip: " << inet_ntoa(client_Address.sin_addr) << "通过[" << ntohs(client_Address.sin_port) << "]连接上了服务器." << std::endl;
		Server::Receive(client);
		Server::Send(client);

		//Server::Accept();

	}


}



void Server::Start(unsigned int port) {
	/*serverAddr */
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.S_un.S_addr = INADDR_ANY;	/*监听所有IP*/

	/*绑定socket;*/
	if (bind(serverSocket, (sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		//绑定socket失败则释放资源退出
		closesocket(serverSocket);
		WSACleanup();
		exit(0);
	}

	if (listen(serverSocket, 1024) == SOCKET_ERROR)
	{
		//监听本地端口失败则释放资源退出
		closesocket(serverSocket);
		WSACleanup();
		exit(0);
	}

	std::cout << "服务器已开启,等待连接..."<< std::endl;

	Server::Accept();
}