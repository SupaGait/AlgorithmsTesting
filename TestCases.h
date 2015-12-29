//
// Created by gerard on 12/29/15.
//

#ifndef ALGORITHMS_TESTCASES_H
#define ALGORITHMS_TESTCASES_H

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

// Testing functioning of insertion sort
// Using char and int array.
void testSelectionSort()
{
    int result = 0;

    {
        char data[5] = {4,3,2,1,0};
        Sorting::selectionSort(data, sizeof(data));

        char expectedResult[5] = {0, 1, 2, 3, 4};
        if ((result = isEqual(data, expectedResult, sizeof(expectedResult))) != 0)
            cout << "Assert error at: " << result << endl;

    }
    {
        int data[7] = {-1, 1, 2, -6, 200, 50, 2};
        constexpr int ArraySize = sizeof(data)/sizeof(int);

        Sorting::selectionSort(data, ArraySize);

        int expectedResult[7] = { -6, -1, 1, 2, 2, 50, 200};
        if ((result = isEqual(data, expectedResult, ArraySize)) != 0)
            cout << "Assert error at: " << result << endl;
    }

    cout << "Done with selectionSort test." << endl;
}

void testMergeSort()
{
    int result = 0;

    {
        char data[5] = {4,3,2,1,0};
        Sorting::mergeSort(data, sizeof(data));

        char expectedResult[5] = {0, 1, 2, 3, 4};
        if ((result = isEqual(data, expectedResult, sizeof(expectedResult))) != 0)
            cout << "Assert error at: " << result << endl;

    }
    cout << "Done with mergeSort test." << endl;
}


#endif //ALGORITHMS_TESTCASES_H
