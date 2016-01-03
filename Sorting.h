//
// Created by gerard on 12/24/15.
//

/***
 * Implemented sorting methods:
 * - Selection Sort
 * - Merge Sort
 *
 * Using templates to give the option to sort  arrays containing different basic types
 */

#ifndef ALGORITHMS_SORTING_H
#define ALGORITHMS_SORTING_H

#include <memory>
#include <cstring>
#include <cstdio>
#include <cstring>
#include "Util.h"

namespace Sorting {

    template <typename T>
    int findMinimalIndex(T* const pData,int dataSize, int offset)
    {
        int minIndex = offset;
        T minValue = pData[offset];
        // Loop through the data starting from offset+1
        for(int i=offset+1; i<dataSize; i++)
        {
            // If there is a lower value, save the value and the index
            if(pData[i] < minValue)
            {
                minValue = pData[i];
                minIndex = i;
            }
        }
        return minIndex;
    }

    template <typename T>
    void selectionSort(T* const pData, int dataSize)
    {
        // Sort the array using insertion sort
        for(int index=0; index<dataSize; index++)
        {
//            printf("index:%d\n", index);
            int minIndex = findMinimalIndex(pData, dataSize, index);
            if(minIndex > index)
            {
//                printf("Swapping:%d(%d) with %d(%d)\n",
//                    pData[index],index,pData[minIndex],minIndex );
                Util::swap(pData[index], pData[minIndex]);
            }
            // Debug:
//            Util::print(pData, dataSize);
        }
    };

    // IndexUpperEnd is the last index containing data
    template <typename T>
    void merge(T* const pData, int indexLowerStart, int indexLowerEnd, int indexUpperEnd)
    {
        const int lowerSize = indexLowerEnd - indexLowerStart + 1;
        const int upperSize = indexUpperEnd - indexLowerEnd;

//        printf("_Merge(%d,%d,%d): [%d:%d] [%d:%d]\n\t: ",
//               indexLowerStart, indexLowerEnd, indexUpperEnd,
//               indexLowerStart, lowerSize,
//               indexLowerEnd+1, upperSize);
//        for(int i = indexLowerStart; i <= indexUpperEnd; i++)
//            printf("%d.", pData[i]);
//        printf("\n");

        // Create temporary arrays to hold the sorted arrays to be merged
        std::unique_ptr<T[]> dataCopyLower( new T[lowerSize] );
        std::unique_ptr<T[]> dataCopyUpper( new T[upperSize] );

        // Copy the data array, lowerStartIndex is the zero indexData in pDataCopy
        T* const pDataCopyLower = dataCopyLower.get();
        T* const pDataCopyUpper = dataCopyUpper.get();
        std::memcpy(pDataCopyLower, &pData[indexLowerStart], lowerSize * sizeof(T));
        std::memcpy(pDataCopyUpper, &pData[indexLowerEnd+1], upperSize * sizeof(T));

        // Debug
//        printf("\t: ");
//        for(int i=0;i<lowerSize;i++)
//            printf("%d.",pDataCopyLower[i]);
//        printf("|");
//        for(int i=0;i<upperSize;i++)
//            printf("%d.",pDataCopyUpper[i]);
//        printf("\n");


        int indexData = indexLowerStart;
        int indexLowerPart = 0;
        int indexUpperPart = 0;

        // For all elements, match the lowest in the parts, merge, next; until all elements/parts are done.
        while((indexData < indexUpperEnd) && (indexLowerPart < lowerSize) && (indexUpperPart < upperSize) )
        {
//            printf("\t- ");
//            for(int i = indexLowerStart; i <= indexUpperEnd; i++)
//                printf("%d.", pData[i]);
//            printf("\n");

            // Determine the element with the lowest data, and copy it and go to next element.
            if( pDataCopyLower[indexLowerPart] < pDataCopyUpper[indexUpperPart])
            {
                pData[indexData] = pDataCopyLower[indexLowerPart];
                indexLowerPart++;
            }
            else{
                pData[indexData] = pDataCopyUpper[indexUpperPart];
                indexUpperPart++;
            }
            indexData++;
        }

        // Copy any remaining elements
        if(indexLowerPart >= lowerSize)
        {
            // LowerPart done, so copy remaining upper part
            std::memcpy(&pData[indexData], &pDataCopyUpper[indexUpperPart], (upperSize - indexUpperPart) * sizeof(T) );
        }
        else
        {
            // UpperPart done, so copy remaining lower part
            std::memcpy(&pData[indexData], &pDataCopyLower[indexLowerPart], (lowerSize - indexLowerPart) * sizeof(T) );
        }

//        printf("\t> ");
//        for(int i = indexLowerStart; i <= indexUpperEnd; i++)
//            printf("%d.", pData[i]);
//        printf("\n");
    }
    template <typename T>
    void mergeSort(T* const pData, int indexStart, int indexLast)
    {
        // Recursively devise the array
        if(indexLast - indexStart > 0)
        {
            // Calculate center index
            int centerIndex = indexStart + (indexLast - indexStart) / 2;

//            printf("MergeSort: %d:%d, %d:%d \n", indexStart, centerIndex,centerIndex+1, indexLast);
            // Divide
            mergeSort(pData, indexStart, centerIndex);
            mergeSort(pData, centerIndex+1, indexLast);

            // Conquer
            merge(pData, indexStart, centerIndex, indexLast);
        }
    }
    template <typename T>
    void mergeSort(T* const pData, int dataSize)
    {
        assert(dataSize > 0);
        mergeSort(pData, 0, dataSize-1);
    }

    // Create an interface for sorting methods
    template<typename ArrayType>
    class SortMethod
    {
    public:
        virtual ~SortMethod(){;}
        virtual void executeSort(ArrayType* data, int dataSize) const = 0;
        virtual std::string const getName() const = 0;
    };
    template<typename ArrayType>
    class MergeSort : public SortMethod<ArrayType>
    {
    public:
        MergeSort() : m_Name("MergeSort"){;}
        virtual void executeSort(ArrayType* data, int dataSize) const
        {
            Sorting::mergeSort(data, dataSize);
        }
        virtual std::string const getName() const { return m_Name;}
    private:
        std::string m_Name;
    };
    template<typename ArrayType>
    class SelectionSort : public SortMethod<ArrayType>
    {
    public:
        SelectionSort() : m_Name("SelectionSort"){;}
        virtual void executeSort(ArrayType* data, int dataSize) const
        {
            Sorting::selectionSort(data, dataSize);
        }
        virtual std::string const getName() const { return m_Name;}
    private:
        std::string m_Name;
    };
};


#endif //ALGORITHMS_SORTING_H
