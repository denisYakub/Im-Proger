#include <string.h>
#include <windows.h>
#include <stdio.h>

char Name[50];
char str[200];

HANDLE hEvent;

int main(int argc, char* argv[])
{
	strcpy_s(Name, "child");
	if (argc != 2)
	{
		printf("Invalid parameter!\n");
		return 0;
	}

	hEvent = (HANDLE)atoi(argv[1]);
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
