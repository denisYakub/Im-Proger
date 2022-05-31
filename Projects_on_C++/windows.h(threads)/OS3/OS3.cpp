#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

#define BUFSIZE 50
#define BUFSIZE2 80

char chBuf[BUFSIZE];
char  chBuf2[BUFSIZE2];

WCHAR proc_name[50];

HANDLE hEvent, readPipe, writePipe;
SECURITY_ATTRIBUTES SecurityAttributes, pipeSA;
PROCESS_INFORMATION ProcessInf, scrProcessInfo, sinkProcessInfo;
STARTUPINFO StartInfo, scrStartInfo, sinkStartInfo;
SOCKET serverSock, newserverSock;

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	int nbytes;
	char buff[256];

	SOCKET newclient;
	newclient = ((SOCKET*)lpParameter)[0];

	if (newclient < 0)
	{
		printf("Accept failed with error %d \n", WSAGetLastError());
		exit(1);
	}
	else {
		printf("Client connected to server!\n");
		sprintf_s(buff, strlen("Hi from Server") + 1, "Hi from Server");
		send(newclient, buff, strlen(buff), 0);
	}
	while (true)
	{
		if ((nbytes = recv(newclient, buff, sizeof(buff), 0)) > 0) {
			buff[nbytes + 1] = '\0';
			printf("Recive from client: %s\n", buff);
			for (int i = 0; i < nbytes + 1; i++) buff[i] = '\0';
		}
	}

	closesocket(newclient);

	return 0;
}

wchar_t* convertCharArrayToLPCWSTR(const char* charArray)
{
	wchar_t* wString = new wchar_t[4096];

	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);

	return wString;
}

void PART1() {
	WCHAR str[50];
	
	wcscpy_s(proc_name, wcslen(L"CreateEvent prog") + 1, L"CreateEvent prog");

	hEvent = CreateEvent(NULL, FALSE, TRUE, L"CreateEvent event");

	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		printf("Event was opened\n");
	}
	else
	{
		printf("Event was created\n");
	}

	while (TRUE)
	{
		wcscpy_s(str, wcslen(L"a") + 1, L"a");

		WaitForSingleObject(hEvent, INFINITE);

		printf("Hello! My name is %ls\n", proc_name);

		while (wcscmp(str, L"good buy"))
		{
			if (!wcscmp(str, L"exit"))
			{
				SetEvent(hEvent);

				CloseHandle(hEvent);

				ExitProcess(0);
			}

			_getws_s(str, 10);
			printf("User input %ls\n", str);
		}

		printf("good buy!\n");
		SetEvent(hEvent);
	}
}

int PART2() {

	char Name[50];
	char path[200];
	char str[200];

	strcpy_s(Name, "Parent");
	strcpy_s(path, "C:\\Users\\denis\\source\\repos\\OS\\Debug\\child.exe ");

	//Чтоб создать наследуемый описатель:
	SecurityAttributes.bInheritHandle = TRUE;
	SecurityAttributes.lpSecurityDescriptor = NULL;
	SecurityAttributes.nLength = sizeof(SecurityAttributes);
	
	hEvent = CreateEvent(&SecurityAttributes, FALSE, TRUE, NULL);

	//Помещаем Handle Event в командную строку 
	_itoa_s((int)hEvent, str, 10);
	strcat_s(path, str);
	memset(&StartInfo, 0, sizeof(StartInfo));
	StartInfo.cb = sizeof(StartInfo);

	if (!CreateProcess(NULL, convertCharArrayToLPCWSTR(path), NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL,
		&StartInfo, &ProcessInf))
	{
		printf("Could not create child process!\n");
		CloseHandle(hEvent);
		return 0;
	}

	while (TRUE)
	{
		strcpy_s(str, "a");

		WaitForSingleObject(hEvent, INFINITE);

		printf("Hello! My name is %s\n", Name);

		while (strcmp(str, "good buy"))
		{
			if (!strcmp(str, "exit"))
			{

				SetEvent(hEvent);

				CloseHandle(hEvent);

				return 0;
			}

			gets_s(str);
			printf("User input %s\n", str);
		}
		printf("good buy!\n");
		SetEvent(hEvent);
	}

	return 0;
}

void PART3() {
	HANDLE hPipe;
	DWORD dwRead;

	char buffer[1024];

	hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\Pipe"),
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
		1,
		1024 * 16,
		1024 * 16,
		NMPWAIT_USE_DEFAULT_WAIT,
		NULL);

	while (hPipe != INVALID_HANDLE_VALUE)
	{
		printf("Server is currently working!\n");
		if (ConnectNamedPipe(hPipe, NULL) != FALSE)   // ждем кого-то для подключения
		{
			printf("Client is connected!\n");
			while (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &dwRead, NULL) != FALSE)
			{
				buffer[dwRead] = '\0';
				printf("%s\n", buffer);
			}
		}
		printf("Client disconnected!\n");
		DisconnectNamedPipe(hPipe);
	}
}

void PART4() {

	sockaddr_in serverAddr, clientAddr;
	WORD versionRequested;
	WSADATA wsaData;
	WORD version = MAKEWORD(2, 2);
	HANDLE hThreads[3];

	int addrLen = sizeof(serverAddr);
	struct hostent* pHostEnt;
	char hostName[64];

	if (WSAStartup(version, &wsaData))
	{
		printf("WSA service failed to initialize with error %d\n",WSAGetLastError());
			exit(1);
	};

	/*Создаем сокет*/
	serverSock = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSock < 0)
	{
		printf("Socket initialization failed with error %d\n",WSAGetLastError());
			exit(1);
	};

	gethostname(hostName, 64);
	pHostEnt = gethostbyname(hostName);

	if (pHostEnt == NULL)
	{
		printf("Can't get host by name.");
		exit(1);
	};
	printf("Server is running on %s \n", hostName);

	/*Связывание сокета*/
	memcpy(&serverAddr.sin_addr, pHostEnt->h_addr, 4);
	serverAddr.sin_port = htons(40842);
	serverAddr.sin_family = AF_INET;

	if (bind(serverSock, (sockaddr*)&serverAddr, addrLen) != 0)
	{
		printf("Bind failed with error %d \n", WSAGetLastError());
		closesocket(serverSock);
		exit(1);
	};

	/*Сервер слушает*/
	if (listen(serverSock, 3))
	{
		printf("Listen failed with error %d \n", WSAGetLastError());
		closesocket(serverSock);
		exit(1);
	}

	/*Установление соединения*/
	int i = 0;

	while (true)
	{
		while (((newserverSock = accept(serverSock, (sockaddr*)&clientAddr, &addrLen)) > 0) and i != 3)
		{
			if ((hThreads[i] = CreateThread(NULL, NULL, ThreadProc, &newserverSock, NULL, NULL)) != 0) {
				printf("Thread created!\n");
				i++;
			}
		}
		closesocket(newserverSock);
	}

	for (size_t j = i; j >= 0; j--)
	{
		CloseHandle(hThreads[j]);
	}
	WSACleanup();
}

int main(int argc, WCHAR* argv[])
{
	//PART1();
	//PART2();
	//PART3();
	PART4();
	return 0;
}
