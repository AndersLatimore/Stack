//
//  Stack.h
//  stackEx
//
//  Created by Anders Akesson on 1/26/13.
//  Copyright (c) 2013 Anders Akesson. All rights reserved.
//

#ifndef __stackEx__Stack__
#define __stackEx__Stack__

#include <iostream>
#include "List.h"
using namespace std;

template <typename T>
class Stack
{
private:
    List<T> *newList; // container
    int nrOfItems;
public:
    Stack();
    void push(T item);
    void pop();
    T* peek();
    bool isEmpty();
    virtual ~Stack();
    
};

#endif /* defined(__stackEx__Stack__) */

template<typename T>
Stack<T>::Stack()
{
    newList = new List<T>;
    this->nrOfItems = 0;
}
template<typename T>
void Stack<T>::push(T item)
{
    newList->insertFirst(item);
    this->nrOfItems++;
}
template<typename T>
void Stack<T>::pop()
{
    if (isEmpty() == true)
    {
        cout << "Stack is empty. " << endl;
        return;
    }
    else
    {
        newList->removeFirst();
        this->nrOfItems--;
    }
}
template<typename T>
T* Stack<T>::peek()
{
    T* item = newList->elementAt(0);
    return item;
}
template<typename T>
bool Stack<T>::isEmpty()
{
    bool isEmpty = true;
    
    if (newList->size() > 1)
    {
        isEmpty = false;
    }
    return isEmpty;
}
template<typename T>
Stack<T>::~Stack()
{
    delete newList;
}