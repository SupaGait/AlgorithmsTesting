//
// Created by Gerard on 19-2-2016.
//

#include "SomeClass.h"
#include <iostream>
using std::cout;
using std::endl;

unsigned int SomeClass::m_totalNr = 0;

SomeClass::SomeClass():
        SomeClass("O_o"){
}
SomeClass::SomeClass(const std::string& name):
        m_nr(m_totalNr),
        m_name(name)
{
#ifdef DEBUG
    cout << "Created SomeClass: " << m_nr << " " << m_name << endl;
#endif
    ++m_totalNr;
}
SomeClass::~SomeClass()
{
#ifdef DEBUG
    cout << "Destructor SomeClass: " << m_nr << " " << m_name << endl;
#endif
}
std::string SomeClass::getName(){
    return m_name;
}
void SomeClass::resetCounter(){
    m_totalNr=0;
}

/***
 * Helper function: print elements
 */
void printListElements(const List<SomeClass> &arrayList)
{
    auto size = arrayList.size();
    cout << "Size: " << size << endl;
    for(unsigned int i=0; i<size ;i++)
    {
        cout << "Element: " << i << " content: " << arrayList.getAt(i).getName() << endl;
    }
}

