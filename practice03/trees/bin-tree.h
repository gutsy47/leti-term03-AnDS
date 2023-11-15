#ifndef ADS_BIN_TREE_H
#define ADS_BIN_TREE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <stack>


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
        Node();
        explicit Node(int);

        int key;
        Node* left;
        Node* right;
    };
    Node *root{};

public:
    BinTree();
    explicit BinTree(std::string);
    ~BinTree();
    friend std::ostream& operator<< (std::ostream&, const BinTree&);
    void depthFirstSearch();

private:
    Node* parse(std::vector<std::string>&);
    void depthFirstSearchUtil(Node*);
    void deleteTree(Node*);
    void osVert(std::ostream&, const Node*, std::string prefix = "", bool isLeft = false) const; // Print from L to R
};



#endif //ADS_BIN_TREE_H
