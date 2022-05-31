#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <iostream>
#include <vector>

HANDLE hNextThreadEvent;
HANDLE hInputThreadEvent;
HANDLE hOutputThreadEvent;

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{

	BOOL bExit = FALSE;
	char str[50];
	int num;
	DWORD dw;

	num = *((int*)lpParameter);

	printf("Thread %d begins\n", num);

	while (!bExit)
	{
		dw = WaitForSingleObject(hNextThreadEvent, INFINITE);
		switch (dw)
		{
		case WAIT_OBJECT_0: printf("Thread %d catch Event\n", num); break;// процесс h[x] получает контроль
		case WAIT_FAILED: printf("Wait failed\n"); break;// неправильный вызов
		}

		printf("Thread %d in while\n", num);

		gets_s(str, 50);
		printf("User input %s\n", str);

		while ((strcmp(str, "next")) && (strcmp(str, "exit")))
		{
			gets_s(str, 50);
			printf("User input %s\n", str);
		}

		if (!strcmp(str, "exit")) bExit = TRUE;

		printf("Thread %d release control\n", num);

		SetEvent(hNextThreadEvent);

	}

	printf("Thread %d finished\n", num);

	return 0;
}
void A() {
	HANDLE hThreads[2];
	int thargs[2];

	printf("I am main! Hello!\n");

	hNextThreadEvent = CreateEvent(NULL,
		FALSE,// сообщает системе, какого типа TRUE – со сбросом вручную; FALSE – с авто сбросом.
		FALSE,// начальное состояние события TRUE – свободное; FALSE – занятое.
		NULL);
	
	for (int i = 0; i < 2; i++)
	{
		thargs[i] = i;
		hThreads[i] = CreateThread(NULL, 0, ThreadProc, thargs + i, 0, NULL);

	}
	Sleep(100);

	SetEvent(hNextThreadEvent);

	WaitForMultipleObjects(2,// количество объектов ядра
		hThreads,// указатель на массив описателей объектов ядра
		TRUE,// приостанавливает поток и заставляет его ждать освобождения либо всех заданных объектов ядра, либо одного из них
				// (TRUE, то функция не даст потоку возобновить работу пока не освободятся все объекты)
		INFINITE);// сколько времени(в миллисекундах) поток готов ждать освобождения объекта

	CloseHandle(hNextThreadEvent);
	CloseHandle(hThreads[0]);
	CloseHandle(hThreads[1]);
}

struct BUFF {
	std::vector<int> mass;
	int size = 10;
};

DWORD WINAPI Producer(LPVOID lpParameter)
{
	BUFF* params = reinterpret_cast<BUFF*>(lpParameter);

	//params->mass.push_back(4);

	/*for (size_t i = params->mass.size(); i < params->size; i++)
	{
		params->mass.push_back(i);
	}*/

	DWORD dw;
	char str[50];
	bool bExit = FALSE;
	while (!bExit)
	{
		dw = WaitForSingleObject(hInputThreadEvent, INFINITE);
		switch (dw)
		{
		case WAIT_OBJECT_0: printf("Thread Producer catch Event\n"); break;// завершился процесс h[0]
		case WAIT_FAILED: printf("Wait failed\n"); break;// неправильный вызов
		}

		printf("Array size befor input = %d\n", params->mass.size());

		if (params->mass.size() != params->size)
		{
			for (size_t i = params->mass.size(); i < params->size; i++)
			{
				params->mass.push_back(i);
				printf("%d\n", params->mass[i]);
			}
			printf("Array size after input = %d\n", params->mass.size());
		}
		else {
			printf("Array is full\n");
		}

		printf("Thread in Producer\n");

		/*gets_s(str, 50);

		while (strcmp(str, "next"))
		{
			gets_s(str, 50);
		}*/
		Sleep(5000);
		printf("Thread Producer release control\n");

		//params->mass.clear();

		SetEvent(hOutputThreadEvent);
	}
	delete params;
	return 0;
}

DWORD WINAPI Comsumer(LPVOID lpParameter)
{
	BUFF* params = reinterpret_cast<BUFF*>(lpParameter);
	DWORD dw;
	char str[50];
	bool bExit = FALSE;
	params->mass;
	while (!bExit)
	{
		dw = WaitForSingleObject(hOutputThreadEvent, INFINITE);
		switch (dw)
		{
		case WAIT_OBJECT_0: printf("Thread Comsumer catch Event\n"); break;// завершился процесс h[0]
		case WAIT_FAILED: printf("Wait failed\n"); break;// неправильный вызов
		}
		printf("Thread in Comsumer\n");
		printf("Array size before output = %d\n", params->mass.size());
		
		if (params->mass.size() == 0)
		{
			printf("Array is empty\n");
		}
		else {
			int i = params->mass.size();
			while (params->mass.size() != 0)
			{
				printf("%d\n", params->mass[i - 1]);
				params->mass.pop_back();
				i--;
			}
			printf("Array size after output = %d\n", params->mass.size());
		}

		/*gets_s(str, 50);

		while (strcmp(str, "next"))
		{
			gets_s(str, 50);
		}*/
		Sleep(5000);
		printf("Thread Comsumer release control\n");

		SetEvent(hInputThreadEvent);
	}
	delete params;
	return 0;
}

void B() {
	HANDLE hThreads[2];
	BUFF* param = new BUFF();

	hInputThreadEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	hOutputThreadEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	hThreads[0] = CreateThread(NULL, 0, Producer, param, 0, NULL);
	hThreads[1] = CreateThread(NULL, 0, Comsumer, param, 0, NULL);

	Sleep(100);

	SetEvent(hInputThreadEvent);

	WaitForMultipleObjects(2,// количество объектов ядра
		hThreads,// указатель на массив описателей объектов ядра
		TRUE,// приостанавливает поток и заставляет его ждать освобождения либо всех заданных объектов ядра, либо одного из них
				// (TRUE, то функция не даст потоку возобновить работу пока не освободятся все объекты)
		INFINITE);// сколько времени(в миллисекундах) поток готов ждать освобождения объекта

	CloseHandle(hInputThreadEvent);
	CloseHandle(hOutputThreadEvent);
	CloseHandle(hThreads[0]);
	CloseHandle(hThreads[1]);
}

int main(int argc, char* argv[])
{
	//A();
	B();
}
