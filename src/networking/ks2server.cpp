#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

const char *HOST = "0.tcp.au.ngrok.io";
u_short PORT = 27189;

int isHostInDotForm(const char *test) 
{
    while (*test != '\0') 
    {
        if (*test >= 65 && *test <= 90 
        || *test >= 97 && *test <= 122) 
        {
            return 1;
        }
        test++;
    }
    return 0;
}

int client() 
{
    WSADATA wsaData;
    struct sockaddr_in saServer;
    hostent *host;
    const char *ip;

    int wsaStartRetCode = WSAStartup(MAKEWORD(2, 2), &wsaData);
    
    if (wsaStartRetCode != 0) 
    {
        std::cout << "WSAStartup failed. " << wsaStartRetCode;
        WSACleanup();
        return 1; 
    }

    if (isHostInDotForm(HOST) == 1) 
    {
        host = gethostbyname(HOST);
        ip = inet_ntoa (*(struct in_addr *)*host->h_addr_list);
        saServer.sin_addr.s_addr = inet_addr(ip);
    }
    else 
    {
        saServer.sin_addr.s_addr = inet_addr(HOST);
    }

    saServer.sin_family = AF_INET;
    saServer.sin_port = htons(PORT);

    SOCKET socketInfo = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    if (socketInfo == INVALID_SOCKET) 
    {
        closesocket(socketInfo);
        WSACleanup();
        return 1;
    }

    connect(socketInfo, (SOCKADDR*)&saServer, 18);
    
    if (WSAGetLastError() == 0) 
    {
        std::cout << "Connection made to server!";
        return 0;
    }
    else 
    {
        std::cout << "Connection refused.";
        return 1;
    }
    WSACleanup();
}