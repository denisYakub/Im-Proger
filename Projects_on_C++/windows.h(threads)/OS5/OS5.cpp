#include <windows.h>
#include <stdio.h>
#include <conio.h>
bool KEY[256];

int main(int argc, char* argv[])
{
	//Создаем и помещаем файл в хендлер
	HANDLE hfile = CreateFile(L"C:\\Users\\denis\\source\\repos\\OS\\OS5\\input.txt",
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL, OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	if (hfile == INVALID_HANDLE_VALUE)
	{
		printf("Cann't create file! %d\n", GetLastError());
		return(0);
	}

	//создаем или открываем именованный объект отображенного в памяти (проецируемого) файла для заданного файла.
	HANDLE hfilemap = CreateFileMapping(hfile,// фаил
		NULL,// безопасность по умолчанию
		PAGE_READWRITE,// доступ на чтение/запись
		0,// максимальный размер объекта (высокий DWORD)
		sizeof(hfile),// максимальный размер объекта (младшее DWORD)
		NULL// имя объекта отображения
	);

	if (hfilemap == NULL)
	{
		printf("Cann't create file mapping! %d\n", GetLastError());
		return 0;
	}

	DWORD dwfilesize = GetFileSize(hfile, NULL);// размер файла

	CloseHandle(hfile);

	//отображает представление проецируемого файла в адресное пространство вызывающего процесса.
	PVOID pvfile = MapViewOfFile(hfilemap,// дескриптор объекта
		FILE_MAP_ALL_ACCESS, // разрешение на чтение/запись
		0, 0, 0);

	if (pvfile == NULL)
	{
		printf("Could not map view of file (%d).\n",GetLastError());

		return 0;
	}

	CloseHandle(hfilemap);

	PSTR pchANSI = (PSTR)pvfile;
	for (int i = 0; i < dwfilesize; i++)
	{
		printf("ch=%c\n", pchANSI[i]);
		pchANSI[i] = 'l';
	}

	printf("Would u like to write smth in to file? press: y\n");
	char ch = _getch();
	if (ch == 'y')
	{
		CopyMemory((PVOID)pvfile, "Message from first process.", sizeof("Message from first process."));
	}else{
			UnmapViewOfFile(pvfile);
			return(1);
		}

	return(1);
}
