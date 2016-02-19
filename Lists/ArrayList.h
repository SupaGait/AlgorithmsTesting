//
// Created by Gerard on 19-2-2016.
//

#ifndef ALGORITHMS_ARRAYLIST_H
#define ALGORITHMS_ARRAYLIST_H

#include <memory>
#include <type_traits>
#include <string.h>
#include "List.h"

template< typename T>
class ArrayList : public List<T> {
private:
    std::unique_ptr<T> m_arrayData;
    unsigned int m_arraySize;
    unsigned int m_elementCount;

public:
    ArrayList(unsigned int initialSize):
            m_arrayData( new T[initialSize] ),
            m_arraySize(initialSize),
            m_elementCount(0)
    {

    }
    virtual void add(T element){
        // Check if we still got space
        if(m_elementCount >= m_arraySize)
        {
            // Re-allocate, double size, create new, move old data, delete old
            auto newArraySize = m_arraySize * 2;

            std::unique_ptr<T> m_biggerArrayData(new T[newArraySize]);
            memcpy(m_biggerArrayData.get(), m_arrayData.get(), m_arraySize );

            // Save the new array and size, old one is auto deconstructed
            m_arraySize = newArraySize;
            m_arrayData.swap(m_biggerArrayData);
        }

        // Copy data and increase element count
        m_arrayData.get()[m_elementCount] = element;
        m_elementCount++;
    }

    virtual void remove(unsigned int position){

    }

    virtual T getAt(unsigned int i) const{
        if(i > m_arraySize)
            throw std::out_of_range("out of range");

        return m_arrayData.get()[i];
    }

    virtual bool isEmpty() const{
        return true;
    }
    virtual unsigned int size() const{
        return m_elementCount;
    }
};


#endif //ALGORITHMS_ARRAYLIST_H