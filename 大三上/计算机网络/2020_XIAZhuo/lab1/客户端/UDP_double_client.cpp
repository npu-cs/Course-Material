#include <winsock2.h>
#include <stdio.h>
#include <iostream>
using namespace std;

#define BUFFER_SIZE 1024

int main()
{
    const char *serip = "192.168.26.31";
    int Seriport = 6666;

    char send_buf[BUFFER_SIZE], recv_buf[BUFFER_SIZE];
    memset(send_buf, 0, sizeof(send_buf));

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
    sclient = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (sclient == INVALID_SOCKET)
    {
        printf("build socket failed!\n");
        return -1;
    }
    // cout << (struct sockaddr *)&seradd << endl;
    printf("Client start to send data:\n");
    int ilen = sizeof(seradd);
    while (1)
    {
        scanf("%s", send_buf);
        int isend = sendto(sclient, send_buf, sizeof(send_buf), 0,
                           (struct sockaddr *)&seradd, sizeof(seradd));
        memset(recv_buf, 0, sizeof(recv_buf));
        int irecv = recvfrom(sclient, recv_buf, sizeof(recv_buf), 0,
                             (struct sockaddr *)&seradd, &ilen);
        printf("client receive data from server:%s\n", recv_buf);
        printf("server ip:[%s],port:[%d]\n", inet_ntoa(seradd.sin_addr), ntohs(seradd.sin_port));
    }
    closesocket(sclient);
    WSACleanup();
    return 0;
}