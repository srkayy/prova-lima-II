#include "BST.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void drawHeader() {
    cout << "=========================================\n";
    cout << "  ALGORITMO RECURSIVO - MAIOR VALOR BST\n";
    cout << "=========================================\n";
}

void drawMenu() {
    cout << "\n    >>> MENU PRINCIPAL <<<\n";
    cout << "    ----------------------\n";
    cout << "    1. Inserir valor\n";
    cout << "    2. Listar arvore (in-ordem)\n";
    cout << "    3. Encontrar maior valor\n";
    cout << "    4. Sair\n";
    cout << "    ----------------------\n";
    cout << "    Escolha uma opcao: ";
}

void waitForEnter() {
    cout << "\n    Pressione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

int main() {
    BST arvore;
    
    // Carrega automaticamente os valores do exercício sem mostrar mensagem
    arvore.insert(20);
    arvore.insert(5);
    arvore.insert(12);
    arvore.insert(36);
    arvore.insert(27);
    arvore.insert(45);
    arvore.insert(9);
    arvore.insert(2);
    arvore.insert(6);
    arvore.insert(17);
    arvore.insert(40);
    
    int opcao, valor;
    
    do {
        clearScreen();
        drawHeader();
        
        // Mostra o maior valor atual
        int maiorAtual = arvore.findMax();
        if (maiorAtual != -1) {
            cout << "    Maior valor atual: " << maiorAtual << "\n";
        }
        
        drawMenu();
        cin >> opcao;
        
        switch (opcao) {
            case 1: // INSERIR
                clearScreen();
                drawHeader();
                cout << "\n    >>> INSERIR VALOR <<<\n";
                cout << "    ----------------------\n";
                cout << "    Digite o valor a ser inserido: ";
                cin >> valor;
                arvore.insert(valor);
                waitForEnter();
                break;
                
            case 2: // LISTAR
                clearScreen();
                drawHeader();
                cout << "\n    >>> LISTAGEM DA ARVORE <<<\n";
                cout << "    ----------------------\n";
                arvore.inOrder();
                waitForEnter();
                break;
                
            case 3: // ENCONTRAR MAIOR VALOR
                clearScreen();
                drawHeader();
                cout << "\n    >>> MAIOR VALOR <<<\n";
                cout << "    ----------------------\n";
                
                cout << "  Executando algoritmo recursivo...\n\n";
                int maior;
                maior = arvore.findMax();
                
                if (maior != -1) {
                    cout << "  RESULTADO: Maior valor encontrado = " << maior << "\n";
                    
                    // Explicação SIMPLES do algoritmo
                    cout << "\n  >>> COMO FUNCIONA? <<<\n";
                    cout << "  Imagine que voce esta procurando o maior numero\n";
                    cout << "  em uma arvore organizada:\n\n";
                    cout << "  1. Sempre vamos para a DIREITA\n";
                    cout << "  2. Porque na arvore, os maiores valores\n";
                    cout << "     ficam do lado direito\n";
                    cout << "  3. Continuamos indo para direita ate\n";
                    cout << "     nao ter mais nada a direita\n";
                    cout << "  4. Quando nao tiver mais nada a direita,\n";
                    cout << "     achamos o maior valor!\n\n";
                    cout << "  E tipo: 'Vou sempre pra direita ate nao dar mais!'";
                } else {
                    cout << "  A arvore esta vazia!\n";
                    cout << "  Nao tem como achar o maior valor se nao tem nada!\n";
                }
                waitForEnter();
                break;
                
            case 4: // SAIR
                clearScreen();
                drawHeader();
                cout << "\n    Obrigado por testar o algoritmo!\n";
                cout << "    Encerrando...\n";
                cout << "=========================================\n";
                break;
                
            default:
                cout << "\n    Opcao invalida! Tente 1-4.\n";
                waitForEnter();
                break;
        }
        
    } while (opcao != 4);
    
    return 0;
}