#include<iostream>
#include<stdlib.h>

//Extern
//������� �������� ���������� � ���������� ���������� ������ ���������.
int Myage;

//Static
//�������� static � ����������, ����������� ��� �����, �� ���������� � ��� ����������, �� ���� �����, ������� ����� ������������ ������ � �����, � ������� ��� ����������.
//������������� ��������� ����� static � ���������� ����������� �������� �� �������� ����������������� ����� � ��������������� �� �����������

void incrementAndPrint()
{
	static int s_value = 1; // ���������� s_value �������� �����������
	++s_value;
	std::cout << s_value << std::endl;
} // ���������� s_value �� ������������ �����, �� ���������� �����������

//int main()
//{
//	incrementAndPrint();
//	incrementAndPrint();
//	incrementAndPrint();
//}

//heap(����)
void calloc()
{
  int* array = (int*)calloc(10, sizeof(int));
  for (size_t i = 0; i < 10; i++)
  {
	  std::cin >> array[i];
  }
  for (size_t i = 0; i < 10; i++)
  {
	  std::cout << array[i];
  }
  free(array);
}
void malloc()
{
    int* array = (int*)malloc(12);
    for (size_t i = 0; i < 3; i++)
    {
        std::cin >> array[i];
    }
    for (size_t i = 0; i < 3; i++)
    {
        std::cout << array[i];
    }
    free(array);
}
void realloc()
{
    int* count = NULL;
    int*mass = (int*)realloc(count, 2 * sizeof(int));
    if (mass == NULL) 
    { 
        free(count); 
        throw "������ ������������� ������!\n";
    }
    for (size_t i = 0; i < 2; i++)
    {
        std::cin >> mass[i];
    }
    for (size_t i = 0; i < 2; i++)
    {
        std::cout << mass[i];
    }
    free(count);
}
//free store new delete
void FreeStore()
{
    int sizeArray = 5;
    int* array = NULL;
    array = new int[5];
    for (size_t i = 0; i < sizeArray; i++)
    {
        array[i] = 5;
    }

    delete[] array;
    array = NULL;
}