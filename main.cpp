#include <iostream>
#include <chrono>
#include <memory>
#include <cstring>

#include "TestCases.h"
#include "Sorting.h"


/***********************
 * Main function of this file:
 * - Testing efficiencies of different sorting algorithms.
 * Secondary intentions:
 * - Practise implementing different sorting strategies
 * - Practise on C++ templating
 * - Practise design patterns.
 *************************/

using namespace std;

// Create an interface for sorting methods
template<typename ArrayType>
class SortMethod
{
public:
    virtual void executeSort(ArrayType* data, int dataSize) = 0;
};
template<typename ArrayType>
class MergeSort : public SortMethod<ArrayType>
{
    virtual void executeSort(ArrayType* data, int dataSize)
    {
        Sorting::mergeSort(data, dataSize);
    }
};
template<typename ArrayType>
class SelectionSort : public SortMethod<ArrayType>
{
    virtual void executeSort(ArrayType* data, int dataSize)
    {
        Sorting::selectionSort(data, dataSize);
    }
};


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
    void startSortMeasurement(SortMethod<ArrayType>& testMethod)
    {
        // Create a new array, and copy the content of the testArray.
        unique_ptr<ArrayType> tempArray(new ArrayType[m_testArraySize]);
        memcpy(tempArray.get(), m_TestArray.get(), m_testArraySize*sizeof(ArrayType));

        // Do the test.
        auto startTime = chrono::system_clock::now();
        testMethod.executeSort(m_TestArray.get(), m_testArraySize);
        auto endTime = chrono::system_clock::now();

        // Print result.
        chrono::duration<double> elapsedTime = endTime - startTime;
        cout << elapsedTime.count() << "s" << endl;
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

    // Create the sorting methods/interfaces.
    MergeSort<char> mergeSort;
    SelectionSort<char> selectionSort;

    // Testing
    cout << "Running the measurements: " << endl;
    TestSorting<char> testCharSort(10000);
    testCharSort.startSortMeasurement(selectionSort);
    testCharSort.startSortMeasurement(mergeSort);

    if(0){
        const int arraySize = 100000;
        int largeArray[arraySize];

        auto startTime = chrono::system_clock::now();
        Sorting::selectionSort(largeArray, arraySize);
        auto endTime = chrono::system_clock::now();
        chrono::duration<double> elapsedTime = endTime - startTime;
        cout << elapsedTime.count() << "s " << "for selectionSort." << endl;
    }
    if(0){
        int largeArray[100000];

        auto startTime = chrono::system_clock::now();
        Sorting::mergeSort(largeArray, sizeof(largeArray));
        auto endTime = chrono::system_clock::now();
        chrono::duration<double> elapsedTime = endTime - startTime;
        cout << elapsedTime.count() << "s " << "for MergeSort." << endl;
    }

    return 0;
}