#include "BST.h"
#include <iostream>

using namespace std;

Node::Node(int value) : key(value), left(NULL), right(NULL) {}

BST::BST() : root(NULL) {}

Node* BST::insertRecursive(Node* node, int key) {
    if (node == NULL) {
        return new Node(key);
    }
    
    if (key < node->key) {
        node->left = insertRecursive(node->left, key);
    } else if (key > node->key) {
        node->right = insertRecursive(node->right, key);
    }
    
    return node;
}

void BST::insert(int key) {
    root = insertRecursive(root, key);
    cout << "  Valor " << key << " inserido com sucesso!\n";
}

void BST::inOrderRecursive(Node* node) {
    if (node != NULL) {
        inOrderRecursive(node->left);
        cout << node->key << " ";
        inOrderRecursive(node->right);
    }
}

void BST::inOrder() {
    if (root == NULL) {
        cout << "  A arvore esta vazia!";
        return;
    }
    cout << "  Arvore (in-ordem): ";
    inOrderRecursive(root);
}

int BST::findMaxRecursive(Node* node) {
    if (node == NULL) {
        return -1;
    }
    
    if (node->right == NULL) {
        return node->key;
    }
    
    return findMaxRecursive(node->right);
}

int BST::findMax() {
    return findMaxRecursive(root);
}

void BST::clear() {
    root = NULL;
}

void BST::loadDefaultValues() {
    clear();
    
    int valores[] = {20, 5, 12, 36, 27, 45, 9, 2, 6, 17, 40};
    int tamanho = sizeof(valores) / sizeof(valores[0]);
    
    for (int i = 0; i < tamanho; i++) {
        insert(valores[i]);
    }
    cout << "  Valores iniciais carregados!\n";
}