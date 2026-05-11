#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

const char *HOST = "0.tcp.au.ngrok.io";
u_short PORT = 13411;

int isHostInDotForm(const char *hostPtr) 
{
    while (*hostPtr != '\0') 
    {
        if (*hostPtr >= 65 && *hostPtr <= 90 
        || *hostPtr >= 97 && *hostPtr <= 122) 
        {
            return 1;
        }
        hostPtr++;
    }
    return 0;
}

int client(const char *buf) 
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
        send(socketInfo, buf, ((strlen(buf))+1), MSG_OOB);
        return 0;
    }
    else 
    {
        std::cout << "Connection refused.";
        return 1;
    }
    WSACleanup();
}