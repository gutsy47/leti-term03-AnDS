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
 * Implement an Binary Tree with the depth-first search, output to ostream only functionality
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
    BinTree& operator= (const BinTree&);

    std::vector<int> depthFirstSearch();

private:
    Node* parse(std::vector<std::string>&);
    Node* copyTree(const Node*);

    void deleteTree(Node*);
    void osVert(std::ostream&, const Node*, std::string prefix = "", bool isLeft = false) const;

    void depthFirstSearchUtil(Node*, std::vector<int>&);
};


#endif //ADS_BIN_TREE_H
