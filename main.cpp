#include <iostream>
#include <chrono>
#include <memory>
#include <cstring>

#include "TestCases.h"
#include "Sorting.h"

using namespace std;

// Create an interface for sorting methods
class SortMethod
{
public:
    virtual void executeSort() = 0;
};

template <typename T>
struct DataSpecification
{
    T* pData;
    int dataSize;
    DataSpecification(T pData, int dataSize): pData(pData), dataSize(dataSize){}
};

// Implementation of sorting methods
class MergeSort : public SortMethod
{
public:
    void executeSort()
    {
        assert(m_dataType.pData);
        Sorting::mergeSort(m_dataType.pData, m_dataType.dataSize);
    }

    void setDataType(DataSpecification dataType)
    {
        m_dataType = dataType;
    }
private:
    DataSpecification m_dataType;
};
/*
class SelectionSort : public SortMethod
{
public:
    template <typename T, T pData, int dataSize>
    void executeSort()
    {
        Sorting::selectionSort(pData,dataSize);
    }
};
*/
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
    void startMeasurement(SortMethod* testMethod)
    {
        // Create a new array, and copy the content of the testArray.
        unique_ptr<ArrayType> tempArray(new ArrayType[m_testArraySize]);
        memcpy(tempArray.get(), m_TestArray.get(), m_testArraySize*sizeof(ArrayType));

        // Do the test.
        auto startTime = chrono::system_clock::now();
        //Sorting::mergeSort(m_TestArray.get(), m_testArraySize);
        //testMethod->executeSort(m_TestArray.get(), m_testArraySize);
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
    MergeSort<> mergeSort;
    //SelectionSort selectionSort;

    // Testing
    cout << "Running the measurements: " << endl;
    TestSorting<char> testCharSort(10000);
    //testCharSort.startMeasurement(selectionSort);

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