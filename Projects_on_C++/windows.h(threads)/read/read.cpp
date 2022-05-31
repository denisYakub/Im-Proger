#include <stdio.h>
#include <windows.h>

#define BUFSIZE 50


int main(int argc, char* argv[])
{

	char chBuf[BUFSIZE];

	DWORD dwRead, dwWritten;

	HANDLE hStdin, hOutputFile;

	printf("Hello! I am reader\n");

	hStdin = GetStdHandle(STD_INPUT_HANDLE);

	if ((hStdin == INVALID_HANDLE_VALUE))
		ExitProcess(1);

	hOutputFile = CreateFile(L"C:\\Users\\denis\\source\\repos\\OS\\read\\out.txt", GENERIC_WRITE, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	for (;;)
	{
		for (int i = 0; i < 50; i++) chBuf[i] = '\0';

		if (!ReadFile(hStdin, chBuf, BUFSIZE, &dwRead, NULL))
		{
			printf("Can'not read\n");
			break;
		}


		printf("In buffer %s\n", chBuf);

		Sleep(1000);

		if (!WriteFile(hOutputFile, chBuf, dwRead, &dwWritten, NULL))
		{
			printf("Can'not Write %d\n", GetLastError());
			break;
		}

	}

}