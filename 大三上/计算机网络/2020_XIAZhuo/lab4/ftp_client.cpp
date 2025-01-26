#include <conio.h>
#include <stdio.h>
#include <winsock2.h>
#include <iostream>
#include <string.h>
#include <iostream>
using namespace std;
#pragma comment(lib, "ws2_32")

#define MAX_SIZE 4096
char CmdBuf[MAX_SIZE];
char command[MAX_SIZE];
char ReplyMsg[MAX_SIZE];
int nReplyCode;
bool bConnected = false;
SOCKET SocketControl;
SOCKET SocketData;

int nRecv;

//接收 FTP 服务器应答
bool RecvReply()
{
    //通过控制连接接受应答信息
    int nRev = 0;
    memset(ReplyMsg, 0, MAX_SIZE);
    nRecv = recv(SocketControl, ReplyMsg, MAX_SIZE, 0);
    if (nRecv == SOCKET_ERROR)
    {
        cout << "socket recv failed!" << endl;
        closesocket(SocketControl);
        return false;
    }
    //获取应答码及应答信息
    if (nRecv > 4)
    {
        char *ReplyCodes = new char[3];
        memset(ReplyCodes, 0, 3);
        memcpy(ReplyCodes, ReplyMsg, 3);
        nReplyCode = atoi(ReplyCodes);
    }
    return true;
}

//向 FTP 服务器发送命令
bool SendCommand()
{
    //通过控制连接发送命令
    int nSend;
    nSend = send(SocketControl, command, strlen(command), 0);
    if (nSend == SOCKET_ERROR)
    {
        printf("SocketControl create error:%d\n", WSAGetLastError());
        return false;
    }
    return true;
}

//建立数据连接
bool DataConnect(char *ServerIpAddr)
{
    //向 FTP 服务器发送 PASV 命令
    memset(command, 0, MAX_SIZE);
    memcpy(command, "PASV", strlen("PASV"));
    memcpy(command + strlen("PASV"), "\r\n", 2);
    if (!SendCommand())
    {
        return false;
    }
    //获得 PASV 命令的应答消息
    if (RecvReply())
    {
        if (nReplyCode != 227)
        {
            printf("PASV 命令应答错误！");
            closesocket(SocketControl);
            return false;
        }
    }
    //解析 PASV 命令和应答消息
    char *part[6];
    if (strtok(ReplyMsg, "("))
    {
        for (int i = 0; i < 5; i++)
        {
            part[i] = strtok(NULL, ",");
            if (!part[i])
            {
                return false;
            }
        }
        part[5] = strtok(NULL, ")");
        if (!part[5])
            return false;
    }
    else
        return false;
    //获得 FTP 服务器的数据端口号
    unsigned short serverPort;
    serverPort = (unsigned short)((atoi(part[4]) << 8) + atoi(part[5]));
    //创建数据 SOCKET
    printf("server data Port:%d\n", serverPort);
    SocketData = socket(AF_INET, SOCK_STREAM, 0);
    if (SocketData == INVALID_SOCKET)
    {
        printf("data socket creat error: %d", WSAGetLastError());
        return false;
    }
    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(serverPort);
    server_addr.sin_addr.s_addr = inet_addr(ServerIpAddr);
    //与 FTP 服务器发送建立数据 TCP 连接请求
    int nConnect = connect(SocketData, (sockaddr *)&server_addr, sizeof(server_addr));
    if (nConnect == SOCKET_ERROR)
    {
        printf("create data TCP connection error : %d\n", WSAGetLastError());
        return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    //检查命令行参数
    if (argc != 2)
    {
        printf("please input param as the following: ftpclient ftpIPaddr\n");
        return -1;
    }
    WSADATA WSAData;
    if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0)
    {
        printf("WSAStartup error !\r\n");
        return -1;
    }
    //创建控制连接 socket
    SocketControl = socket(AF_INET, SOCK_STREAM, 0);
    if (SocketControl == INVALID_SOCKET)
    {
        printf("creat TCP Control socket error !");
        return -1;
    }
    //定义 FTP 服务器控制连接地址和端口号
    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(21);
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    //向 FTP 服务器发送控制连接请求
    printf("FTP control connect......");
    int nConnect = connect(SocketControl, (sockaddr *)&server_addr, sizeof(server_addr));
    if (nConnect == SOCKET_ERROR)
    {
        printf("client could not establish the FTP control connection with server\n");
        return -1;
    }
    //获取控制连接上的应答消息
    if (RecvReply())
    {
        if (nReplyCode == 220) //判断应答 Code
            printf("%s \n", ReplyMsg);
        else
        {
            printf("the reply msg is error\n");
            closesocket(SocketControl);
            return -1;
        }
    }
    //向服务器发送 USER 命令
    printf("FTP->USER:");
    memset(CmdBuf, 0, MAX_SIZE);
    gets(CmdBuf); //输入用户名并保存
    memset(command, 0, MAX_SIZE);
    memcpy(command, "USER ", strlen("USER "));
    memcpy(command + strlen("USER "), CmdBuf, strlen(CmdBuf));
    memcpy(command + strlen("USER ") + strlen(CmdBuf), "\r\n", 2);
    if (!SendCommand())
        return -1;
    //获得 USER 命令的应答信息
    if (RecvReply())
    {
        if (nReplyCode == 230 || nReplyCode == 331)
            printf("%s", ReplyMsg);
        else
        {
            printf("USER 命令应答错误\n");
            closesocket(SocketControl);
            return -1;
        }
    }
    printf("%d", nReplyCode);
    if (nReplyCode == 331)
    {
        //向 FTP 服务器发送 PASS 命令
        printf(" FTP > PASS:");
        memset(CmdBuf, 0, MAX_SIZE);
        for (int i = 0; i < MAX_SIZE; i++)
        {
            CmdBuf[i] = getch(); //输入用户密码
            if (CmdBuf[i] == '\r')
            {
                CmdBuf[i] = '\0';
                break;
            }
            else
                printf("*");
        }
        printf("\n");
        memset(command, 0, MAX_SIZE);
        memcpy(command, "PASS ", strlen("PASS "));
        memcpy(command + strlen("PASS "), CmdBuf, strlen(CmdBuf));
        memcpy(command + strlen("PASS ") + strlen(CmdBuf), "\r\n", 2);
        if (!SendCommand())
            return -1;
        //获得 PASV 命令的应答信息
        if (RecvReply())
        {
            if (nReplyCode == 230)
                printf("%s", ReplyMsg);
            else
            {
                printf("PASS 命令应答错误\n");
                closesocket(SocketControl);
                return -1;
            }
        }
    }
    //向 FTP 服务器发送 LIST 命令
    printf("ftp>LIST\r\n");
    char ftpserver[MAX_SIZE];
    memset(ftpserver, 0, MAX_SIZE);
    memcpy(ftpserver, argv[1], strlen(argv[1]));
    if (!DataConnect(ftpserver))
        return -1;
    memset(command, 0, MAX_SIZE);
    memcpy(command, "LIST", strlen("LIST"));
    memcpy(command + strlen("LIST"), "\r\n", 2);
    if (!SendCommand())
        return -1;
    //获得 LIST 命令的应答信息
    if (RecvReply())
    {
        if (nReplyCode == 125 || nReplyCode == 150 || nReplyCode == 226)
            cout << ReplyMsg;
        else
        {
            printf("LIST 命令应答错误 ! \r\n");
            closesocket(SocketControl);
            return -1;
        }
    }
    //获取 LIST 命令的目录信息
    char ListBuffer[MAX_SIZE];
    while (true)
    {
        memset(ListBuffer, 0, MAX_SIZE);
        nRecv = recv(SocketData, ListBuffer, MAX_SIZE, 0);
        if (nRecv == SOCKET_ERROR)
        {
            printf("数据接收错误 !\r\n");
            closesocket(SocketData);
            return -1;
        }
        if (nRecv <= 0)
            break;
        cout << ListBuffer;
    }
    closesocket(SocketData);
    //获取 LIST 命令的应答信息
    if (RecvReply())
    {
        if (nReplyCode == 226)
            cout << ReplyMsg;
        else
        {
            printf("LIST 命令应答错误 !\r\n");
            closesocket(SocketControl);
            return -1;
        }
    }
    //向 FTP 服务器发送 quit 命令
    printf("FTP->QUIT:");
    memset(command, 0, MAX_SIZE);
    memcpy(command, "QUIT", strlen("QUIT"));
    memcpy(command + strlen("QUIT"), "\r\n", 2);
    if (!SendCommand())
        return -1;
    //获得 quit 命令的应答信息
    if (RecvReply())
    {
        if (nReplyCode == 221)
        {
            printf("%s", ReplyMsg);
            bConnected = false;
            closesocket(SocketControl);
            return -1;
        }
        else
        {
            printf("QUIT 命令应答错误\r\n");
            closesocket(SocketControl);
            return -1;
        }
        WSACleanup();
    }
    return 0;
}