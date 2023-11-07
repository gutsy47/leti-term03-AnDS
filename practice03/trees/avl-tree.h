#ifndef ADS_AVL_TREE_H
#define ADS_AVL_TREE_H

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
    class Node {
    public:
        explicit Node(int);

        int key;
        Node* left;
        Node* right;
        unsigned char height;

        void fixHeight();
    };
    Node *root;

public:
    // Constructors and destructors
    AVLTree();    // Constructor
    ~AVLTree();   // Destructor
    void clear(); // Delete the nodes but not the tree

    // Accessors
    [[nodiscard]] unsigned char height() const;

    // Friends
    friend std::ostream& operator<< (std::ostream&, const AVLTree&);

    // Methods
    void insert(int);
    bool find(int);
    void remove(int);

private:
    // Balance utils
    static unsigned char getHeight(Node*); // Return height if (node != nullptr) else zero
    int getBalanceFactor(Node*);           // Return factor if (node != nullptr) else zero
    Node* rotateRight(Node*);
    Node* rotateLeft(Node*);

    // Methods' utils
    Node* insertUtil(Node*, int);
    Node* searchUtil(Node*, int);
    Node* removeUtil(Node*, int);
    void deleteTree(Node*);

    // Output stream utils
    void getVerticalOrder(const Node*, std::vector<std::vector<int>>&, int) const; // PrintHorizontal util
    void osHor(std::ostream&) const; // Print from U to D
    void osVert(std::ostream&, const Node*, std::string prefix = "", bool isLeft = false) const; // Print from L to R
};

#endif //ADS_AVL_TREE_H
