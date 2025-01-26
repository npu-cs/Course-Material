#include <winsock2.h>
#include <iostream>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "lwsock32")
#define BUFFER_SIZE 512

int main()
{
    WSADATA wsadata;
    SOCKET sClient;
    const char *Serip = "192.168.26.31";
    int SeriPort = 8080; // 有变化！

    struct sockaddr_in seraddr;
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
    FILE *fileptr = NULL;
    fileptr = fopen("video.avi", "rb");
    if (fileptr == NULL)
    {
        printf("file can not open!\n");
        return -1;
    }
    if (connect(sClient, (struct sockaddr *)&seraddr, sizeof(seraddr)) ==
        INVALID_SOCKET)
    {
        printf("connect failed: %d", WSAGetLastError());
        return -1;
    }
    printf("client start to send file!\n");
    char data_buffer[BUFFER_SIZE];
    memset(data_buffer, 0, BUFFER_SIZE);
    bool flag = true;
    while (1)
    {
        if (!feof(fileptr))
        {
            int iread = fread(data_buffer, 1, 512, fileptr);
            int isend = send(sClient, data_buffer, iread, 0);
            if (flag)
            {
                printf("start to sleep\n");
                Sleep(2000);
                printf("sleep end\n");
                flag = false;
            }
        }
        else
            break;
    }
    printf("file send end successfully!\n");
    char str[100] = "quit";
    send(sClient, str, sizeof(str), 0);
    fclose(fileptr);
    closesocket(sClient);
    WSACleanup();
    return 0;
}