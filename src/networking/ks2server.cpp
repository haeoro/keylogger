#include <winsock2.h>
#include <Ws2tcpip.h>
#include <iostream>
#include <windows.h>

#define PORT 4444
#define HOST "192.168.1.100"

int client() 
{
    
    WSADATA wsaData;
    struct sockaddr_in serverInfo;
    serverInfo.sin_family = AF_INET;
    serverInfo.sin_addr.s_addr = inet_addr(HOST);
    serverInfo.sin_port = htons(PORT);

    int wsaStartRetCode = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsaStartRetCode != 0) 
    {
        std::cout << "WSAStartup failed. " << wsaStartRetCode;
        WSACleanup();
        return 1; 
    }

    SOCKET socketInfo = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    if (socketInfo == INVALID_SOCKET) 
    {
        WSACleanup();
        return 1;
    }

    connect(socketInfo, (SOCKADDR*)&serverInfo, 18);
    
    if (WSAGetLastError() == 0) 
    {
        std::cout << "Connection made to server!";
    }
    else if (WSAGetLastError() == 10061) 
    {
        std::cout << "Connection refused.";
    }
    WSACleanup();
}

