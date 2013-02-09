//
//  List.h
//  listTemplateEx
//
//  Created by Anders Akesson on 1/24/13.
//  Copyright (c) 2013 Anders Akesson. All rights reserved.
//

#ifndef listTemplateEx_List_h
#define listTemplateEx_List_h

#include <iostream>
#include <exception>
#include <cerrno>

using namespace std;

template <typename T>
class List
{
    
private:
    
	class Node
	{
	public:
		T item;
		Node *next;
		Node(T item)
        {
            this->item = item;
            this->next = NULL;
        }
		~Node() {}
	};
	
	Node *first;
	int nrOfNodes;
    
    struct MyException : public exception
    {
        const char * what () const throw ()
        {
            return "ERROR. The program has thrown a C++ Exception";
        }
    };
    
public:
	List();
	List(const List<T>& list);
	virtual ~List();
	List& operator=(const List<T>& list);
	void insertLast(T item);
	void insertAt(int pos, T item);
	void insertFirst(T item);
	T* elementAt(int pos) const;
	bool removeFirst();
	bool removeLast();
	bool removeAt(int pos);
	int size() const;
    void print() const;
    void clear();
    
};

template <typename T>
List<T>::List()
{
    this->first = NULL;
	this->nrOfNodes = 0;
}
template <typename T>
List<T>::List(const List<T>& list)
{
    this->first = NULL;
    this->nrOfNodes = 0;
    Node* copyList = list.first;
    
    while (copyList != NULL)
    {
        insertLast(copyList->value);
        copyList = copyList->next;
    }
}
template <typename T>
List<T>& List<T>::operator=(const List<T>& list)
{
    if(&list == this)
        return *this;
    
    if (first != NULL)
    {
        clear();
    }
    
    this->first = NULL;
    this->nrOfNodes = 0;
    Node* copyList = list.first;
    
    while (copyList != NULL)
    {
        insertLast(copyList->item);
        copyList = copyList->next;
    }
    return *this;
}
template <typename T>
void List<T>::insertLast(T item)
{
    Node *e = new Node(item);
    Node* walker = this->first;
    
    if (this->first != NULL)
    {
        while (walker->next != NULL)
        {
            walker = walker->next;
        }
        walker->next = e;
    }
    else
    {
        this->first = e;
    }
    
    this->nrOfNodes++;
}
template <typename T>
void List<T>::insertAt(int pos, T item)
{
    if (pos <= 0)
    {
        insertFirst(item);
    }
    
    else
    {
        if (pos > this->nrOfNodes || pos < 1)
        {
            insertLast(item);
        }
        else
        {
            Node* e = new Node(item);
            Node* walker = this->first;
            
            int index = 0;
            
            while (index < pos-1)
            {
                walker = walker->next;
                index++;
            }
            e->next = walker->next;
            walker->next = e;
            this->nrOfNodes++;
        }
    }
    
}
template <typename T>
void List<T>::insertFirst(T item)
{
    Node* e = new Node(item);
    e->next = this->first;
    this->first = e;
    this->nrOfNodes++;
}
template <typename T>
T* List<T>::elementAt(int pos) const
{
    if(this->nrOfNodes == 0)
        throw MyException();
    
    T* result = NULL;
    
    if (this->first != NULL)
    {
        
        if (pos > this->nrOfNodes)
        {
            throw MyException();
        }
        
        else if (this->first->next == NULL  || pos < 1)
        {
            result = &first->item;
        }
        
        else
        {
            Node* walker = this->first;
            
            int index = 0;
            
            while (walker != NULL && index != pos)
            {
                walker = walker->next;
                result = &walker->item;
                index++;
            }
        }
    }
    
    return result;
}
template <typename T>
bool List<T>::removeFirst()
{
    bool result = false;
    
    if (this->first != NULL)
    {
        Node* walker = this->first;
        result = true;
        this->first = this->first->next;
        delete walker;
        this->nrOfNodes--;
    }
    
    return result;
    
}
template <typename T>
bool List<T>::removeLast()
{
    bool result = false;
    
    if(!this->first) return result;
    
    if (this->first != NULL)
    {
        if (this->first->next == NULL)
        {
            removeFirst();
        }
        else if(this->first != NULL)
        {
            Node* walker = this->first;
            Node* previous;
            result = true;
            
            while (walker->next != NULL)
            {
                previous = walker;
                walker = walker->next;
            }
            if(walker)
            {
                previous->next = walker->next;
                delete walker;
            }
            this->nrOfNodes--;
        }
    }
    return result;
}
template <typename T>
bool List<T>::removeAt(int pos)
{
    bool result = false;
    
    if (pos <= 0)
    {
        removeFirst();
    }
    
    else
    {
        if (this->nrOfNodes < 1 || pos > this->nrOfNodes)
        {
            return result;
        }
        else
        {
            Node* walker = this->first;
            Node* previous;
            int index = 0;
            
            while (walker != NULL && index != pos)
            {
                previous = walker;
                result = true;
                walker = walker->next;
                index++;
            }
            if(walker)
            {
                previous->next = walker->next;
                delete walker;
            }
            
            this->nrOfNodes--;
        }
    }
    
    return result;
}
template <typename T>
int List<T>::size() const
{
    return this->nrOfNodes;
}
template <typename T>
void List<T>::print() const
{
    if (this->size() <= 0)
    {
        cout << "Nothing added. " << endl;
    }
    
    else
    {
        Node* walker = this->first;
        
        while(walker != NULL)
        {
            cout << walker->item << "\t";
            walker = walker->next;
        }
    }
}
template <typename T>
void List<T>::clear()
{
    Node* walker = this->first;
    
    if(this->nrOfNodes < 1)
    {
        while(walker != NULL)
        {
            Node* garbage = walker;
            walker = walker->next;
            delete garbage;
        }
    }
}
template <typename T>
List<T>::~List()
{
    clear();
}
#endif


