#include"server.h"


int main(void) {
	Server socket_Server;
	socket_Server.Start(33333);

	return 0;
}