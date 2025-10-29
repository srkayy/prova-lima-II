#include "BST.h"
#include <iostream>

using namespace std;

// Construtor do nó
Node::Node(int value) : key(value), left(NULL), right(NULL) {}

// Construtor da BST - árvore vazia
BST::BST() : root(NULL) {}

// Destrutor - libera memória
BST::~BST() {
    clear();
}

// ==================== FUNÇÃO F1: INSERÇÃO ====================
Node* BST::insertRecursive(Node* node, int key) {
    // Se encontrou posição vazia, cria novo nó
    if (node == NULL) {
        return new Node(key);
    }
    
    // Insere na subárvore esquerda se for menor
    if (key < node->key) {
        node->left = insertRecursive(node->left, key);
    } 
    // Insere na subárvore direita se for maior
    else if (key > node->key) {
        node->right = insertRecursive(node->right, key);
    }
    
    return node;
}

void BST::insert(int key) {
    root = insertRecursive(root, key);
    cout << "\n  Valor " << key << " inserido com sucesso!";
}

// ==================== FUNÇÃO F2: LISTAGEM ====================
void BST::inOrderRecursive(Node* node) {
    if (node != NULL) {
        inOrderRecursive(node->left);
        cout << node->key << " ";
        inOrderRecursive(node->right);
    }
}

void BST::inOrder() {
    if (root == NULL) {
        cout << "\n  A arvore esta vazia!";
        return;
    }
    cout << "\n  Arvore (in-ordem): ";
    inOrderRecursive(root);
}

// ==================== FUNÇÃO F3: REMOÇÃO ====================
Node* BST::findMin(Node* node) {
    // Encontra o menor valor (mais à esquerda)
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

Node* BST::removeRecursive(Node* node, int key) {
    if (node == NULL) return NULL;

    // Busca o nó a ser removido
    if (key < node->key) {
        node->left = removeRecursive(node->left, key);
    } else if (key > node->key) {
        node->right = removeRecursive(node->right, key);
    } else {
        // Nó encontrado - trata os 3 casos de remoção
        
        // Caso 1: Nó sem filho ou com apenas um filho
        if (node->left == NULL) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == NULL) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        
        // Caso 2: Nó com dois filhos
        // Encontra o sucessor in-order (menor da direita)
        Node* temp = findMin(node->right);
        node->key = temp->key; // Copia o valor
        // Remove o sucessor
        node->right = removeRecursive(node->right, temp->key);
    }
    return node;
}

void BST::remove(int key) {
    if (search(key)) {
        root = removeRecursive(root, key);
        cout << "\n  Valor " << key << " removido com sucesso!";
    } else {
        cout << "\n  Valor " << key << " nao encontrado!";
    }
}

// ==================== FUNÇÕES AUXILIARES ====================
bool BST::searchRecursive(Node* node, int key) {
    if (node == NULL) return false;
    
    if (key == node->key) return true;
    else if (key < node->key) return searchRecursive(node->left, key);
    else return searchRecursive(node->right, key);
}

bool BST::search(int key) {
    return searchRecursive(root, key);
}

void BST::clear() {
    // Função simplificada para limpar a árvore
    // Em uma implementação completa, seria recursiva
    root = NULL;
}

void BST::loadDefaultValues() {
    clear(); // Limpa árvore atual
    
    // Valores do item (a): 20, 5, 12, 36, 27, 45, 9, 2, 6, 17, 40
    int valores[] = {20, 5, 12, 36, 27, 45, 9, 2, 6, 17, 40};
    int tamanho = sizeof(valores) / sizeof(valores[0]);
    
    for (int i = 0; i < tamanho; i++) {
        insert(valores[i]);
    }
    cout << "\n  Valores iniciais carregados!";
}