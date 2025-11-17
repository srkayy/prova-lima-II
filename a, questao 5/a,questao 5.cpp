#include <iostream>
#include <cstdlib> 
using namespace std;

class Node {
public:
    int data;         
    Node* left;          // Ponteiro para filho esquerdo
    Node* right;         // Ponteiro para filho direito

    Node(int val) {
        data = val;
        left = NULL;
        right = NULL;
    }
};

class BST {
private:
    Node* root;  // Raiz da arvore

    // Funcao recursiva para inserir um valor na BST
    Node* insert(Node* node, int val) {
        if (node == NULL)
            return new Node(val); // Cria novo no se chegar ao fim
        if (val < node->data)
            node->left = insert(node->left, val);  // Insere na esquerda
        else if (val > node->data)
            node->right = insert(node->right, val); // Insere na direita
        return node;
    }

    // Verifica se a arvore eh cheia (todos os nos possuem 0 ou 2 filhos)
    bool isFull(Node* node) {
        if (node == NULL)
            return true; // Arvore vazia eh considerada cheia
        if (node->left == NULL && node->right == NULL)
            return true; 
        if (node->left != NULL && node->right != NULL)
            return isFull(node->left) && isFull(node->right); // Verifica recursivamente
        return false; // Caso tenha apenas 1 filho
    }

    // Percurso em ordem (esquerda - raiz - direita)
    void inOrder(Node* node) {
        if (node == NULL) return;
        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }

public:
    BST() { root = NULL; }

    void inserir(int val) {
        root = insert(root, val);
    }

    // Mostra a arvore em ordem
    void mostrar() {
        if (root == NULL)
            cout << "Arvore vazia.\n";
        else {
            cout << "Elementos em ordem: ";
            inOrder(root);
            cout << "\n";
        }
    }

    // Chama verificacao de arvore cheia
    void verificarCheia() {
        if (isFull(root))
            cout << "\n[ OK ] A arvore eh CHEIA.\n";
        else
            cout << "\n[ X ] A arvore NAO eh cheia.\n";
    }

    // Insere valores padrao na arvore
    void preCarregar() {
        int valores[] = {8, 4, 12, 2, 6, 10, 14};
        int tamanho = sizeof(valores) / sizeof(valores[0]);
        for (int i = 0; i < tamanho; i++) {
            inserir(valores[i]);
        }
        cout << "\nArvore pre-carregada com sucesso!\n";
    }
};

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    BST arvore; // Instancia da arvore
    int opcao, valor;

    do {
        limparTela();
        cout << "=========================================\n";
        cout << "        MENU - ARVORE BINARIA DE BUSCA   \n";
        cout << "=========================================\n";
        cout << " [1] Inserir elemento\n";
        cout << " [2] Mostrar arvore (em ordem)\n";
        cout << " [3] Verificar se a arvore eh cheia\n";
        cout << " [4] Pre-carregar numeros padrao\n";
        cout << " [0] Sair\n";
        cout << "-----------------------------------------\n";
        cout << " Escolha: ";
        cin >> opcao;
        cout << "-----------------------------------------\n";

        switch (opcao) {
            case 1:
                cout << "Digite o valor: ";
                cin >> valor;
                arvore.inserir(valor); 
                cout << "Elemento inserido!\n";
                break;
            case 2:
                arvore.mostrar(); 
                break;
            case 3:
                arvore.verificarCheia(); // Verifica se eh cheia
                break;
            case 4:
                arvore.preCarregar(); // Carrega valores padrao
                break;
            case 0:
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opcao invalida!\n";
        }

        if (opcao != 0) {
            cout << "\nPressione ENTER para continuar...";
            cin.ignore();
            cin.get();
        }

    } while (opcao != 0);

    return 0;
}
