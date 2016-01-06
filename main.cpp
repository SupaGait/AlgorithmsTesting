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
    double startSortMeasurement(const Sorting::SortMethod<ArrayType>& testMethod, bool printResult = true) {
        // Create a new array, and copy the content of the testArray.
        //unique_ptr<ArrayType> tempArray(new ArrayType[m_testArraySize]);
        //memcpy(tempArray.get(), m_DataVec.get(), m_testArraySize * sizeof(ArrayType));
        std::vector<ArrayType> testVector(m_DataVec);

        // Do the test.
        auto startTime = chrono::system_clock::now();
        testMethod.executeSort(testVector);
        auto endTime = chrono::system_clock::now();

        chrono::duration<double> elapsedTime = endTime - startTime;

        // Print result.
        if(printResult)
            cout << testMethod.getName() << ": " << elapsedTime.count() << "s" << endl;

        return elapsedTime.count();
    }
private:
    std::vector<ArrayType> m_DataVec;
};

template<typename Type, int Size>
void testSorting() {
    TestSorting<Type> testCharSort(Size);
    std::cout << std::endl << typeid(Type).name() << std::endl;
    testCharSort.startSortMeasurement(Sorting::SelectionSort<Type>());
    testCharSort.startSortMeasurement(Sorting::MergeSort<Type>());
    testCharSort.startSortMeasurement(Sorting::StdSort<Type>());
}

int main() {


    // Test Cases
    cout << "Running some functionality test cases: " << endl;
    testSelectionSort();
    testMergeSort();
    cout << endl;

    // Testing
    cout << "Running simple measurements: " << endl;
    {
        constexpr int ArraySize = 1000;
        testSorting<char,ArraySize>();
        testSorting<int,ArraySize>();
        testSorting<float,ArraySize>();
        testSorting<double,ArraySize>();
    }

    cout << std::endl << "Running in exponential increasing size: " << endl;
    cout << "Size , std sort, merge sort, selection sort " << endl;
    double totalSelectionTime = 0;
    double totalMergeTime = 0;
    double totalStdTime = 0;
    for(int i=10; i <= 100000; i = i*10 )
    {
        TestSorting<double> testCharSort(i); \
        double stdTime = testCharSort.startSortMeasurement(Sorting::StdSort<double>(), false);
        double mergeTime = testCharSort.startSortMeasurement(Sorting::MergeSort<double>(), false);
        double selectionTime = testCharSort.startSortMeasurement(Sorting::SelectionSort<double>(), false);
        std::cout << i << ": " << stdTime << "\t" << mergeTime << "\t" << selectionTime<< std::endl;
    }

    return 0;
}