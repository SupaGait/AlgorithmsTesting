//
// Created by gerard on 12/24/15.
//

#ifndef ALGORITHMS_SORTING_H
#define ALGORITHMS_SORTING_H

#include "Utill.h"

namespace Sorting {

    template <typename T>
    int findMinimalIndex(T* pData,int dataSize, int offset)
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
    void insertionSort(T* pData,int dataSize)
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
                Utill::swap(pData[index], pData[minIndex]);
            }
            // Debug:
//            Utill::print(pData, dataSize);
        }
    };

};


#endif //ALGORITHMS_SORTING_H
