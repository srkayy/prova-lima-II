#ifndef BST_H
#define BST_H

class Node {
public:
    int key;
    Node* left;
    Node* right;
    
    Node(int value);
};

class BST {
private:
    Node* root;

    Node* insertRecursive(Node* node, int key);
    void inOrderRecursive(Node* node);
    int findMaxRecursive(Node* node);

public:
    BST();
    void insert(int key);
    void inOrder();
    int findMax();
    void clear();
    void loadDefaultValues();
};

#endif