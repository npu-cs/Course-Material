#include <winsock2.h>
#include <stdio.h>
#define BUFFER_SIZE 512

int main()
{
    WSADATA wsadata;
    SOCKET sClient;
    const char *Serip = "192.168.43.174";
    int SeriPort = 5050;

    char send_buf[BUFFER_SIZE];
    struct sockaddr_in seraddr;
    memset(send_buf, 0, BUFFER_SIZE);
    if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
    {
        printf("failed to load winsock\n");
        return -1;
    }

    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(SeriPort);
    seraddr.sin_addr.s_addr = inet_addr(Serip);
    sClient = socket(AF_INET, SOCK_STREAM, 0);
    if (sClient == INVALID_SOCKET)
    {
        printf("create socket failed: %d\n", WSAGetLastError());
        return -1;
    }
    printf("OK");
    if (connect(sClient, (struct sockaddr *)&seraddr, sizeof(seraddr)) ==
        INVALID_SOCKET)
    {
        printf("connect failed: %d", WSAGetLastError());
        return -1;
    }
    printf("start send data to server:\n");
    while (1)
    {
        scanf("%s", send_buf);
        int isnd = send(sClient, send_buf, sizeof(send_buf), 0);
        if (isnd == 0)
            break;
        else if (isnd == SOCKET_ERROR)
        {
            printf("send data error:%d", WSAGetLastError());
            return -1;
        }
    }
    closesocket(sClient);
    WSACleanup();
    return 0;
}