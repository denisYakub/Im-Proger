#include "Sorts.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include "List.h"

const std::string ERROR_SIZE = "Invalid size";
const std::string ERROR_ARRAY_NULLPTR = "Nullpointer excepted";
const std::string ERROR_DATA_ARRAY = "Invalid value in array";

int getMax(const int* arr, const int size)
{
    int max = arr[0];
    for (int i = 1; i < size; ++i)
    {
        if (arr[i] < 0)
            throw ERROR_DATA_ARRAY;
        max = (arr[i] > max) ? arr[i] : max;
    }
    return max;
}

int getBitwise(int number, int k)
{
    return ((number / (int)pow(10, k - 1)) % 10);
}

void copyArray(int* first, int* second, int size)
{
    for (int i = 0; i < size; ++i)
        first[i] = second[i];
}

void countingSort(int* array, int size)
{
    if (array == nullptr)
        throw ERROR_ARRAY_NULLPTR;

    if (size <= 0)
        throw ERROR_SIZE;

    int k = getMax(array, size);

    int* c = new int[k + 1];

    for (int i = 0; i < k + 1; ++i)
        c[i] = 0;

    for (int i = 0; i < size; ++i)
        c[array[i]]++;


    for (int i = 1; i < k + 1; ++i)
        c[i] += c[i - 1];

    int j = 0;
    for (int i = 0; i < k + 1; ++i)
    {
        for (; j < c[i]; ++j)
            array[j] = i;

    }
    delete[] c;
}

void radixSort(int* array, int size)
{
    if (array == nullptr)
        throw ERROR_ARRAY_NULLPTR;

    if (size <= 0)
        throw ERROR_SIZE;

    int max = getMax(array, size);

    int maxDigits = 0;
    while (max > 0)
    {
        maxDigits++;
        max /= 10;
    }

    int* b = new int[size];

    for (int k = 1; k <= maxDigits; ++k) {
        int c[10] = { 0 };

        for (int i = 0; i < size; ++i) {
            c[getBitwise(array[i], k)]++;
        }

        int counter = 0;
        for (int i = 0; i < 10; ++i) {
            std::swap(counter, c[i]);
            counter += c[i];
        }

        int* b = new int[size];

        for (int i = 0; i < size; ++i) {
            int d = getBitwise(array[i], k);
            b[c[d]] = array[i];
            c[d]++;
        }
        copyArray(array, b, size);
        delete[] b;
    }
}

void bucketSort(double* array, int size)
{
    if (array == nullptr)
        throw ERROR_ARRAY_NULLPTR;

    if (size <= 0)
        throw ERROR_SIZE;

    List<double>* b = new List<double>[size];

    for (int i = 0; i < size; ++i)
    {
        if ((array[i] < 0) || (array[i] >= 1))
            throw ERROR_DATA_ARRAY;

        b[(int)floor((array[i] * size))] += array[i];
    }

    int counter = 0;
    for (int i = 0; i < size; ++i) {
        for (List<double>::Node* curr = b[i].head_; curr != nullptr; curr = curr->getNext()) {
            array[counter] = curr->getData();
            counter++;
        }
    }
    delete[] b;
}

int binSearch(int* array, int value, int begin, int end) {
    if (begin == end) {
        if (value > array[begin]) {
            return begin + 1;
        }
        return begin;
    }

    int mid = (begin + end) / 2;
    if (array[mid] > value) {
        return binSearch(array, value, begin, mid);
    }
    else {
        return binSearch(array, value, mid + 1, end);
    }

}

void binaryInsertionSort(int* array, int size) {
    for (int i = 1; i < size; ++i) {
        int position = binSearch(array, array[i], 0, i - 1);
        for (int j = i - 1; j >= position; --j) {
            std::swap(array[j], array[j + 1]);
        }
    }
}

void shellSort(int* array, int size) {
    int counter = 0;
    for (int step = size / 2; step > 0; step /= 2) {
        for (int i = 0; i < step; ++i) {
            List<int> list;
            for (int curr = i; curr < size; curr += step) {
                counter += (list += array[curr]);
            }
            List<int>::Node* currElem = list.head_;
            for (int curr = i; curr < size; curr += step) {
                array[curr] = currElem->getData();
                currElem = currElem->getNext();
            }
        }
    }
    std::cout << "Time of Shell on array of " << size << " elements is " << counter << std::endl;
}

void hibSort(int* array, int size) {
    int counter = 0;
    int k = (int)log2(size + 1);
    for (int step = pow(2, k) - 1; step > 0; step = pow(2, k) - 1) {
        for (int i = 0; i < step; ++i) {
            List<int> list;
            for (int curr = i; curr < size; curr += step) {
                counter += (list += array[curr]);
            }
            List<int>::Node* currElem = list.head_;
            for (int curr = i; curr < size; curr += step) {
                array[curr] = currElem->getData();
                currElem = currElem->getNext();
            }
        }
        k--;
    }
    std::cout << "Time of Hibbard on array of " << size << " elements is " << counter << std::endl;
}

void sedSort(int* array, int size) {
    int counter = 0;
    int k = 2 * (int)log2((size - 1) / 9);
    while (k >= 0) {
        int step;
        if (k % 2 == 0) {
            step = 9 * pow(2, k) - 9 * pow(2, k / 2) + 1;
        }
        else {
            step = 8 * pow(2, k) - 6 * pow(2, (k + 1) / 2) + 1;
        }
        for (int i = 0; i < step; ++i) {
            List<int> list;
            for (int curr = i; curr < size; curr += step) {
                counter += (list += array[curr]);
            }
            List<int>::Node* currElem = list.head_;
            for (int curr = i; curr < size; curr += step) {
                array[curr] = currElem->getData();
                currElem = currElem->getNext();
            }
        }
        k--;
    }
    std::cout << "Time of Sedgewick on array of " << size << " elements is " << counter << std::endl;
}