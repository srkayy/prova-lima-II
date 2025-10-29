#include "BST.h"
#include <iostream>
#include <cstdlib> // Para system("clear") ou system("cls")

using namespace std;

// Função para limpar a tela (funciona em Windows e Linux)
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Desenha um cabeçalho bonito
void drawHeader() {
    cout << "=========================================\n";
    cout << "      ARVORE BINARIA DE BUSCA\n";
    cout << "=========================================\n";
}

// Desenha o menu principal
void drawMenu() {
    cout << "\n    >>> MENU PRINCIPAL <<<\n";
    cout << "    ----------------------\n";
    cout << "    1. INSERCAO\n";
    cout << "    2. LISTAGEM\n"; 
    cout << "    3. REMOCAO\n";
    cout << "    ----------------------\n";
    cout << "    4. Carregar Valores Iniciais\n";
    cout << "    5. Sair\n";
    cout << "    ----------------------\n";
    cout << "    Escolha uma opcao: ";
}

// Função para pausar e esperar Enter
void waitForEnter() {
    cout << "\n    Pressione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

int main() {
    BST arvore;
    int opcao, valor;
    char continuar;
    
    do {
        clearScreen();
        drawHeader();
        drawMenu();
        cin >> opcao;
        
        switch (opcao) {
            case 1: // INSERÇÃO
                clearScreen();
                drawHeader();
                cout << "\n    >>> 1 - INSERCAO <<<\n";
                cout << "    ----------------------\n";
                cout << "    Digite o valor a ser inserido: ";
                cin >> valor;
                arvore.insert(valor);
                waitForEnter();
                break;
                
            case 2: // LISTAGEM  
                clearScreen();
                drawHeader();
                cout << "\n    >>> 2 - LISTAGEM <<<\n";
                cout << "    ----------------------\n";
                arvore.inOrder();
                waitForEnter();
                break;
                
            case 3: // REMOÇÃO
                do {
                    clearScreen();
                    drawHeader();
                    cout << "\n    >>> 3 - REMOCAO <<<\n";
                    cout << "    ----------------------\n";
                    cout << "    Digite o valor a ser removido: ";
                    cin >> valor;
                    arvore.remove(valor);
                    
                    cout << "\n    Deseja realizar outra remocao? (s/n): ";
                    cin >> continuar;
                } while (continuar == 's' || continuar == 'S');
                break;
                
            case 4: // Carregar valores iniciais
                clearScreen();
                drawHeader();
                cout << "\n    >>> VALORES INICIAIS <<<\n";
                cout << "    ----------------------\n";
                cout << "    Carregando: 20, 5, 12, 36, 27, 45, 9, 2, 6, 17, 40\n";
                arvore.loadDefaultValues();
                waitForEnter();
                break;
                
            case 5: // Sair
                clearScreen();
                drawHeader();
                cout << "\n    Obrigado por usar o programa!\n";
                cout << "    Encerrando...\n";
                cout << "=========================================\n";
                break;
                
            default:
                cout << "\n    Opcao invalida! Tente 1-5.\n";
                waitForEnter();
                break;
        }
        
    } while (opcao != 5);
    
    return 0;
}