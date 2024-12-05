#include <iostream>
#include <winsock2.h>
#include <time.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

#define STATUS_FAILED 0xFFFF

unsigned long serverIPAddress;
long MaxThreadNum = 200;
long ThreadCount = 0;
long *lockTreadCount = &ThreadCount;

DWORD WINAPI ScanTcpPort(LPVOID lpParam)
{
    short TcpPort = *(short *)lpParam;
    InterlockedIncrement(lockTreadCount);
    SOCKET socketid = socket(AF_INET, SOCK_STREAM, 0);
    if (socketid == INVALID_SOCKET)
    {
        cout << "Create socketid error! " << endl;
        return 0;
    }
    else
    {
        sockaddr_in severAddr;
        severAddr.sin_family = AF_INET;
        severAddr.sin_port = htons(TcpPort);
        severAddr.sin_addr.S_un.S_addr = serverIPAddress;
        // clock_t start_time = clock();
        connect(socketid, (sockaddr *)&severAddr, sizeof(severAddr));
        // clock_t end_time = clock();
        // cout << "connect time: " << (double)(end_time - start_time) / CLOCKS_PER_SEC << "s" << endl;
        // fd_set结构体操作函数
        // 清空集合：FD_ZERO(fd_set *)
        // 加入集合：FD_SET(int, fd_set *)
        // 从集合删除：FD_CLR(int, fd_set *)
        // 是否可以读写FD_ISSET(int, fd_set *)
        struct fd_set write;
        FD_ZERO(&write);
        FD_SET(socketid, &write);
        struct timeval timeout;
        timeout.tv_sec = 0.3; // 设置超时时间为0.3秒
        timeout.tv_usec = 0;  // 微秒
        // 在timeout时间内若端口可写，则返回值>0
        if (select(0, NULL, &write, NULL, &timeout) > 0)
            cout << "TcpPort:" << TcpPort << endl;
        closesocket(socketid);
    }
    InterlockedDecrement(lockTreadCount);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Please input parameter:ScanTcpport server address" << endl;
        return -1;
    }
    WSADATA WSAData;
    if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0)
    {
        cout << "WSAStartup failed: " << GetLastError() << endl;
        ExitProcess(STATUS_FAILED);
    }
    serverIPAddress = inet_addr(argv[1]);
    cout << "Open TCP Ports: " << endl;
    clock_t start_time = clock();
    for (int i = 0; i < 1024; i++)
    {
        while (ThreadCount >= MaxThreadNum)
            Sleep(20);
        DWORD ThreadId;
        CreateThread(NULL, 0, ScanTcpPort, (LPVOID) new short(i), 0, &ThreadId);
    }
    while (ThreadCount > 0)
    {
        Sleep(100);
        WSACleanup();
    }
    clock_t end_time = clock();
    cout << "cost time: " << (double)(end_time - start_time) / CLOCKS_PER_SEC << "s" << endl;
    return 0;
}