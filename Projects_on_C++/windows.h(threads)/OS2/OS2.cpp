#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <vector>
using namespace std;

#define _SECOND 10000000
LPCWSTR lpCommandLine[1] = { L"C:\\WINDOWS\\SYSTEM32\\NOTEPAD.EXE" };
STARTUPINFO startInfo;
PROCESS_INFORMATION processInfo;

int main(int agrc, char* argv[]) {
	if (agrc == 0) {
		printf("No input data\n");
		ExitProcess(-1);
	}

	int proccount = atoi(argv[1]);
	int sec = atoi(argv[2]);

	ZeroMemory(&startInfo, sizeof(STARTUPINFO));
	startInfo.cb = sizeof(startInfo);
	WCHAR proc_name[36];
	HANDLE hand[3];
	for (size_t i = 0; i < proccount; i++)
	{
		wcscpy_s(proc_name, wcslen(lpCommandLine[0]) + 1, lpCommandLine[0]);
		printf("!!!%ls\n", lpCommandLine[0]);
		if (!CreateProcess(NULL, proc_name, NULL, NULL, FALSE, HIGH_PRIORITY_CLASS | CREATE_NEW_CONSOLE, NULL, NULL,
			&startInfo,
			&processInfo))
		{
			fprintf(stderr, "CreateProcess failed on error %d\n", GetLastError());
			ExitProcess(1);
		}
		hand[i] = processInfo.hProcess;
	}
	HANDLE wTimer;
	__int64 endTime;
	LARGE_INTEGER quitTime;

	wTimer = CreateWaitableTimer(NULL, FALSE, NULL);
	endTime = -sec * _SECOND;

	quitTime.LowPart = (DWORD)(endTime & 0xFFFFFFFF);
	quitTime.HighPart = (LONG)(endTime >> 32);

	SetWaitableTimer(wTimer, &quitTime, 0, NULL, NULL, FALSE);
	WaitForSingleObject(wTimer, INFINITE);

	printf("WaitableTimer send a signal!\n");

	for (size_t i = 0; i < proccount; i++)
	{
		TerminateProcess(hand[i], 1);
	}
	
	return 0;
}
