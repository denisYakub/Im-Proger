#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "ws2_32.lib")

int main(int argc, char* argv[])
{
	SOCKET clientSock;
	sockaddr_in serverAddr;
	struct hostent* pHostEnt;
	char hostName[64];
	int addrLen = sizeof(serverAddr);
	int nbytes;
	char buff[256];
	char str[50];
	WORD versionRequested;
	WSADATA wsaData;
	WORD version = MAKEWORD(2, 2);

	if (WSAStartup(version, &wsaData))
	{
		printf("WSA service failed to initialize with error % d\n",WSAGetLastError());
			exit(1);
	};
	/*Создаем сокет*/
	clientSock = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSock < 0)
	{
		printf("Socket initialization failed \n");
		exit(1);
	};
	/* Определяем адрес хоста*/
	gethostname(hostName, 64);
	printf("Client is running on %s \n", hostName);
	// We are going to connect with Server!!!
	printf("We are going to connect with Server %s \n", hostName);
	pHostEnt = gethostbyname(hostName);
	if (pHostEnt == NULL)
	{
		printf("Can't get host by name.");
		exit(1);
	};
	/*Соединение с сервером*/
	memcpy(&serverAddr.sin_addr, pHostEnt->h_addr, 4);
	serverAddr.sin_port = htons(40842);
	serverAddr.sin_family = AF_INET;
	if (connect(clientSock, (sockaddr*)&serverAddr, addrLen) != 0)
	{
		printf("Connect error. \n");
		closesocket(clientSock);
		exit(1);
	}
	printf("Connected to server!\n");
	//
	sprintf_s(buff, strlen("Hi from client") + 1, "Hi from client");
	send(clientSock, buff, strlen(buff), 0);

	if ((nbytes = recv(clientSock, buff, sizeof(buff), 0)) > 0) {
		buff[nbytes + 1] = '\0';
		printf("Recive from client: %s\n", buff);
	}

	strcpy_s(str, "a");

	while (strcmp(str, "good buy"))
	{
		gets_s(str);
		printf("User input %s\n", str);
		sprintf_s(buff, strlen(str) + 1, str);
		send(clientSock, buff, strlen(buff), 0);
	}
	closesocket(clientSock);
	WSACleanup();
	return 0;
}