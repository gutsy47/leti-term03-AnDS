#include "stack.h"

#include <iostream>


/// Print the stack
std::ostream& operator<< (std::ostream& os, const Stack& stack) {
    for (const auto& it : stack.items)
        std::cout << it << ' ';
    return os;
}


/// Add element to the end of the stack
void Stack::push(std::string &value) {
    items.push_front(value);
    size++;
}


/// Return top item and remove it from stack
std::string Stack::pop() {
    if (isEmpty()) return "";
    std::string item = items.front();
    items.pop_front();
    size--;
    return item;
}


/// Return top item without removing it
std::string * Stack::top() {
    if (isEmpty()) return nullptr;
    return &items.front();
}


/// Return size of the stack
unsigned Stack::getSize() const {
    return size;
}


/// Return false if stack is empty else true
bool Stack::isEmpty() const {
    return items.empty();
}