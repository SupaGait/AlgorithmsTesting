#include <iostream>
#include <chrono>
#include <memory>
#include <cstring>

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
    TestSorting(const int arraySize):
            m_testArraySize(arraySize)
    {
        m_TestArray.reset(new ArrayType[m_testArraySize]);
    }

    /*** Creates a copy from the testArray to perform the measurement on
    ***/
    void startSortMeasurement(const Sorting::SortMethod<ArrayType>& testMethod) {
        // Create a new array, and copy the content of the testArray.
        unique_ptr<ArrayType> tempArray(new ArrayType[m_testArraySize]);
        memcpy(tempArray.get(), m_TestArray.get(), m_testArraySize * sizeof(ArrayType));

        // Do the test.
        auto startTime = chrono::system_clock::now();
        testMethod.executeSort(m_TestArray.get(), m_testArraySize);
        auto endTime = chrono::system_clock::now();

        // Print result.
        chrono::duration<double> elapsedTime = endTime - startTime;
        cout << testMethod.getName() << ": " << elapsedTime.count() << "s" << endl;
    }
private:
    const int m_testArraySize;
    unique_ptr<ArrayType> m_TestArray;
};


int main() {

    // Test Cases
    cout << "Running some functionality test cases: " << endl;
    testSelectionSort();
    testMergeSort();
    cout << endl;

    // Testing
    cout << "Running the measurements: " << endl;
    TestSorting<char> testCharSort(20000);
    cout << endl << "Char: " << endl;
    testCharSort.startSortMeasurement(Sorting::SelectionSort<char>());
    testCharSort.startSortMeasurement(Sorting::MergeSort<char>());
    {
        TestSorting<int> testIntSort(10000);
        cout << endl << "Int: " << endl;
        testIntSort.startSortMeasurement(Sorting::SelectionSort<int>());
        testIntSort.startSortMeasurement(Sorting::MergeSort<int>());
    }
    {
        TestSorting<float> testFloatSort(10000);
        cout << endl << "float: " << endl;
        testFloatSort.startSortMeasurement(Sorting::SelectionSort<float>());
        testFloatSort.startSortMeasurement(Sorting::MergeSort<float>());
    }
    {
        TestSorting<double> testDoubleSort(10000);
        cout << endl << "double: " << endl;
        testDoubleSort.startSortMeasurement(Sorting::SelectionSort<double>());
        testDoubleSort.startSortMeasurement(Sorting::MergeSort<double>());
    }

    cout << endl << "Same Char as 1st again: " << endl;
    testCharSort.startSortMeasurement(Sorting::SelectionSort<char>());
    testCharSort.startSortMeasurement(Sorting::MergeSort<char>());

    return 0;
}