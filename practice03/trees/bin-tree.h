#ifndef ADS_BIN_TREE_H
#define ADS_BIN_TREE_H

#include <iostream>
#include <fstream>
#include <vector>


/**
 * @class BinTree
 * @brief Implementation of Binary Tree
 * Implement an Binary Tree with the following functionality:
 * left or right insertion and depth-first search, output to ostream
 * @example main.cpp
 */
class BinTree {
private:
    class Node {
    public:
        explicit Node(int);

        int key;
        Node* left;
        Node* right;
    };
    Node *root;

public:
    BinTree();
    ~BinTree();
    friend std::ostream& operator<< (std::ostream&, const BinTree&);
    void depthFirstSearch();

private:
    void depthFirstSearchUtil(Node*);
    void deleteTree(Node*);
    void osVert(std::ostream&, const Node*, std::string prefix = "", bool isLeft = false) const; // Print from L to R
};



#endif //ADS_BIN_TREE_H
