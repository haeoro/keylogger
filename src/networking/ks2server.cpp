#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

const char *HOST = nullptr;
u_short PORT = 0;

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

SOCKET initClient()
{
    WSADATA wsaData;
    static struct sockaddr_in saServer;
    hostent *host = nullptr;
    const char *ip = nullptr;

    if (HOST == nullptr || PORT == 0)
    {
        return 1;
    }

    int wsaStartRetCode = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (wsaStartRetCode != 0)
    {
        WSACleanup();
        return 1;
    }

    if (isHostInDotForm(HOST))
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

    connect(socketInfo, (SOCKADDR*)&saServer, sizeof(saServer));

    if (WSAGetLastError() == 0)
    {
        return socketInfo;
    }
    else
    {
        closesocket(socketInfo);
        WSACleanup();
        return 1;
    }
}
