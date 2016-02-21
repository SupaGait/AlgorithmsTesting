//
// Created by Gerard on 19-2-2016.
//

#ifndef ALGORITHMS_SOMECLASS_H
#define ALGORITHMS_SOMECLASS_H

#include "List.h"
#include <string>

class SomeClass
{
private:
    static unsigned int m_totalNr;
    unsigned int m_nr;
    std::string m_name;
public:
    SomeClass();
    SomeClass(const std::string& name);
    ~SomeClass();
    std::string getName();
    static void resetCounter();
};
void printListSize(const List<SomeClass> &arrayList);
void printListElements(const List<SomeClass> &arrayList);


#endif //ALGORITHMS_SOMECLASS_H
