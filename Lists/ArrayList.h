//
// Created by Gerard on 19-2-2016.
//

#ifndef ALGORITHMS_ARRAYLIST_H
#define ALGORITHMS_ARRAYLIST_H

#include <memory>
#include <string.h>
#include "List.h"

#include <iostream>

template< typename T>
class ArrayList : public List<T> {
private:
    std::unique_ptr<T[]> m_arrayData;
    unsigned int m_arraySize;
    unsigned int m_elementCount;

public:
    ArrayList():
            //m_arrayData( (T*) operator new ( sizeof(T)*initialSize)), /* Maybe for further optimisation, but for now, just keep it simple.*/
            m_arrayData(nullptr),
            m_arraySize(0),
            m_elementCount(0)
    {}

    ~ArrayList()
    {
#ifdef DEBUG
        std::cout << "--Destructor Arraylist--- " << std::endl;
#endif
    }

    /***
     * Add a new element
     * If the array is to small, a new array with double size will be allocated,
     * followed by copying all elements, the old array will be freed.
     */
    virtual void add(T element){
        // Check if we still got space
        if(m_elementCount >= m_arraySize)
        {
            if(m_arraySize == 0) {
                // Default allocate minimal 8 elements
                m_arraySize = 8;
                m_arrayData = std::unique_ptr<T[]>(new  T[m_arraySize]);
            }
            else{
                // Re-allocate, double size, create new, move old data, delete old
                auto newArraySize = m_arraySize * 2;

                //std::unique_ptr<T> m_biggerArrayData( (T*) operator new ( sizeof(T)*newArraySize) ); /* Maybe for further optimisation, but for now, just keep it simple.*/
                std::unique_ptr<T[]> m_biggerArrayData( new  T[newArraySize] );
                memcpy(m_biggerArrayData.get(), m_arrayData.get(), m_arraySize*sizeof(T) );

                // Save the new array and size, old one is auto deconstructed
                m_arraySize = newArraySize;
                m_arrayData.swap(m_biggerArrayData);
            }
        }
        // Copy data and increase element count
        m_arrayData.get()[m_elementCount] = element;
        m_elementCount++;
    }

    /***
     * Remove element at position
     * First position is 0.
     * - All elements above the position will be shifted
     * - Pointers to elements above position will not be valid anymore
     */
    virtual void remove(unsigned int position){
        auto maxPosition = m_elementCount-1;

        if( isEmpty() || position > maxPosition)
            throw std::out_of_range("remove()");

        auto array = m_arrayData.get();
        if(position < maxPosition)
        {
            // Delete the element by moving the next element 1 back
            memmove( &array[position], &array[position+1], sizeof(T)*(m_elementCount-position) );
        }

        // Result is always one element less.
        --m_elementCount;
    }

    virtual T& getAt(unsigned int i) const{
        if(i > m_elementCount)
            throw std::out_of_range("getAt()");

        return m_arrayData.get()[i];
    }

    virtual bool isEmpty() const{
        return m_elementCount==0;
    }
    virtual unsigned int size() const{
        return m_elementCount;
    }
};


#endif //ALGORITHMS_ARRAYLIST_H