//
// Created by Gerard on 21-2-2016.
//

#ifndef ALGORITHMS_LINKEDLIST_H
#define ALGORITHMS_LINKEDLIST_H

#include "List.h"
#include <memory>
#include <exception>
#include <assert.h>

using std::unique_ptr;

// Forward declaration
template<typename T>
class Node;

/***
 * Linked list implementation
 */
template<typename T>
class LinkedList : public List<T>
{
    using node = Node<T>;
public:
    virtual void add(T element)
    {
        if(isEmpty())
        {
            // Create a new head element
            m_head = unique_ptr<node>(new Node<T>(element) ); // node alias does not seem to work with new???
        }
        else
        {
            // Find the last node, and add the new node
            auto& lastNode = findNode(-1);
            lastNode.insertAfter(element);
        }
        ++m_nodeCount;
    }

    virtual void remove(unsigned int position){/*TODO*/};

    virtual T &getAt(unsigned int i) const
    {
        return( findNode(i).getElement() );
    }

    virtual bool isEmpty() const {return m_head.get()== nullptr;}

    virtual unsigned int size() const {return m_nodeCount;}

private:
    /***
     * Find a node with a given number by walking through the nodes.
     * First node is 0
     * nr < 0 = find the last
     * nr > size an exception will be thrown
     */
    node& findNode(int nr) const
    {
        if(isEmpty())
            throw std::out_of_range("List is empty");

        if(nr < 0)
        {
            // Iterate the nodes until last is found
            auto node = m_head.get();
            while(node->getNext())
                node = node->getNext();

            // Found last node, add the new node
            return *node;
        }
        else
        {
            if(nr > m_nodeCount-1)
                throw std::out_of_range("Requested index is out of range.");

            // Find the node
            auto node = m_head.get();
            unsigned int nodeNr = 0;
            while(node->getNext() && nodeNr != nr) {
                node = node->getNext();
                ++nodeNr;
            }

            return *node;
        }
    }
private:
    unique_ptr<node> m_head;
    unsigned int m_nodeCount;
};

/***
 * Used as metadata in the list to locate previous and next element.
 */
template<typename T>
class Node
{
    using node = Node<T>;
    using nodeObj = unique_ptr<node>;
public:
    /***
     * Constructor for initial element
     */
    Node(T element):
        m_previous(nullptr),
        m_next(nullptr),
        m_element(element)
    {/*Empty*/}

    /***
    * Constructor for adding a new node
    */
    Node(node* previous, nodeObj& next, T element):
            m_previous(previous),
            m_next(next.release()),
            m_element(element)
    {/*Empty*/};

    /***
     * Retrieve the element
     */
    T& getElement(){return m_element;}

    /***
     * Insert a node after the current node.
     */
    void insertAfter(T element)
    {
        // Create the new node, transfer ownership of current next node
        auto newNode = nodeObj( new Node<T>(this, m_next, element) );
        // Get ownership of the new node
        m_next.reset(newNode.release());
    }
    void remove();

    /***
     * Returns nullprt if there is no next
     */
    node* getNext(){ return m_next.get();}

    /***
     * Returns nullprt if there is no previous
     */
    node* getPrevious(){ return m_previous;}

private:
    node* m_previous;
    nodeObj m_next;
    T m_element;
};

#endif //ALGORITHMS_LINKEDLIST_H