#include <winsock2.h>
#include <Ws2tcpip.h>
#include <iostream>
#include <windows.h>

#pragma comment(lib, "Ws2_32.lib")
#define DEFAULT_PORT "21722"

int client() 
{
    
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) 
    {
        std::cout << "WSAStartup failed. " << iResult;
        return 1; 
    }
    
    if (iResult != 0) 
    {
        WSACleanup();
        return 1;
    }
    SOCKET ConnectSocket = INVALID_SOCKET;
    ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ConnectSocket == INVALID_SOCKET) 
    {
        WSACleanup();
        return 1;
    }


    iResult = connect(ConnectSocket, &server, 18);
    
    
    if (iResult = SOCKET_ERROR) 
    {
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
    }
    else if (iResult == 0) 
    {
        "connection successful.";
    }

    if (ConnectSocket == INVALID_SOCKET) 
    {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }
}

