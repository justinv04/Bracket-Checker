#include "DSList.h"
#include "DSStack.h"
#include <stdexcept>
#include <iostream>

    //      ---***<<< DSStackArray Definitions >>>***---

template <typename Object>
DSStackArray<Object>::DSStackArray() // defualt constructor
{
    size = 0; 
    capacity = 1000; // just in case
    array = new Object[capacity]; // create a new array of the size 'capacity'
}

template <typename Object>
DSStackArray<Object>::DSStackArray(const DSStackArray &other) // copy constructor
{
    size = other.size;
    capacity = other.capacity;
    array = new Object[capacity];
    for (size_t i = 0; i < capacity; i++) // copy over values
    {
        array[i] = other.array[i];
    }
}

template <typename Object>
DSStackArray<Object> &DSStackArray<Object>::operator=(const DSStackArray &other) // copy assignment operator
{
    if (this != &other) 
    {
        delete[] array; // 
        size = other.size;
        capacity = other.capacity;
        array = new Object[capacity];
        for (size_t i = 0; i < capacity; i++) 
        {
            array[i] = other.array[i];
        }
    }
    return *this;
}

template <typename Object>
DSStackArray<Object>::~DSStackArray() // destructor
{
    delete[] array; 
}

template <typename Object>
void DSStackArray<Object>::push(const Object &data) // add to the stack
{
    if (size == capacity) // if the array is full, resize it
    {
        Object *newArray = new Object[capacity * 2]; // double capacity to be sure
        for (size_t i = 0; i < capacity; i++) 
        {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
        capacity *= 2;
    }
    array[size++] = data;
}

template <typename Object>
bool DSStackArray<Object>::isEmpty() // checks if there are no objects in the stack
{
    return size == 0;
}

template <typename Object>
size_t DSStackArray<Object>::getSize() // returns # of objects in the stack
{
    return size;
}


template <typename Object>
Object DSStackArray<Object>::pop() // remove from the stack
{
    if (size == 0) 
    {
        return -1;
    }
    Object data = array[--size];
    array[size] = Object();
    return data;
}

template <typename Object>
Object DSStackArray<Object>::getTop() // get the top without removing it
{
    if (size == 0) 
    {
        return -1;
    }
    return array[size-1];
}

    //      ---***<<< DSStackList Definitions >>>***---

template <typename Object>
DSStackList<Object>::DSStackList() // default constructor
{
    list = DSList<Object>();
}

template <typename Object>
DSStackList<Object>::DSStackList(const DSStackList &other) // copy constructor
{
    list = other.list; // this works because DSList's copy assignment operator works
}

template <typename Object>
DSStackList<Object> &DSStackList<Object>::operator=(const DSStackList &other) // copy assignment operator
{
    if (this != &other) // copys the contents of the other list
    {
        list = other.list; 
    }
    return *this;
}

template <typename Object>
DSStackList<Object>::~DSStackList() // destructor
{
    list.clear(); // clears the list
}

template <typename Object>
void DSStackList<Object>::push(const Object &data) // add to the stack
{
    list.push_front(data); 
}

template <typename Object>
bool DSStackList<Object>::isEmpty() // bool for empty list
{
    return list.isEmpty(); 
}

template <typename Object>
Object DSStackList<Object>::pop() // remove from the stack
{
    if (list.isEmpty()) // handles case of an empty list
    {
        return -1; 
    }
    return list.pop_front(); 
}

template <typename Object>
Object DSStackList<Object>::getTop() 
{
    if (list.isEmpty()) 
    {
        return -1;
    }
    Object data = list.pop_front(); // take the data out
    list.push_front(data); // put the data back
    return data; // return the copy
}