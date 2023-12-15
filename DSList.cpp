#include <cstddef>
#include <stdexcept>
#include "DSList.h"

// default constructor
template <typename Object>
DSList<Object>::DSList() 
{
    size = 0;
    head = nullptr;
}

// copy constructor
template <typename Object>
DSList<Object>::DSList(const DSList &other)
{
    size = 0;
    head = nullptr;
    Node* ptr = other.head;
    while (ptr != nullptr) 
    {
        push_back(ptr->data);
        ptr = ptr->next;
    }
}

// copy assignment operator
template <typename Object>
DSList<Object>& DSList<Object>::operator=(const DSList &other)
{
    if (this != &other) 
    {
        clear();
        Node* ptr = other.head;
        while (ptr != nullptr) // loops through the other list with pointers
        {
            push_back(ptr->data);
            ptr = ptr->next;
        }
    }
    return *this;
}

// destructor
template <typename Object>
DSList<Object>::~DSList()
{
    clear(); // does everything but delete the actual DSList object
}

// returns size
template <typename Object>
size_t DSList<Object>::getSize()
{
    return size;
}

// returns if empty
template <typename Object>
bool DSList<Object>::isEmpty()
{
    return head == nullptr; 
}

// clears the list
template <typename Object>
void DSList<Object>::clear()
{
    while (head != nullptr) // deallocates the list pointer by pointer
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    size = 0; 
}

// returns the index of the value searched for, -1 if not found
template <typename Object>
long int DSList<Object>::find(const Object &data)
{
    long int index = -1;
    Node* ptr = head;
    for (size_t i = 0; i < size && ptr != nullptr; i++) // for statement handles if pointer is null
    {
        if (ptr->data == data) 
        {
            index = i;
            break;
        }
        ptr = ptr->next;
    }
    return index;
}

// adds to the front
template <typename Object>
void DSList<Object>::push_front(const Object &data)
{
    Node* newNode = new Node(data, nullptr);
    size++;
    Node* temp = head;
    newNode->next = temp;
    head = newNode;
}

// adds to the back
template <typename Object>
void DSList<Object>::push_back(const Object &data)
{
    Node* newNode = new Node(data, nullptr);
    size++;
    if (isEmpty()) 
        head = newNode;
    else
    {
        Node* ptr = head;
        while (ptr->next != nullptr) 
        {
            ptr = ptr->next;
        }
        ptr->next = newNode;
    }
}

// removes and returns front
template <typename Object>
Object DSList<Object>::pop_front()
{
    if(isEmpty()) // handle if list is empty
    {
        throw std::out_of_range("List is empty!");
    }
    Object frontData = head->data;
    Node* temp = head;
    head = temp->next;
    delete temp;
    size--;
    return frontData;
}

// removes and returns back
template <typename Object>
Object DSList<Object>::pop_back() 
{
    if (isEmpty()) 
    {
        throw std::out_of_range("List is empty!");
    }
    Node* prev = nullptr; // the node right in front of
    Node* temp = head; // the tail
    while (temp->next != nullptr) // loop through to the end
    {
        prev = temp;
        temp = temp->next;
    }
    Object removedData = temp->data; // grab the back
    prev->next = nullptr; // cut off the tail
    delete temp; // delete the tail
    size--; 
    return removedData; // return the data
}

