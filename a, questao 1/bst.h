#ifndef BST_H
#define BST_H

class Node {
public:
    int key;        // Valor do nó
    Node* left;     // Ponteiro para filho esquerdo
    Node* right;    // Ponteiro para filho direito
    
    Node(int value); // Construtor
};

class BST {
private:
    Node* root;     // Raiz da árvore

    // Métodos auxiliares recursivos
    Node* insertRecursive(Node* node, int key);
    void inOrderRecursive(Node* node);
    Node* findMin(Node* node);
    Node* removeRecursive(Node* node, int key);
    bool searchRecursive(Node* node, int key);

public:
    BST();          // Construtor
    ~BST();         // Destrutor
    
    // Funções principais solicitadas
    void insert(int key);       // F1: Inserção
    void inOrder();             // F2: Listagem
    void remove(int key);       // F3: Remoção
    bool search(int key);       // Busca auxiliar
    
    // Funções extras úteis
    void clear();               // Limpar árvore
    void loadDefaultValues();   // Carregar valores do item (a)
};

#endif