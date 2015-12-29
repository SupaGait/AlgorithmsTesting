#include <iostream>
#include <cassert>
#include "Sorting.h"

using namespace std;

// Arrays need to have the same size!
// Returns index if not equal
// returns 0 if OK.
template <typename T>
int isEqual(T* array1, T* array2, int arraySize)
{
    for (int i = 0; i < arraySize; ++i) {
        assert(array1[i] == array2[i]);

        if (array1[i] != array2[i])
        {
            return i;
        }
    }
    return 0;
}

void testInsertionSort()
{
    int result = 0;

    {
        char data[5] = {4,3,2,1,0};
        Sorting::insertionSort(data, sizeof(data));

        char expectedResult[5] = {0, 1, 2, 3, 4};
        if ((result = isEqual(data, expectedResult, sizeof(expectedResult))) != 0)
            cout << "Assert error at: " << result << endl;

    }
    {
        int data[7] = {-1, 1, 2, -6, 200, 50, 2};
        constexpr int ArraySize = sizeof(data)/sizeof(int);

        Sorting::insertionSort(data, ArraySize);

        int expectedResult[7] = { -6, -1, 1, 2, 2, 50, 200};
        if ((result = isEqual(data, expectedResult, ArraySize)) != 0)
            cout << "Assert error at: " << result << endl;
    }

    cout << "Done with insertion test." << endl;
}

int main() {
    cout << "Starting tests:" << endl;

    testInsertionSort();

    return 0;
}