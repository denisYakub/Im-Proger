#include<iostream>
#include<stdlib.h>

//Extern
//способы передачи информации о глобальных переменных файлам программы.
int Myage;

//Static
//добавл€€ static к переменной, объ€вленной вне блока, мы определ€ем еЄ как внутреннюю, то есть такую, которую можно использовать только в файле, в котором она определена.
//»спользование ключевого слова static с локальными переменными измен€ет их свойство продолжительности жизни с автоматического на статическое

void incrementAndPrint()
{
	static int s_value = 1; // переменна€ s_value €вл€етс€ статической
	++s_value;
	std::cout << s_value << std::endl;
} // переменна€ s_value не уничтожаетс€ здесь, но становитс€ недоступной

//int main()
//{
//	incrementAndPrint();
//	incrementAndPrint();
//	incrementAndPrint();
//}

//heap(куча)
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
        throw "ќшибка перевыделени€ пам€ти!\n";
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