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


/**
 * Deep copy constructor
 * @param[in] other - list from which the copy is taken
 */
List::List(const List& other) {
    _head = nullptr;
    _tail = nullptr;
    _size = 0;

    struct Node *current = other._head;
    while (current) {
        append(current->value);
        current = current->next;
    }
}


/// Free the memory allocated for a DLL
List::~List() {
    clear();
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


/// Get node by it's index via [] operator
struct Node * List::operator[](int index) {
    return get(index);
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


/// Reverse the list
void List::reverse() {
    // Accessing an element is a difficult operation for lists,
    // so swap pointers not the values themselves
    Node *current = _head;
    Node *prev = nullptr;
    Node *next;

    // Swap pointers
    while (current) {
        next = current->next;
        current->next = prev;
        current->prev = next;
        prev = current;
        current = next;
    }

    // And update head and tail
    std::swap(_head, _tail);
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


/// Get node by it's index
struct Node * List::get(int index) {
    if (isEmpty()) {
        std::cout << "IndexError: The list is empty\n";
        return nullptr;
    } else if (abs(index) > getSize()) {
        std::cout << "IndexError: Index out of range\n";
        return nullptr;
    } else if (index < 0) {
        index = int(getSize()) + index;
    }

    // Traverse to the index or throw an error
    struct Node *node = _head;
    for (unsigned i = 0; i < index; ++i) {
        if (!node->next) {
            std::cout << "IndexError: Index out of range\n";
            return nullptr;
        }
        node = node->next;
    }

    return node;
}


/// Return index if element found else -1
int List::find(int value) {
    if (isEmpty()) return -1;

    // Traverse while not found
    struct Node *node = _head;
    for (int i = 0; i < _size; ++i) {
        if (node->value == value) return i;
        if (!node->next) return -1;
        node = node->next;
    }
}


/// Add element to the specified position
void List::insert(unsigned index, int value) {
    struct Node * found = get(int(index));

    // IndexError
    if (!found) return;

    // Insert
    auto *newNode = new struct Node;
    newNode->value = value;
    newNode->prev = found->prev;
    newNode->next = found;
    if (newNode->prev) newNode->prev->next = newNode;
    if (newNode->next) newNode->next->prev = newNode;
    if (index == 0) _head = newNode;
}


/// Remove element by it's index
void List::remove(unsigned index) {
    if (isEmpty()) return;

    // Find
    struct Node *found = get(int(index));
    if (!found) return;

    // Delete
    found->prev ? found->prev->next = found->next : _head = found->next; // Update prev node or update the head if null
    found->next ? found->next->prev = found->prev : nullptr;             // Update next node or list deleted if null
    delete found;
    _size--;
}


/// Swap two nodes by their indexes
void List::swap(unsigned i1, unsigned i2) {
    // (Empty || 1 element || Same indexes) => no swap
    if (isEmpty() || _head == _tail || i1 == i2) return;

    // 1st index less than 2nd one
    if (i1 > i2) std::swap(i1, i2);

    // Get nodes. If not found -> return
    struct Node *node1 = get(int(i1));
    struct Node *node2 = get(int(i2));
    if (!node1 || !node2) return;

    // Head and tail cases
    if (node1 == _head && node2 == _tail) {
        _head = node2;
        _tail = node1;
    } else if (node1 == _head) {
        _head = node2;
    } else if (node2 == _tail) {
        _tail = node1;
    }

    // Update 'next' elements and update the 'prev' pointers of the 'next' nodes if exist
    struct Node *temp = node1->next;
    node1->next = node2->next;
    node2->next = temp;
    if (node1->next) node1->next->prev = node1;
    if (node2->next) node2->next->prev = node2;

    // Update 'prev' elements and update the 'next' pointers of the 'prev' nodes if exist
    temp = node1->prev;
    node1->prev = node2->prev;
    node2->prev = temp;
    if (node1->prev) node1->prev->next = node1;
    if (node2->prev) node2->prev->next = node2;
}


/// Return size of the list
unsigned List::getSize() const {
    return _size;
}


/// Return false if list is empty else true
bool List::isEmpty() const {
    return _size == 0;
}
