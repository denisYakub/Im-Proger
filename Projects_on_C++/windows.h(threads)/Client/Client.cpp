#include <windows.h>
#include <iostream>
#include <string.h>

using namespace std;

int main()
{
  HANDLE hPipe;
  DWORD dwWritten;

  char str[50];

  hPipe = CreateFile(TEXT("\\\\.\\pipe\\Pipe"),
    GENERIC_READ | GENERIC_WRITE,
    0,
    NULL,
    OPEN_EXISTING,
    0,
    NULL);
  if (hPipe != 0) {
    printf("Client is working!\n");
  }else{
    printf("Client can not be launched!\n");
  }
  strcpy_s(str, "a");

  while (strcmp(str, "good buy"))
  {
    gets_s(str);
    printf("User input %s\n", str);
    if (hPipe != INVALID_HANDLE_VALUE)
    {
      WriteFile(hPipe,
        str,
        51,
        &dwWritten,
        NULL);
    }
    else {
      printf("No connection to the server!\n");
    }
  }
  printf("good buy!\n");
  CloseHandle(hPipe);
  return (0);
}