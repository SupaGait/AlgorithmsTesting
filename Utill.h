//
// Created by gerard on 12/28/15.
//

#ifndef ALGORITHMS_UTILL_H
#define ALGORITHMS_UTILL_H

#include <cstdio>

namespace Utill {
    template<typename _T>
    void swap(_T &var1, _T &var2) {
        _T tempVar1 = var1;
        var1 = var2;
        var2 = tempVar1;
    }

    template <typename T>
    void print(T* pData, int dataSize)
    {
        // Print the content of the array
        for(int i = 0; i < dataSize; i++)
        {
            printf("%d.", pData[i]);
            if((i%20 == 0) && (i != 0))
                printf("\n");
        }
        printf("\n");
    }
}
#endif //ALGORITHMS_UTILL_H
