#include <winsock.h>
#include <windows.h>
#include <stdio.h>
#pragma comment(lib, "wsock32.lib")

#define RECV_PROT 1000
#define SEND_PORT 2000

BOOL optReturn = TRUE;
SOCKET sock;
// SOCKETADDR_IN sockAddrFrom, sockAddrTo;
struct sockaddr_in sockAddrFrom, sockAddrTo;

DWORD CreatSoket()
{
    WSADATA WSAData;
    if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0)
    {
        printf("socket lib load error!");
        return FALSE;
    }
    //创建套接字
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
    {
        printf("create socket failed!\n");
        WSACleanup();
        return FALSE;
    }
    sockAddrFrom.sin_family = AF_INET;
    sockAddrFrom.sin_addr.s_addr = inet_addr("192.168.26.31");
    sockAddrFrom.sin_port = htons(SEND_PORT); //套接字上绑定IP地址和端口号
    if (bind(sock, (LPSOCKADDR)&sockAddrFrom, sizeof(sockAddrFrom)))
    {
        closesocket(sock);
        WSACleanup();
        return FALSE;
    }

    //套接字选项设置
    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *)&optReturn,
                   sizeof(optReturn) == SOCKET_ERROR))
    {
        closesocket(sock);
        WSACleanup();
        return FALSE;
    }
    return TRUE;
}

//发送广播报文
DWORD BroadDataSend(char lpBuffer[])
{
    int lengthSend = 0;
    sockAddrTo.sin_family = AF_INET;
    sockAddrTo.sin_addr.s_addr = INADDR_BROADCAST;
    sockAddrTo.sin_port = htons(RECV_PROT);
    lengthSend = sendto(sock, lpBuffer, strlen(lpBuffer), MSG_DONTROUTE,
                        (struct sockaddr *)&sockAddrTo, sizeof(sockaddr));
    if (lengthSend == SOCKET_ERROR)
    {
        //发送失败
        closesocket(sock);
        WSACleanup();
        return FALSE;
    }
    return TRUE;
}

int main()
{
    char buffer[100];
    int i;
    CreatSoket();
    printf("press any key to continue!\n");
    getchar();
    for (i = 0; i < 100; i++)
    {
        sprintf(buffer, "data %d", i);
        BroadDataSend(buffer);
        Sleep(50);
    }
    getchar();
    return TRUE;
}
