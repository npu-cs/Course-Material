// g++ UDP_single_client.c - lwsock32
#include <winsock2.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>

int main()
{
    const char *serip = "192.168.26.31";
    int Seriport = 6666;
    WSADATA wsadata;
    if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
    {
        printf("failed to load winsock\n");
        return -1;
    }

    struct sockaddr_in seradd;
    seradd.sin_family = AF_INET;
    seradd.sin_port = htons(Seriport);
    seradd.sin_addr.s_addr = inet_addr(serip);

    SOCKET sclient;
    sclient = socket(AF_INET, SOCK_DGRAM, 0);
    if (sclient == INVALID_SOCKET)
    {
        printf("build socket failed!\n");
        return -1;
    }
    FILE *fileptr = NULL;
    fileptr = fopen("video.avi", "rb");
    if (fileptr == NULL)
    {
        printf("file can not open!\n");
        return -1;
    }
    printf("client start to send file!\n");
    char data_buffer[512];
    memset(data_buffer, 0, 512);
    bool flag = true;
    while (1)
    {
        if (!feof(fileptr))
        {
            int iread = fread(data_buffer, 1, 512, fileptr);
            int isend = sendto(sclient, data_buffer, iread, 0,
                               (struct sockaddr *)&seradd, sizeof(seradd));
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
    sendto(sclient, str, sizeof(str), 0, (struct sockaddr *)&seradd, sizeof(seradd));
    fclose(fileptr);
    closesocket(sclient);
    WSACleanup();
    return 0;
}