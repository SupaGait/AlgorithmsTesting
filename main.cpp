#include <iostream>
#include <chrono>
#include <memory>
#include <cstring>
#include <algorithm>    // STD::sort

#include "TestCases.h"
#include "Sorting.h"


/***********************
 * Main function of this project:
 * - Testing efficiencies of different sorting algorithms.
 * Secondary intentions:
 * - Practise implementing different sorting strategies
 * - Practise on C++ templating
 * - Practise design patterns.
 *************************/

using namespace std;

// Use the same array with different sorting techniques.
// Possible with different data types
template<typename ArrayType>
class TestSorting
{
public:
    TestSorting(const unsigned int arraySize) : m_DataVec(arraySize){;}

    /*** Creates a copy from the testArray to perform the measurement on
    ***/
    void startSortMeasurement(const Sorting::SortMethod<ArrayType>& testMethod) {
        // Create a new array, and copy the content of the testArray.
        //unique_ptr<ArrayType> tempArray(new ArrayType[m_testArraySize]);
        //memcpy(tempArray.get(), m_DataVec.get(), m_testArraySize * sizeof(ArrayType));
        std::vector<ArrayType> testVector(m_DataVec);

        // Do the test.
        auto startTime = chrono::system_clock::now();
        testMethod.executeSort(testVector);
        auto endTime = chrono::system_clock::now();

        // Print result.
        chrono::duration<double> elapsedTime = endTime - startTime;
        cout << testMethod.getName() << ": " << elapsedTime.count() << "s" << endl;
    }
private:
    std::vector<ArrayType> m_DataVec;
};



#define testSorting(TYPE) \
{ \
    constexpr int ArraySize = 20000; \
    TestSorting<TYPE> testCharSort(ArraySize); \
    std::cout << std::endl << #TYPE << std::endl; \
    testCharSort.startSortMeasurement(Sorting::SelectionSort<TYPE>()); \
    testCharSort.startSortMeasurement(Sorting::MergeSort<TYPE>()); \
    testCharSort.startSortMeasurement(Sorting::StdSort<TYPE>()); \
}

int main() {


    // Test Cases
    cout << "Running some functionality test cases: " << endl;
    testSelectionSort();
    testMergeSort();
    cout << endl;

    // Testing
    cout << "Running the measurements: " << endl;
    {
        testSorting(char)
        testSorting(int)
        testSorting(float)
        testSorting(double)
    }

/*
    TestSorting<char> testCharSort(ArraySize);
    cout << endl << "Char: " << endl;
    testCharSort.startSortMeasurement(Sorting::SelectionSort<char>());
    testCharSort.startSortMeasurement(Sorting::MergeSort<char>());
    testCharSort.startSortMeasurement(Sorting::StdSort<char>());
    {
        TestSorting<int> testIntSort(ArraySize);
        cout << endl << "Int: " << endl;
        testIntSort.startSortMeasurement(Sorting::SelectionSort<int>());
        testIntSort.startSortMeasurement(Sorting::MergeSort<int>());
        testIntSort.startSortMeasurement(Sorting::StdSort<int>());
    }
    {
        TestSorting<float> testFloatSort(ArraySize);
        cout << endl << "float: " << endl;
        testFloatSort.startSortMeasurement(Sorting::SelectionSort<float>());
        testFloatSort.startSortMeasurement(Sorting::MergeSort<float>());
        testFloatSort.startSortMeasurement(Sorting::StdSort<float>());
    }
    {
        TestSorting<double> testDoubleSort(ArraySize);
        cout << endl << "double: " << endl;
        testDoubleSort.startSortMeasurement(Sorting::SelectionSort<double>());
        testDoubleSort.startSortMeasurement(Sorting::MergeSort<double>());
        testDoubleSort.startSortMeasurement(Sorting::StdSort<double>());
    }

    cout << endl << "Same Char as 1st again: " << endl;
    testCharSort.startSortMeasurement(Sorting::SelectionSort<char>());
    testCharSort.startSortMeasurement(Sorting::MergeSort<char>());
    testCharSort.startSortMeasurement(Sorting::StdSort<char>());
*/
    return 0;
}