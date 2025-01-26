#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "ws2_32.lib")

int main()
{
	WSADATA wsaData;
	SOCKET oldSocket, newSocket;
	int iLen = 0;
	int iSend = 0;
	int ircv = 0;
	char recv_buffer[512];

	struct sockaddr_in seraddr, cliaddr;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("failed to load winsock\n");
		return -1;
	}
	oldSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (oldSocket == INVALID_SOCKET)
	{
		printf("create socket failed:%d", WSAGetLastError());
		return -1;
	}

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(5050);
	seraddr.sin_addr.s_addr = inet_addr("192.168.43.174");
	if (bind(oldSocket, (LPSOCKADDR)&seraddr, sizeof(seraddr)) == SOCKET_ERROR)
	{
		printf("bind() failed:%d\n", WSAGetLastError());
		return -1;
	}
	printf("server start to receive data:\n");

	if (listen(oldSocket, 5) == SOCKET_ERROR)
	{
		printf("listen() failed: %d\n", WSAGetLastError());
		return -1;
	}
	iLen = sizeof(cliaddr);
	newSocket = accept(oldSocket, (struct sockaddr *)&cliaddr, &iLen);
	if (newSocket == INVALID_SOCKET)
	{
		printf("accept() failed:%d\n", WSAGetLastError());
		return -1;
	}

	while (1)
	{
		memset(recv_buffer, 0, 512);
		ircv = recv(newSocket, recv_buffer, sizeof(recv_buffer), 0);
		if (ircv == SOCKET_ERROR)
		{
			printf("rcv() failed:%d\n", WSAGetLastError());
			break;
		}
		else if (ircv == 0)
			break;
		else
		{
			printf("server recieve data from client:%s\n", recv_buffer);
		}
	}
	closesocket(newSocket);
	closesocket(oldSocket);
	WSACleanup();
	return 0;
}