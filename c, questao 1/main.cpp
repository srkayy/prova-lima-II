#include <iostream>
#include <limits>
#include "Grafo.h"

using namespace std;

void limparBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void mostrarMenu() {
    system("pause");
    system("cls");
    cout << "\n=========================================" << endl;
    cout << "          SISTEMA DE GRAFOS" << endl;
    cout << "=========================================" << endl;
    cout << "1. Carregar grafo de arquivo" << endl;
    cout << "2. Inserir arco" << endl;
    cout << "3. Remover arco" << endl;
    cout << "4. Listar grafo (lista de adjacencia)" << endl;
    cout << "5. Exibir matriz de adjacencia" << endl;
    cout << "6. Exibir matriz de distancias" << endl;
    cout << "7. Exibir grau dos vertices" << endl;
    cout << "8. Exibir todas as representacoes" << endl;
    cout << "9. Criar grafo vazio" << endl;
    cout << "0. Sair" << endl;
    cout << "=========================================" << endl;
    cout << "Escolha uma opcao: ";
}

void carregarArquivo(Grafo& g) {
    string nomeArquivo;
    cout << "Digite o nome do arquivo (ex: grafo.txt): ";
    cin >> nomeArquivo;
    g.carregarDeArquivo(nomeArquivo.c_str());
}

void inserirArcoInterativo(Grafo& g) {
    if (g.getV() == 0) {
        cout << "Erro: Grafo nao inicializado. Carregue um arquivo ou crie um grafo vazio primeiro." << endl;
        return;
    }
    
    int v, w, peso;
    cout << "Digite o vertice de origem: ";
    cin >> v;
    cout << "Digite o vertice de destino: ";
    cin >> w;
    cout << "Digite o peso: ";
    cin >> peso;
    
    if (cin.fail()) {
        cout << "Erro: Entrada invalida!" << endl;
        limparBuffer();
        return;
    }
    
    g.inserirArco(v, w, peso);
}

void removerArcoInterativo(Grafo& g) {
    if (g.getV() == 0) {
        cout << "Erro: Grafo nao inicializado. Carregue um arquivo ou crie um grafo vazio primeiro." << endl;
        return;
    }
    
    int v, w;
    cout << "Digite o vertice de origem: ";
    cin >> v;
    cout << "Digite o vertice de destino: ";
    cin >> w;
    
    if (cin.fail()) {
        cout << "Erro: Entrada invalida!" << endl;
        limparBuffer();
        return;
    }
    
    g.removerArco(v, w);
}

void criarGrafoVazio(Grafo& g) {
    int V;
    cout << "Digite o numero de vertices: ";
    cin >> V;
    
    if (cin.fail() || V <= 0) {
        cout << "Erro: Numero de vertices invalido!" << endl;
        limparBuffer();
        return;
    }
    
    g = Grafo(V);
    cout << "Grafo vazio criado com " << V << " vertices." << endl;
}

void exibirTodasRepresentacoes(Grafo& g) {
    if (g.getV() == 0) {
        cout << "Erro: Grafo nao inicializado." << endl;
        return;
    }
    
    cout << "\n=== REPRESENTACOES COMPLETAS DO GRAFO ===" << endl;
    g.listarGrafo();
    g.exibirMatrizAdjacencia();
    g.exibirMatrizDistancias();
    g.exibirGrauVertices();
}

int main() {
    Grafo g;
    int opcao;
    
    cout << "Bem-vindo ao Sistema de Grafos Ponderados!" << endl;
    
    do {
        mostrarMenu();
        cin >> opcao;
        
        if (cin.fail()) {
            cout << "Erro: Opcao invalida!" << endl;
            limparBuffer();
            continue;
        }
        
        switch (opcao) {
            case 1:
                carregarArquivo(g);
                break;
                
            case 2:
                inserirArcoInterativo(g);
                break;
                
            case 3:
                removerArcoInterativo(g);
                break;
                
            case 4:
                if (g.getV() == 0) {
                    cout << "Erro: Grafo nao inicializado." << endl;
                } else {
                    g.listarGrafo();
                }
                break;
                
            case 5:
                if (g.getV() == 0) {
                    cout << "Erro: Grafo nao inicializado." << endl;
                } else {
                    g.exibirMatrizAdjacencia();
                }
                break;
                
            case 6:
                if (g.getV() == 0) {
                    cout << "Erro: Grafo nao inicializado." << endl;
                } else {
                    g.exibirMatrizDistancias();
                }
                break;
                
            case 7:
                if (g.getV() == 0) {
                    cout << "Erro: Grafo nao inicializado." << endl;
                } else {
                    g.exibirGrauVertices();
                }
                break;
                
            case 8:
                exibirTodasRepresentacoes(g);
                break;
                
            case 9:
                criarGrafoVazio(g);
                break;
                
            case 0:
                cout << "Saindo do sistema..." << endl;
                break;
                
            default:
                cout << "Opcao invalida! Tente novamente." << endl;
                break;
        }
        
        // Pausa para visualizacao
        if (opcao != 0) {
            cout << "\nPressione Enter para continuar...";
            limparBuffer();
        }
        
    } while (opcao != 0);
    
    return 0;
}