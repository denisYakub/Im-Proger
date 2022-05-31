#include <windows.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <atlstr.h>
using namespace std;


void L1P1(string file) {

	LPCWSTR lpCommandLine[3];//длинный указатель на постоянную строку
	CString comand[3];

	STARTUPINFO startInfo;// STARTUPINFO (указатель)
	PROCESS_INFORMATION processInfo;// PROCESS_INFORMATION (указатель)

	HANDLE hand[3];//Дескриптор
	WCHAR proc_name[36];

	char str[100];
	int j = 0;
	ifstream fl(file);

	ZeroMemory(&startInfo, sizeof(STARTUPINFO));//Чтобы избежать нежелательных эффектов оптимизации компиляторов
	startInfo.cb = sizeof(startInfo);

	if (fl.is_open()) {
		while (fl.getline(str, 100)) {
			comand[j] = str;
			lpCommandLine[j] = comand[j];
			j++;
		}
		fl.close();

		for (int i = 0; i < 3; i++)
		{
			wcscpy_s(proc_name, wcslen(lpCommandLine[i]) + 1, lpCommandLine[i]);//Копирует строку.
			printf("!!!%ls %d\n", lpCommandLine[i], wcslen(lpCommandLine[i]));

			if (!CreateProcess(NULL, // имя исполняемого модуля (указатель)
				proc_name, // командная строка (указатель)
				NULL, // атрибуты безопасности процесса (указатель)
				NULL, // атрибуты безопасности потока (указатель)
				FALSE,// флаг наследования описателя
				HIGH_PRIORITY_CLASS | CREATE_NEW_CONSOLE, // флаги создания
				NULL, // новый блок окружения (указатель)
				NULL,// имя текущей директории (указатель)
				&startInfo,// STARTUPINFO (указатель)
				&processInfo // PROCESS_INFORMATION (указатель)
			))
			{
				fprintf(stderr, "CreateProcess failed on error %d\n", GetLastError());
				ExitProcess(1);
			} 
			hand[i] = processInfo.hProcess;
		}

		printf("ProcessHandle=%d\n", (int)processInfo.hProcess);
		printf("ThreadHandle=%d\n", (int)processInfo.hThread);

		CloseHandle(processInfo.hProcess);//Закрывает дескриптор открытого объекта.
		CloseHandle(processInfo.hThread);
	}
	else {
		cout << "Can not open the file.txt\n";
		fprintf(stderr, "CreateProcess failed on error %d\n", GetLastError());
		ExitProcess(2);
	}
}

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	int param;
	param = *(int*)lpParameter;
	printf("Thread %d created\n", param);
	while (TRUE)
	{
		printf("I'm thread %d and I'm working!\n", param);
		Sleep(100);
	}
}

void L1P2() {
	HANDLE mHandle[2];
	DWORD mArg[2], mId[2];
	int i;
	printf("Thread main created\n");
	for (i = 0; i < 2; i++)
	{
		mArg[i] = i;
		mHandle[i] = CreateThread(NULL, // атрибуты безопасности потока (указатель)
			0, // начальный размер стека потока в байтах
			ThreadProc, // функция потока (указатель)
			mArg + i, // аргумент для нового потока
			0, // флаги создания
			mId + i // возвращаемый идентификатор потока (указатель)
		);
		
	}
	Sleep(1000);
	
	while (TRUE)
	{
		printf("I am main and I'm working!\n");
		Sleep(100);
	}
}
int main(int agrc, char* argv[]) {
	//L1P1(argv[1]);
	L1P2();
	return 0;
}