#include "Test.h"
#include <iostream>
#include "Sorts.h"

template <class T>
bool isSorted(T* array, int size) {
    if (size <= 0) {
        throw "Invalid size of array";
    }
    for (int i = 1; i < size; ++i) {
        if (array[i] < array[i - 1]) {
            return false;
        }
    }
    return true;
}

template <class T>
void printArray(T* array, int size) {
    if (size <= 0) {
        throw "Invalid size of array";
    }
    for (int i = 0; i < size; ++i) {
        std::cout << array[i] << ' ';
    }
    std::cout << '\n';
}

int printResult(bool result) {
    if (result)
    {
        std::cout << "  Test passed" << "\n\n";
        return 1;
    }
    else
    {
        std::cout << "  Test unpassed" << "\n\n";
        return 0;
    }

}

template <class T>
int testSort(T* array, int size, void (*sort)(T*, int)) {
    try {
        std::cout << "  Input array: \n  ";
        printArray(array, size);
        sort(array, size);
        std::cout << "  Output array: \n  ";
        printArray(array, size);
        return printResult(isSorted(array, size));
    }
    catch (const char* error) {
        std::cerr << error << '\n';
        return -1;
    }
}

int goodCounterSort() {

    std::cout << "Good CounterSort Test\n";
    const int SIZE = 20;
    int array[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        array[i] = rand() % 2;
    }
    return testSort(array, SIZE, countingSort);
}

int randomCounterSort() {
    std::cout << "Random CounterSort Test\n";
    const int SIZE = 20;
    int array[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        array[i] = rand() % SIZE;
    }
    return testSort(array, SIZE, countingSort);
}

int badCounterSort() {
    std::cout << "Bad CounterSort Test\n";
    const int SIZE = 2;
    int array[SIZE];
    array[0] = 10000;
    array[1] = 0;
    return testSort(array, SIZE, countingSort);
}

int goodRadixSort() {
    std::cout << "Good RadixSort Test\n";
    const int SIZE = 20;
    int array[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        array[i] = rand() % 10;
    }
    return testSort(array, SIZE, radixSort);
}

int randomRadixSort() {
    std::cout << "Random RadixSort Test\n";
    const int SIZE = 20;
    int array[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        array[i] = rand() % 1000;
    }
    return testSort(array, SIZE, radixSort);
}

int badRadixSort() {
    std::cout << "Bad RadixSort Test\n";
    const int SIZE = 2;
    int array[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        array[i] = rand() % 1000000;
    }
    return testSort(array, SIZE, radixSort);
}

int goodBucketSort() {
    std::cout << "Good BucketSort Test\n";
    const int SIZE = 10;
    double array[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        array[i] = (9 - i) * 0.1;
    }
    return testSort(array, SIZE, bucketSort);
}
int randomBucketSort() {
    std::cout << "Random BucketSort Test\n";
    const int SIZE = 20;
    double array[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        array[i] = (rand() % 100) * 0.01;
    }
    return testSort(array, SIZE, bucketSort);
}
int badBucketSort() {
    std::cout << "Bad BucketSort Test\n";
    const int SIZE = 20;
    double array[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        array[i] = (rand() % 10) * 0.01;
    }
    return testSort(array, SIZE, bucketSort);
}

int goodBinaryInsertionSort() {
    std::cout << "Good BinaryInsertionSort Test\n";
    const int SIZE = 20;
    int array[SIZE];
    for (int i = 0; i < SIZE / 2; ++i) {
        array[2 * i] = 2 * i + 1;
        array[2 * i + 1] = 2 * i;
    }
    return testSort(array, SIZE, binaryInsertionSort);
}
int randomBinaryInsertionSort() {
    std::cout << "Random BinaryInsertionSort Test\n";
    const int SIZE = 20;
    int array[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        array[i] = rand() % 1000;
    }
    return testSort(array, SIZE, binaryInsertionSort);
}
int badBinaryInsertionSort() {
    std::cout << "Bad BinaryInsertionSort Test\n";
    const int SIZE = 20;
    int array[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        array[i] = SIZE - 1 - i;
    }
    return testSort(array, SIZE, binaryInsertionSort);
}

int goodShellInsertionSort() {
    std::cout << "Good shellSort Test\n";
    const int SIZE = 20;
    int array[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        array[i] = SIZE - 1 - i;
    }
    return testSort(array, SIZE, shellSort);
}
int randomShellInsertionSort() {
    std::cout << "Random shellSort Test\n";
    const int SIZE = 20;
    int array[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        array[i] = rand() % 100;
    }
    return testSort(array, SIZE, shellSort);
}
int badShellInsertionSort() {
    std::cout << "Bad shellSort Test\n";
    int size = 20;
    int array[] = { 738, 57, 616, 790, 640, 679, 335, 6, 972, 98, 95, 319, 454, 223, 289, 760, 905, 126, 123, 506 };
    for (int i = 0; i < size / 4; ++i) {
    }
    return testSort(array, size, shellSort);
}

int goodHibbardInsertionSort() {
    std::cout << "Good hibbardSort Test\n";
    const int SIZE = 20;
    int array[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        array[i] = SIZE - 1 - i;
    }
    return testSort(array, SIZE, hibSort);
}
int randomHibbardInsertionSort() {
    std::cout << "Random hibbardSort Test\n";
    const int SIZE = 20;
    int array[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        array[i] = rand() % 100;
    }
    return testSort(array, SIZE, hibSort);
}
int badHibbardInsertionSort() {
    std::cout << "Bad hibbardSort Test\n";
    int size = 20;
    int array[] = { 738, 57, 616, 790, 640, 679, 335, 6, 972, 98, 95, 319, 454, 223, 289, 760, 905, 126, 123, 506 };
    for (int i = 0; i < size / 4; ++i) {
    }
    return testSort(array, size, hibSort);
}

int goodSedgewickInsertionSort() {
    std::cout << "Good sedgewickSort Test\n";
    const int SIZE = 20;
    int array[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        array[i] = SIZE - 1 - i;
    }
    return testSort(array, SIZE, sedSort);
}
int randomSedgewickInsertionSort() {
    std::cout << "Random sedgewickSort Test\n";
    const int SIZE = 20;
    int array[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        array[i] = rand() % 100;
    }
    return testSort(array, SIZE, sedSort);
}
int badSedgewickInsertionSort() {
    std::cout << "Bad sedgewickSort Test\n";
    int size = 20;
    int array[] = { 738, 57, 616, 790, 640, 679, 335, 6, 972, 98, 95, 319, 454, 223, 289, 760, 905, 126, 123, 506 };
    for (int i = 0; i < size / 4; ++i) {
    }
    return testSort(array, size, sedSort);
}