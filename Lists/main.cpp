//
// Created by Gerard on 19-2-2016.
//


#include <iostream>
#include "SomeClass.h"
#include "ArrayList.h"

using std::cout;
using std::endl;

int main()
{
    {
        cout << endl << "Test out of range exception on getAt()." << endl;
        SomeClass::resetCounter();

        ArrayList<SomeClass> arrayList(5);
        cout << arrayList.getAt(1).getNr() << endl;
        cout << arrayList.getAt(4).getNr() << endl;
        try {
            cout << arrayList.getAt(20).getNr() << endl;
        }
        catch (const std::exception e) {
            cout << "Ow damm.. there was an exception (Yes, this is actually good) : " << e.what() << endl;
        }
    }

    {
        cout << endl << "Test adding elements and re-allocation." << endl;
        SomeClass::resetCounter();

        ArrayList<SomeClass> arrayList(2);
        printListSize(arrayList);
        printListElements(arrayList);

        cout << endl;
        arrayList.add( SomeClass() );
        arrayList.add( SomeClass() );
        printListSize(arrayList);
        printListElements(arrayList);

        cout << endl;
        arrayList.add( SomeClass() );
        arrayList.add( SomeClass() );
        printListSize(arrayList);
        printListElements(arrayList);
    }
}

