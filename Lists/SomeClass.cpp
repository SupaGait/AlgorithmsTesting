//
// Created by Gerard on 19-2-2016.
//

#include "SomeClass.h"
#include <iostream>

using std::cout;
using std::endl;

unsigned int SomeClass::m_totalNr = 0;

SomeClass::SomeClass():
        m_nr(m_totalNr)
{
    //cout << "Created SomeClass: " << m_nr << endl;
    m_totalNr++;
}
SomeClass::~SomeClass()
{
    //cout << "Destructor SomeClass: " << m_nr << endl;
}
unsigned int SomeClass::getNr(){
    return m_nr;
}
void SomeClass::resetCounter(){
    m_totalNr=0;
}


/***
 * Helper function: print content
 */
void printListSize(const List<SomeClass> &arrayList)
{
    cout << "Size: " << arrayList.size() << endl;
}
/***
 * Helper function: print elements
 */
void printListElements(const List<SomeClass> &arrayList)
{
    for(unsigned int i=0; i<arrayList.size();i++)
    {
        cout << "Element: " << i << " content: " << arrayList.getAt(i).getNr() << endl;
    }
}
