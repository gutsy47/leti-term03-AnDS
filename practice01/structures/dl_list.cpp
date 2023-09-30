#include "dl_list.h"

#include <iostream>


/// Default constructor. Size = 0, head & tail = nullptr
List::List() = default;


/**
 * Create doubly-linked list filled with def. value
 * @param[in] size - amount of nodes (def. = 1, size > 0)
 * @param[in] value - default value (def. = 0)
 */
List::List(unsigned size, int value) {
    if (size == 0) return;  // Empty list

    auto *current = new struct Node;
    struct Node *prev = nullptr;
    _head = current;

    // Create DLL starting from the head node
    for (int i = 0; i < size; ++i) {
        _tail = current;
        current->value = value + i;
        current->prev = prev;

        if (prev) prev->next = current;
        prev = current;

        current = new struct Node;
    }
    current->next = nullptr;
    _size = size;
}


/**
 * Create doubly-linked list filled with given numbers
 * @param[in] size - amount of nodes (size  > 0)
 * @param[in] values - int values of list
 */
List::List(unsigned size, const int *values) {
    if (size == 0) return;  // Empty list

    auto *current = new struct Node;
    struct Node *prev = nullptr;
    _head = current;

    // Create & fill the DLL
    for (int i = 0; i < size; ++i) {
        _tail = current;
        current->value = *(values + i);
        current->prev = prev;

        if (prev) prev->next = current;
        prev = current;

        current = new struct Node;
    }
    current->next = nullptr;
    _size = size;
}


/// Free the memory allocated for a DLL
List::~List() {
    clear();
    delete _head;
    delete _tail;
}


/// Assignment operator
List& List::operator= (const List& rhs) {
    // Self-assignment handler
    if (this == &rhs) return *this;

    // Clear the existing list
    clear();

    // Copy nodes from rhs to this list
    Node* current = rhs._head;
    while (current) {
        append(current->value);
        current = current->next;
    }

    return *this;
}

/// Print the list
std::ostream& operator<< (std::ostream& os, const List& list) {
    for (struct Node *temp = list._head; temp; temp = temp->next)
        os << temp->value << ' ';
    return os;
}


/// Clear the list. Set head & tail to nullptr
void List::clear() {
    while (_head) {
        struct Node *temp = _head;
        _head = _head->next;
        delete temp;
    }
    _head = nullptr;
    _tail = nullptr;
    _size = 0;
}


/// Add element to the end of the list
void List::append(int value) {
    auto *newNode = new struct Node;
    newNode->value = value;
    newNode->next = nullptr;

    if (isEmpty()) {  // List empty. Set both head and tail to the new node
        _head = newNode;
        _tail = newNode;
    } else {          // List is not empty. Update the tail
        _tail->next = newNode;
        newNode->prev = _tail;
        _tail = newNode;
    }

    _size++;
}


/// Return false if list is empty else true
bool List::isEmpty() const {
    return _size == 0;
}
