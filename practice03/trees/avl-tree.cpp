#include "avl-tree.h"
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>


/// Node constructor
AVLTree::Node::Node(int k) {
    key = k;
    height = 1;
    left = nullptr;
    right = nullptr;
}


/// Tree constructor
AVLTree::AVLTree() {
    root = nullptr;
}


/// Tree constructor from vector of values
AVLTree::AVLTree(const std::vector<int> &values) {
    root = nullptr;
    for (const auto &el : values) insert(el);
}

/// Tree destructor
AVLTree::~AVLTree() {
    deleteTree(root);
}


/// Delete the nodes but not the tree
void AVLTree::clear() {
    deleteTree(root);
    root = nullptr;
}


/// Delete the tree recursively
void AVLTree::deleteTree(Node *head) {
    if (!head) return;

    deleteTree(head->left);
    deleteTree(head->right);

    delete head;
}


/// Return height if node exists else 0
unsigned char AVLTree::getHeight(Node *node) {
    return node ? node->height : 0;
}


/// Return the height of the tree
unsigned char AVLTree::height() const {
    return root->height;
}

/// Return leftHeight-rightHeight or zero if node doesn't exist
int AVLTree::getBalanceFactor(Node *head) {
    if (!head) return 0;
    return getHeight(head->left) - getHeight(head->right);
}


/// Update the height of the node
void AVLTree::Node::fixHeight() {
    unsigned char hLeft = getHeight(left);
    unsigned char hRight = getHeight(right);
    height = (hLeft > hRight ? hLeft : hRight) + 1;
}


/// Rotate the subtree to the right
AVLTree::Node* AVLTree::rotateRight(Node *head) {
    Node *newHead = head->left;
    head->left = newHead->right;
    newHead->right = head;
    head->fixHeight();
    newHead->fixHeight();
    return newHead;
}


/// Rotate the subtree to the left
AVLTree::Node* AVLTree::rotateLeft(Node *head) {
    Node *newHead = head->right;
    head->right = newHead->left;
    newHead->left = head;
    head->fixHeight();
    newHead->fixHeight();
    return newHead;
}


/// Insert new Node and return the new root
AVLTree::Node* AVLTree::insertUtil(Node *head, int k) {
    if (!head) {
        return new Node(k);
    }

    if (k < head->key) head->left = insertUtil(head->left, k);
    else if (k > head->key) head->right = insertUtil(head->right, k);

    head->fixHeight();
    int balanceFactor = getBalanceFactor(head);
    if (balanceFactor > 1) {
        if (k >= head->left->key) head->left = rotateLeft(head->left);
        return rotateRight(head);
    } else if (balanceFactor < -1) {
        if (k <= head->right->key) head->right = rotateRight(head->right);
        return rotateLeft(head);
    }

    return head;
}


/// Insert new Node with int k value to the tree
void AVLTree::insert(int k) {
    root = insertUtil(root, k);
}


/// Return Node object if found else nullptr
AVLTree::Node* AVLTree::searchUtil(Node *head, int k) {
    // !head means that there is no node, return nullptr
    if (!head || k == head->key) return head;

    if (k > head->key) return searchUtil(head->right, k);
    else return searchUtil(head->left, k);
}


/// Return true if node with int k value exists else false
bool AVLTree::find(int k) {
    return searchUtil(root, k) != nullptr;
}


/// Remove the Node with int k value and return the updated root
AVLTree::Node *AVLTree::removeUtil(Node *head, int k) {
    if (!head) return nullptr;

    if (k < head->key) head->left = removeUtil(head->left, k);
    else if (k > head->key) head->right = removeUtil(head->right, k);
    else {
        if (!head->left || !head->right) {
            // Node with one or no children
            Node *temp = head->left ? head->left : head->right;  // If true then right doesn't exist, else check right
            if (!temp) {        // No children
                temp = head;
                head = nullptr;
            } else {            // One child
                *head = *temp;
            }
            delete temp;
        } else {
            // Node with two children
            Node *temp = head->right;
            while (temp->left) temp = temp->left;
            head->key = temp->key;
            head->right = removeUtil(head->right, temp->key);
        }
    }

    if (!head) return nullptr;

    // Update the height
    head->height = 1 + std::max(getHeight(head->left), getHeight(head->right));

    // Check for balance violation and perform rotations
    int balance = getBalanceFactor(head);
    if (balance > 1 && getBalanceFactor(head->left) >= 0) {
        return rotateRight(head);
    }
    if (balance > 1 && getBalanceFactor(head->left) < 0) {
        head->left = rotateLeft(head->left);
        return rotateRight(head);
    }
    if (balance < -1 && getBalanceFactor(head->right) <= 0) {
        return rotateLeft(head);
    }
    if (balance < -1 && getBalanceFactor(head->right) > 0) {
        head->right = rotateRight(head->right);
        return rotateLeft(head);
    }

    return head;
}


/// Remove the Node with int k value and update the root if necessary
void AVLTree::remove(int k) {
    root = removeUtil(root, k);
}


/// Fill the vector with tree node keys using post-order traversal
void AVLTree::getVerticalOrder(const Node *head, std::vector<std::vector<int>> &verticalOrder, int depth = 0) const {
    if (!head) {
        verticalOrder[depth].push_back(9999);
        return;
    }

    getVerticalOrder(head->right, verticalOrder, depth + 1);
    verticalOrder[depth].push_back(head->key);
    getVerticalOrder(head->left, verticalOrder, depth + 1);
}


/**
 * Print the tree from up to down
 * @warning - Numbers must be in the range [-99, 999]
 * @warning - Extra branches will be displayed if bFactor != 0
 */
void AVLTree::osHor(std::ostream& os) const {
    if (!root) return;  // Nothing to print

    const std::string downL = "Ú";
    const std::string downR = "¿";
    const std::string horiz = "Ä";
    const std::string horUp = "Á";

    unsigned char h = root->height;                    // Max height
    unsigned short maxLine = short(pow(2, h - 1)) * 4; // Chars needed to display the last row
    unsigned short tab, prefix = 10;                   // Prefix will be recounted. First raw tab isn't needed

    std::vector<std::vector<int>> verticalOrder;
    verticalOrder.resize(h + 1);
    getVerticalOrder(root, verticalOrder);

    for (short i = 1; i <= h; ++i) {
        auto row = verticalOrder[i - 1];
        std::reverse(row.begin(), row.end());

        tab = prefix;                            // Chars between the nodes (-1 for empty field of 3-character keys)
        prefix = short(maxLine / pow(2, i)) - 1; // Chars before the print

        // Print branches after first Node
        if (i != 1) {
            os << std::string(prefix, ' '); // Chars before the print
            for (int j = 0; j < row.size() / 2; ++j) {
                std::cout << downL;                                   // "?"
                for (int l = 0; l < tab / 2; ++l) std::cout << horiz; // "?" (tab / 2) times
                std::cout << horUp;                                   // "?"
                for (int l = 0; l < tab / 2; ++l) std::cout << horiz; // "?" (tab / 2) times
                std::cout << downR << std::string(tab, ' ');          // "?"
            }
            os << std::endl;
        }

        // Print the values of the nodes
        if (prefix) os << std::string(prefix - 1, ' ');      // -1 for empty field of 3-char numbers
        for (auto &key: row) {
            unsigned char keyLength = std::to_string(key).length(); // Chars needed to display the number
            if (keyLength < 3) {                                    // Not 3 => add pre-space
                os << " ";
                keyLength++;  // Now number uses keyLength + 1 chars to be displayed
            }
            if (key == 9999) { // Empty Node output
                os << "   ";
                keyLength = 3;
            } else {
                os << key;
            }
            os << std::string(tab + 1 - keyLength, ' '); // Chars between
        }
        os << std::endl;
    }
}


/// Print the tree from left to right
void AVLTree::osVert(std::ostream &os, const Node *head, std::string prefix, bool isLeft) const {
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
std::ostream&operator<< (std::ostream &os, const AVLTree &tree) {
    if (tree.height() > 4) tree.osVert(os, tree.root);
    else tree.osHor(os);
    os << std::endl;
    return os;
}


/// Breadth First Traversal util
void AVLTree::breadthFirstUtil(AVLTree::Node *head) const {
    if (!head) return;

    std::queue<Node*> q;
    q.push(head);
    while (!q.empty()) {
        Node *curr = q.front();
        q.pop();

        std::cout << curr->key << ' ';

        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
}

/// Breadth First Traversal
void AVLTree::breadthFirstTraversal() const {
    breadthFirstUtil(root);
}


/// In Order Traversal util
void AVLTree::inOrderUtil(AVLTree::Node *head) const {
    if (!head) return;

    std::stack<Node*> s;
    Node *curr = head;
    while (curr || !s.empty()) {
        while (curr) {
            s.push(curr);
            curr = curr->left;
        }

        curr = s.top();
        s.pop();

        std::cout << curr->key << ' ';

        curr = curr->right;
    }
}


/// In Order Traversal
void AVLTree::inOrderTraversal() const {
    inOrderUtil(root);
}


/// Pre Order Traversal util
void AVLTree::preOrderUtil(AVLTree::Node *head) const {
    if (!head) return;

    std::stack<Node*> s;
    Node *curr = head;

    while (curr || !s.empty()) {
        while (curr) {
            std::cout << curr->key << ' ';

            s.push(curr);
            curr = curr->left;
        }

        curr = s.top();
        s.pop();

        curr = curr->right;
    }
}


/// Pre Order Traversal
void AVLTree::preOrderTraversal() const {
    preOrderUtil(root);
}


/// Post Order Traversal util
void AVLTree::postOrderUtil(AVLTree::Node *head) const {
    if (!head) return;

    std::stack<Node*> s;
    Node *curr = head;
    Node *last = nullptr;

    while (curr || !s.empty()) {
        while (curr) {
            s.push(curr);
            curr = curr->left;
        }

        Node *top = s.top();
        if (!top->right || top->right == last) {
            std::cout << top->key << ' ';

            s.pop();
            last = top;
        } else {
            curr = top->right;
        }
    }
}


/// Post Order Traversal
void AVLTree::postOrderTraversal() const {
    postOrderUtil(root);
}