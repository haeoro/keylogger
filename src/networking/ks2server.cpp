#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>


int client() 
{
    WSADATA wsaData;
    struct sockaddr_in saServer;
    hostent *host;
    const char *ip;
    
    // host and port info here.
    const char *HOST = "0.tcp.au.ngrok.io";
    u_short PORT = 17711;

    int wsaStartRetCode = WSAStartup(MAKEWORD(2, 2), &wsaData);
    
    if (wsaStartRetCode != 0) 
    {
        std::cout << "WSAStartup failed. " << wsaStartRetCode;
        WSACleanup();
        return 1; 
    }

    host = gethostbyname(HOST);
    ip = inet_ntoa (*(struct in_addr *)*host->h_addr_list);

    saServer.sin_family = AF_INET;
    saServer.sin_addr.s_addr = inet_addr(ip);
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