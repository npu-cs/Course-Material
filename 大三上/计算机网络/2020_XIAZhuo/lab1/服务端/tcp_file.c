#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib,"ws2_32.lib")

int main()
{
	SOCKET oldSocket,newSocket;
	struct sockaddr_in seraddr,cliaddr;
	WSADATA wsaData;
	
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
	{
		printf("failed to load winsock\n");
		return -1;
	}
	oldSocket=socket(AF_INET,SOCK_STREAM,0);
	if(oldSocket==INVALID_SOCKET)
	{
		printf("create socket failed:%d\n",WSAGetLastError());
		return -1;
	}
	
	printf("server start to receive data\n");
	
	seraddr.sin_family=AF_INET;
	seraddr.sin_port=htons(8080);
	seraddr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	if(bind(oldSocket,(LPSOCKADDR)&seraddr,sizeof(seraddr))==SOCKET_ERROR)
	{
		printf("bind() failed:%d\n",WSAGetLastError());
		return -1;	
	}
	
	if(listen(oldSocket,5)==SOCKET_ERROR)
	{
		printf("listen() failed: %d\n",WSAGetLastError());
		return -1;
	}
	int iLen=sizeof(cliaddr);
	newSocket=accept(oldSocket,(struct sockaddr*)&cliaddr,&iLen);
	if(newSocket==INVALID_SOCKET)
	{
		printf("accept() failed:%d\n",WSAGetLastError());
		return -1;
		
	}
	
	FILE *ptrfile=fopen("video2.avi","wb");
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
		int ircv=recv(newSocket,data_buffer,512,0);
		int iwrite=fwrite(data_buffer,1,ircv,ptrfile);
		if(strcmp(data_buffer,"quit")==0)
			break;
	}
	printf("server recieve data end successsfully\n");
	fclose(ptrfile);
	closesocket(newSocket);
	closesocket(oldSocket);
	WSACleanup();
	return 0;
}
	
	
	
	