
#include <iostream>
#include <winsdkver.h>
#include <SDKDDKVer.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "stdafx.h"
#include <stdlib.h>

int main()
{
    SOCKET serverSocket, acceptSocket;
    int PORT{ 55555 };

    /* Load up dll */
    WSADATA wsaData;
    int wsaerr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, &wsaData);
    if (wsaerr) {
        std::cout << "failed : dll file load : " << WSAGetLastError() << "\n";
        WSACleanup();
        return 0;
    }
    else {
        std::cout << "success : dll file load\n";
    }

    /* Create Socket */
    serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cout << "failed : socket create : " << WSAGetLastError() << "\n";
        closesocket(serverSocket);
        WSACleanup();
        return 0;
    }
    else {
        std::cout << "success : socket create\n";
    }

    /* Bind Socket */
    sockaddr_in service;
    service.sin_family = AF_INET;
    InetPton(AF_INET, L"127.0.0.1", &service.sin_addr.s_addr);
    service.sin_port = htons(PORT);
    if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        std::cout << "failed : socket bind : " << WSAGetLastError() << "\n";
        closesocket(serverSocket);
        WSACleanup();
        return 0;
    }
    else {
        std::cout << "success : socket bind\n";
    }

    /* Listen for clients */
    if (listen(serverSocket, 1) == SOCKET_ERROR) {
        std::cout << "failed : socket listen" << WSAGetLastError() << "\n";
        closesocket(serverSocket);
        WSACleanup();
        return 0;
    }
    else {
        std::cout << "success : socket listen\n";
    }

    /* Accept connection */
    acceptSocket = accept(serverSocket, NULL, NULL);
    if (acceptSocket == INVALID_SOCKET) {
        std::cout << "failed : socket accept : " << WSAGetLastError() << "\n";
        closesocket(serverSocket);
        closesocket(acceptSocket);
        WSACleanup();
    }
    else {
        std::cout << "success : socket accept\n";
    }
    return 0;
}
