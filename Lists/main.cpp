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

        ArrayList<SomeClass> arrayList; // Empty arrayList

        try {
            cout << arrayList.getAt(1).getName() << endl;
        }
        catch (const std::exception e) {
            cout << "Ow damm.. there was an exception (Yes, this is actually good) : " << e.what() << endl;
        }
    }

    {
        cout << endl << "Test adding elements and re-allocation." << endl;
        SomeClass::resetCounter();

        ArrayList<SomeClass> arrayList;
        printListSize(arrayList);
        printListElements(arrayList);

        cout << endl;
        SomeClass sjon = SomeClass("Sjon1");
        arrayList.add( sjon );
        arrayList.add( SomeClass("Sjaak2"));
        printListSize(arrayList);
        printListElements(arrayList);

        cout << endl;
        arrayList.add( SomeClass("Henk3") );
        arrayList.add( SomeClass("Piet4") );
        printListSize(arrayList);
        printListElements(arrayList);

        cout << endl << "will ArrayList be destructed?" << endl;
    }

    cout << endl << "Is everyting Destructed?.." << endl;
}

