//#include "stdafx.h"
#include <winsock2.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")

int main()
{
	SOCKET sSocket;
	struct sockaddr_in seradd,cliadd;
	WSADATA wsadata;
	
	if(WSAStartup(MAKEWORD(2,2),&wsadata)!=0)
	{
		printf("failed to load winsocket\n");
		return -1;
	}
	sSocket=socket(AF_INET,SOCK_DGRAM,0);
	if(sSocket==INVALID_SOCKET)
	{
		printf("socket() failed:%d\n",WSAGetLastError());
		return -1;
	}
	
	seradd.sin_family=AF_INET;
	seradd.sin_port=htons(5050);
	seradd.sin_addr.s_addr=inet_addr("192.168.43.155");
	
	if(bind(sSocket,(LPSOCKADDR)&seradd,sizeof(seradd))==SOCKET_ERROR)
	{
		printf("地址绑定时出错:%d\n",WSAGetLastError());
		return -1;
	}
	int ilen=sizeof(cliadd);
	
	FILE *ptrfile=fopen("video1.avi","wb");
	if(ptrfile==NULL)
	{
		printf("file can not open!\n");
		return -1;
	}
	char data_buffer[512];
	memset(data_buffer,0,512);
	printf("server start to recieve file\n");
	while(1)
	{
		int irecv=recvfrom(sSocket,data_buffer,512,0,(struct sockaddr*)&cliadd,&ilen);
		int iwrite=fwrite(data_buffer,1,irecv,ptrfile);
		if(strcmp(data_buffer,"quit")==0) break;
	}
	printf("server recieve data end successsfully\n");
	fclose(ptrfile);
	closesocket(sSocket);
	WSACleanup();
	return 0;
}
	
	
	
	