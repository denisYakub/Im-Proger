#include <iostream>
#include "Sorts.h"
#include "Test.h"
using namespace std;

int main()
{
    int counterPassedTest = 0;
    const int NOFTEST = 21;

    counterPassedTest += goodCounterSort();
    counterPassedTest += randomCounterSort();
    counterPassedTest += badCounterSort();

    counterPassedTest += goodRadixSort();
    counterPassedTest += randomRadixSort();
    counterPassedTest += badRadixSort();

    counterPassedTest += goodBucketSort();
    counterPassedTest += randomBucketSort();
    counterPassedTest += badBucketSort();

    counterPassedTest += goodBinaryInsertionSort();
    counterPassedTest += randomBinaryInsertionSort();
    counterPassedTest += badBinaryInsertionSort();

    counterPassedTest += goodShellInsertionSort();
    counterPassedTest += randomShellInsertionSort();
    counterPassedTest += badShellInsertionSort();

    counterPassedTest += goodHibbardInsertionSort();
    counterPassedTest += randomHibbardInsertionSort();
    counterPassedTest += badHibbardInsertionSort();

    counterPassedTest += goodSedgewickInsertionSort();
    counterPassedTest += randomSedgewickInsertionSort();
    counterPassedTest += badSedgewickInsertionSort();

    cout << counterPassedTest << " of " << NOFTEST << " tests passed";

    return 0;
}