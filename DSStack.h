#ifndef DSStack_H
#define DSStack_H
#include "DSStack.h"
#include "DSList.h"

template <typename Object>
class DSStackArray
{
    private:
        size_t size; // # of objects in the array
        size_t capacity; // size of the array
        Object *array; // array to store values
    public:
        DSStackArray();
        DSStackArray(const DSStackArray &other);
        DSStackArray &operator=(const DSStackArray &other);
        ~DSStackArray();
        void push(const Object &data); // add to the stack
        bool isEmpty(); // check if stack is empty
        size_t getSize(); // # of brackets
        Object pop(); // remove from the stack
        Object getTop(); // get the top of the stack without removing it
};

template <typename Object>
class DSStackList
{
    private:
        DSList<Object> list; // DSList to store objects
    public:
        DSStackList();
        DSStackList(const DSStackList &other);
        DSStackList &operator=(const DSStackList &other);
        ~DSStackList();
        void push(const Object &data);
        bool isEmpty();
        Object pop();
        Object getTop();
};
#endif