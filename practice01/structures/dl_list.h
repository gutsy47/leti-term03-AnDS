#ifndef PRACTICE01_DL_LIST_H
#define PRACTICE01_DL_LIST_H

#include <iostream>

/// Node structure represents a node in a Doubly-Linked List
struct Node {
    int value = 0;
    struct Node *next = nullptr;
    struct Node *prev = nullptr;
};


class List {
public:
    // Constructors and destructor
    List();
    explicit List(unsigned size, int value = 0);
    explicit List(unsigned, const int*);
    ~List();

    // Operators
    List& operator= (const List&);
    friend std::ostream& operator<< (std::ostream&, const List&);

    // Methods
    void clear();
    void append(int);
    [[nodiscard]] bool isEmpty() const;

private:
    struct Node *_head = nullptr;
    struct Node *_tail = nullptr;
    unsigned _size = 0;
};


#endif //PRACTICE01_DL_LIST_H
