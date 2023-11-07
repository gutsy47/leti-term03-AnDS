#include "bin-tree.h"
#include <iostream>
#include <string>


/// Node constructor
BinTree::Node::Node(int k) {
    key = k;
    left = nullptr;
    right = nullptr;
}


/// Tree constructor
BinTree::BinTree() {
    root = nullptr;
}


/// Tree destructor
BinTree::~BinTree() {
    deleteTree(root);
}


/// Delete the tree recursively
void BinTree::deleteTree(Node *head) {
    if (!head) return;

    deleteTree(head->left);
    deleteTree(head->right);

    delete head;
}


/// Print the tree from left to right
void BinTree::osVert(std::ostream &os, const Node *head, std::string prefix, bool isLeft) const {
    if (!head) return;

    const std::string vert = "³   ";
    const std::string up = "ÚÄ>";
    const std::string mid = "ÄÄ>";
    const std::string down = "ÀÄ>";

    // Print right path
    std::string rPrefix = prefix + (isLeft ? vert : "    ");
    osVert(os, head->right, rPrefix, false);

    // Print value
    if (head->key == root->key) os << mid << head->key << std::endl;
    else os << prefix << (isLeft ? down : up) << head->key << std::endl;

    // Print left path
    if (prefix.empty()) prefix += "    ";
    else prefix += (isLeft ? "    " : vert);
    osVert(os, head->left, prefix, true);
}


/// Print the tree to the output stream
std::ostream&operator<< (std::ostream &os, const BinTree &tree) {
    tree.osVert(os, tree.root);
    os << std::endl;
    return os;
}