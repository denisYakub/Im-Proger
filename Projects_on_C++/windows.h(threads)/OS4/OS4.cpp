#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>

#define PAGELIMIT 80// число страниц

LPTSTR lpNxtPage;// адрес след страницы
DWORD dwPages = 0;             
DWORD dwPageSize;// размер страницы на моеё компе

INT PageFaultExceptionFilter(DWORD dwCode)
{
  LPVOID lpvResult;

  //ИСКЛЮЧЕНИЕ НАРУШЕНИЕ ДОСТУПА
  if (dwCode != EXCEPTION_ACCESS_VIOLATION)
  {
    _tprintf(TEXT("Exception code = %d.\n"), dwCode);
    return EXCEPTION_EXECUTE_HANDLER;
  }

  _tprintf(TEXT("Exception is a page fault.\n"));

  // число стрнц =< созд. стрнц.
  if (dwPages >= PAGELIMIT)
  {
    _tprintf(TEXT("Exception: out of pages.\n"));
    return EXCEPTION_EXECUTE_HANDLER;
  }

  // Создаем след стрнц
  lpvResult = VirtualAlloc(
    (LPVOID)lpNxtPage,
    dwPageSize,        
    MEM_COMMIT,         
    PAGE_READWRITE);
  if (lpvResult == NULL)
  {
    _tprintf(TEXT("VirtualAlloc failed.\n"));
    return EXCEPTION_EXECUTE_HANDLER;
  }
  else
  {
    _tprintf(TEXT("Allocating another page.\n"));
  }

  // Увеличьте количество страниц и переместите lpNxtPage на следующую страницу.

  dwPages++;
  lpNxtPage = (LPTSTR)((PCHAR)lpNxtPage + dwPageSize);

  // Продолжить выполнение там, где произошла ошибка страницы.

  return EXCEPTION_CONTINUE_EXECUTION;
}

VOID _tmain(VOID)
{
  LPVOID Base;// Базовый адрес тестовой памяти и общий указатель сим
  BOOL Success;                
  DWORD i;
  SYSTEM_INFO sSysInfo;// о моей системе инф

  GetSystemInfo(&sSysInfo);

  _tprintf(TEXT("This computer has page size %d.\n"), sSysInfo.dwPageSize);

  dwPageSize = sSysInfo.dwPageSize;

  // Резервируем страницы в виртуальном адресном пространстве процесса.
  Base = VirtualAlloc(
    NULL,// адрес которую выбирает память для резервации
    PAGELIMIT * dwPageSize, // размер аллокатора
    MEM_RESERVE,
    PAGE_READWRITE);

  if (Base == NULL)
    _tprintf(TEXT("VirtualAlloc reserve failed."));

  Base = VirtualAlloc(Base, PAGELIMIT * dwPageSize, MEM_COMMIT, PAGE_READWRITE);//фиксируем память

  char* char_ptr = static_cast<char*>(Base);

  for (i = 0; i < PAGELIMIT * dwPageSize + 1; i++)
  {
    __try
    {
      // записываем в память
      char_ptr[i] = 'a';
    }
    // если ошибка записы вызываем функцию для обработки
    __except (PageFaultExceptionFilter(GetExceptionCode()))
    {
      _tprintf(TEXT("Exiting process.\n"));
      ExitProcess(GetLastError());
    }
  }

  // Освобождение памяти после использования
  Success = VirtualFree(
    Base,
    0,
    MEM_RELEASE);

  _tprintf(TEXT("Release %s.\n"), Success ? TEXT("succeeded") : TEXT("failed"));

}