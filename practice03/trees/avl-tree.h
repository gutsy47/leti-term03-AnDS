#ifndef INC_02_TREE_H
#define INC_02_TREE_H

#include <iostream>
#include <fstream>
#include <vector>


/**
 * @class Tree
 * @brief Implementation of AVL-Tree
 * Implement an AVL-Tree with the following functionality:
 * insert, search, delete node/tree, output to ostream
 * @example main.cpp
 */
class AVLTree {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;
        unsigned char height;

        explicit Node(int);
    };
    Node *root;

public:
    void insert(int);
    Node* search(int);
    void deleteNode(int);
    void print(bool isPrintVertical = false, std::ostream &outStream = std::cout) const;
    void clear();
    AVLTree() : root(nullptr) {}

private:
    void getVerticalOrder(const Node*, std::vector<std::vector<int>>&, int) const;
    void printHorizontal(const Node*) const;
    void printVertical(Node*, int, std::ostream &outStream = std::cout, std::string prefix = "", bool isLeft = false) const;
    static unsigned char height(Node*);
    static void fixHeight(Node*);
    static Node* rotateRight(Node*);
    static Node* rotateLeft(Node*);
    static int getBalanceFactor(Node*);
    Node* _insert(Node*, int);
    Node* _search(Node*, int);
    Node* _deleteNode(Node*, int);
    void deleteTree(Node*);
};

#endif //INC_02_TREE_H
