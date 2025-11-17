#include "BST.h"
#include <iostream>

using namespace std;

// Construtor do no
Node::Node(int value) : key(value), left(NULL), right(NULL) {}

// Construtor da arvore inicia raiz como vazia
BST::BST() : root(NULL) {}

// Insercao recursiva na BST
Node* BST::insertRecursive(Node* node, int key) {
    if (node == NULL) {
        return new Node(key); // Cria novo no se posicao correta for encontrada
    }
    
    if (key < node->key) {
        node->left = insertRecursive(node->left, key);  // Insere na subarvore esquerda
    } else if (key > node->key) {
        node->right = insertRecursive(node->right, key); // Insere na subarvore direita
    }
    
    return node; // Retorna o proprio no
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
        return -1; // Indicador de que a arvore esta vazia
    }
    
    if (node->right == NULL) {
        return node->key; // O maior esta no no mais a direita
    }
    
    return findMaxRecursive(node->right);
}

int BST::findMax() {
    return findMaxRecursive(root);
}

// Limpa a arvore
void BST::clear() {
    root = NULL;
}

// Carrega valores padrao na BST
void BST::loadDefaultValues() {
    clear(); // Reinicia a arvore
    
    int valores[] = {20, 5, 12, 36, 27, 45, 9, 2, 6, 17, 40};
    int tamanho = sizeof(valores) / sizeof(valores[0]);
    
    for (int i = 0; i < tamanho; i++) {
        insert(valores[i]); // Insere cada numero
    }
    cout << "  Valores iniciais carregados!\n";
}
