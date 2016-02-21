//
// Created by Gerard on 19-2-2016.
//


#include <iostream>
#include "SomeClass.h"
#include "ArrayList.h"

void testArrayList();

// Prototypes
void testGet(List<SomeClass> &&list);
void testAdd(List<SomeClass> &&list);
void testRemove(List<SomeClass> &&list);

using std::cout;
using std::endl;

int main()
{
    testArrayList();
}

void testArrayList() {

    // Test functionality of arraylist
    // Each function receives a new instance
    testGet( ArrayList<SomeClass>() );
    testAdd( ArrayList<SomeClass>() );
    testRemove( ArrayList<SomeClass>() );

}

void testRemove(List<SomeClass> &&list) {
    cout << endl << "Test removing elements." << endl;
    SomeClass::resetCounter();

    list.add( SomeClass("PersonPos0") );
    list.add( SomeClass("PersonPos1") );
    list.add( SomeClass("PersonPos2") );
    list.add( SomeClass("PersonPos3 < delete") );
    list.add( SomeClass("PersonPos4") );
    list.add( SomeClass("PersonPos5") );
    printListElements(list);

    list.remove(3);
    printListElements(list);
}

void testAdd(List<SomeClass> &&list) {
    cout << endl << "Test adding elements and re-allocation." << endl;
    SomeClass::resetCounter();

    printListElements(list);

    cout << endl;
    SomeClass sjon = SomeClass("Sjon1");
    list.add( sjon );
    list.add( SomeClass("Sjaak2"));
    printListElements(list);

    cout << endl;
    list.add( SomeClass("Henk3") );
    list.add( SomeClass("Piet4") );
    printListElements(list);
}

void testGet(List<SomeClass> &&list) {
    cout << endl << "Test out of range exception on getAt()." << endl;
    SomeClass::resetCounter();

    try {
        cout << list.getAt(1).getName() << endl;
    }
    catch (const std::exception e) {
        cout << "Ow damm.. there was an exception (Yes, this is actually good) : " << e.what() << endl;
    }
   }

