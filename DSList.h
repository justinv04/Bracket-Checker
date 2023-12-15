#ifndef DSList_H
#define DSList_H
#include <cstddef>

template <typename Object>
class DSList
{
    private:
    size_t size; // # of objects in the list
    struct Node
    {
        Object data;
        Node *next;

        Node(const Object &d = Object{}, Node *n = nullptr) : data{d}, next{n} {};
    };
    Node *head;

    public:
    DSList(); // default constructor
    DSList(const DSList &other); // copy constructor
    DSList &operator=(const DSList &other); // copy assignment operator
    ~DSList(); // destructor
    size_t getSize(); // returns size
    bool isEmpty(); // returns if empty
    void clear(); // clears the list
    long int find(const Object &data); // returns the index of the value searched for, -1 if not found
    void push_front(const Object &data); // adds to the front
    void push_back(const Object &data); // adds to the back
    Object pop_front(); // removes and returns front
    Object pop_back(); // removes and returns back
};

#endif
