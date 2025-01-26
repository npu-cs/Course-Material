//#include "stdafx.h"
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib,"ws2_32.lib")

#define BUFFER_SIZE 1024

void main()
{
	SOCKET sSocket;
	char recv_buf[BUFFER_SIZE],send_buf[BUFFER_SIZE];
	struct sockaddr_in seradd,cliadd;
	
	WSADATA wsadata;
	
	if(WSAStartup(MAKEWORD(2,2),&wsadata)!=0)
	{
		printf("failed to load winsocket\n");
		return;
	}
	sSocket=socket(AF_INET,SOCK_DGRAM,0);
	if(sSocket==INVALID_SOCKET)
	{
		printf("socket() failed:%d\n",WSAGetLastError());
		return;
	}
	
	seradd.sin_family=AF_INET;
	seradd.sin_port=htons(5050);
	seradd.sin_addr.s_addr=inet_addr("192.168.43.155");
	
	if(bind(sSocket,(LPSOCKADDR)&seradd,sizeof(seradd))==SOCKET_ERROR)
	{
		printf("地址绑定时出错:%d\n",WSAGetLastError());
		return;
	}
	int ilen=sizeof(cliadd);
	memset(recv_buf,0,sizeof(recv_buf));
	printf("server start to receive data:\n");
	while(1)
	{
		int irecv=recvfrom(sSocket,recv_buf,sizeof(recv_buf),0,(struct sockaddr*)&cliadd,&ilen);
		if(irecv==SOCKET_ERROR)
		{
			printf("接受出错%d\n",WSAGetLastError());
			return;
		}
		else if(irecv==0)
			break;
		else
		{
			printf("Server received from Client %s\n",recv_buf);
			printf("Client ip:[%s],client port:[%d]\n",inet_ntoa(cliadd.sin_addr),ntohs(cliadd.sin_port));
		}
		int isend=sendto(sSocket,recv_buf,sizeof(recv_buf),0,(struct sockaddr*)&cliadd,sizeof(cliadd));
	}
	closesocket(sSocket);
	WSACleanup();
}