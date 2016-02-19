//
// Created by Gerard on 19-2-2016.
//

#ifndef ALGORITHMS_LIST_H
#define ALGORITHMS_LIST_H


template<typename T>
class List {
public:
    virtual ~List(){}
    virtual void add(T element) = 0;
    virtual void remove(unsigned int position) = 0;
    virtual T& getAt(unsigned int) const = 0;
    virtual bool isEmpty() const = 0;
    virtual unsigned int size() const = 0;
};


#endif //ALGORITHMS_LIST_H
