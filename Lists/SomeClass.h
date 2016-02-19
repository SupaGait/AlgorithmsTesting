//
// Created by Gerard on 19-2-2016.
//

#ifndef ALGORITHMS_SOMECLASS_H
#define ALGORITHMS_SOMECLASS_H

#include "List.h"


class SomeClass
{
private:
    static unsigned int m_totalNr;
    unsigned int m_nr;
public:
    SomeClass();
    ~SomeClass();
    unsigned int getNr();
    static void resetCounter();
};
void printListSize(const List<SomeClass> &arrayList);
void printListElements(const List<SomeClass> &arrayList);


#endif //ALGORITHMS_SOMECLASS_H
