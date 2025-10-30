#include <iostream>
#include <vector>
#include <iomanip>
#include <climits>
#include <limits>
#include "Grafo.h"

using namespace std;

void limparBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pausar() {
    system("pause");
    system("cls");
}

class FloydWarshall {
private:
    int V;
    int** dist;
    int** next;
    
    void inicializar(Grafo& grafo) {
        V = grafo.getV();
        
        // Aloca matrizes
        dist = new int*[V];
        next = new int*[V];
        
        for(int i = 0; i < V; i++) {
            dist[i] = new int[V];
            next[i] = new int[V];
        }
        
        for(int i = 0; i < V; i++) {
            for(int j = 0; j < V; j++) {
                // Usa a matriz dist do grafo como base
                dist[i][j] = grafo.dist[i][j];
                
                // Inicializa matriz next para reconstruir caminhos
                if(i == j || dist[i][j] == INT_MAX) {
                    next[i][j] = -1;
                } else {
                    next[i][j] = j;
                }
            }
        }
    }
    
    void executarAlgoritmo() {
        for(int k = 0; k < V; k++) {
            for(int i = 0; i < V; i++) {
                for(int j = 0; j < V; j++) {
                    // Evita overflow
                    if(dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                        if(dist[i][j] > dist[i][k] + dist[k][j]) {
                            dist[i][j] = dist[i][k] + dist[k][j];
                            next[i][j] = next[i][k];
                        }
                    }
                }
            }
        }
    }
    
public:
    FloydWarshall(Grafo& grafo) {
        inicializar(grafo);
        executarAlgoritmo();
    }
    
    ~FloydWarshall() {
        for(int i = 0; i < V; i++) {
            delete[] dist[i];
            delete[] next[i];
        }
        delete[] dist;
        delete[] next;
    }
    
    int obterDistancia(int origem, int destino) {
        if(origem < 0 || origem >= V || destino < 0 || destino >= V) {
            return INT_MAX;
        }
        return dist[origem][destino];
    }
    
    vector<int> obterCaminho(int origem, int destino) {
        vector<int> caminho;
        
        if(origem < 0 || origem >= V || destino < 0 || destino >= V) {
            return caminho;
        }
        
        if(next[origem][destino] == -1) {
            return caminho; // Nao ha caminho
        }
        
        caminho.push_back(origem);
        int atual = origem;
        
        while(atual != destino) {
            atual = next[atual][destino];
            caminho.push_back(atual);
        }
        
        return caminho;
    }
    
    void exibirMatrizDistancias() {
        cout << "=== MATRIZ DE DISTANCIAS MINIMAS ===" << endl;
        cout << "    ";
        for(int i = 0; i < V; i++) {
            cout << setw(6) << i;
        }
        cout << endl;
        
        for(int i = 0; i < V; i++) {
            cout << setw(3) << i << " ";
            for(int j = 0; j < V; j++) {
                if(dist[i][j] == INT_MAX) {
                    cout << setw(6) << "INF";
                } else {
                    cout << setw(6) << dist[i][j];
                }
            }
            cout << endl;
        }
        cout << endl;
    }
    
    void exibirTodosCaminhos() {
        cout << "=== TODOS OS CAMINHOS MINIMOS ===" << endl;
        for(int i = 0; i < V; i++) {
            for(int j = 0; j < V; j++) {
                if(i != j) {
                    int distancia = obterDistancia(i, j);
                    vector<int> caminho = obterCaminho(i, j);
                    
                    cout << i << " -> " << j << ": ";
                    if(distancia == INT_MAX) {
                        cout << "Sem caminho" << endl;
                    } else {
                        cout << "Distancia = " << distancia << ", Caminho = ";
                        for(size_t k = 0; k < caminho.size(); k++) {
                            cout << caminho[k];
                            if(k < caminho.size() - 1) {
                                cout << " -> ";
                            }
                        }
                        cout << endl;
                    }
                }
            }
        }
    }
};

// Menu interativo para Floyd-Warshall
void menuFloydWarshall() {
    Grafo g;
    FloydWarshall* fw = nullptr;
    int opcao;
    bool grafoCarregado = false;
    
    do {
        cout << "\n=========================================" << endl;
        cout << "    ALGORITMO DE FLOYD-WARSHALL" << endl;
        cout << "=========================================" << endl;
        cout << "1. Carregar grafo de arquivo" << endl;
        cout << "2. Executar Floyd-Warshall" << endl;
        cout << "3. Consultar distancia entre vertices" << endl;
        cout << "4. Consultar caminho entre vertices" << endl;
        cout << "5. Exibir matriz de distancias minimas" << endl;
        cout << "6. Exibir todos os caminhos" << endl;
        cout << "7. Exibir grafo original" << endl;
        cout << "0. Sair" << endl;
        cout << "=========================================" << endl;
        cout << "Escolha uma opcao: ";
        
        cin >> opcao;
        
        if(cin.fail()) {
            cout << "Erro: Opcao invalida!" << endl;
            limparBuffer();
            continue;
        }
        
        switch(opcao) {
            case 1: {
                string nomeArquivo;
                cout << "Digite o nome do arquivo: ";
                cin >> nomeArquivo;
                g.carregarDeArquivo(nomeArquivo.c_str());
                grafoCarregado = true;
                pausar();
                break;
            }
                
            case 2: {
                if(!grafoCarregado) {
                    cout << "Erro: Carregue um grafo primeiro (opcao 1)!" << endl;
                    pausar();
                    break;
                }
                
                if(fw != nullptr) {
                    delete fw;
                    fw = nullptr;
                }
                
                cout << "Executando Floyd-Warshall..." << endl;
                fw = new FloydWarshall(g);
                cout << "Floyd-Warshall executado com sucesso!" << endl;
                pausar();
                break;
            }
                
            case 3: {
                if(fw == nullptr) {
                    cout << "Erro: Execute Floyd-Warshall primeiro (opcao 2)!" << endl;
                    pausar();
                    break;
                }
                
                int origem, destino;
                cout << "Vertice origem: ";
                cin >> origem;
                cout << "Vertice destino: ";
                cin >> destino;
                
                if(cin.fail()) {
                    cout << "Erro: Vertices invalidos!" << endl;
                    limparBuffer();
                    break;
                }
                
                int dist = fw->obterDistancia(origem, destino);
                if(dist == INT_MAX) {
                    cout << "Nao ha caminho de " << origem << " para " << destino << endl;
                } else {
                    cout << "Distancia minima: " << dist << endl;
                }
                pausar();
                break;
            }
                
            case 4: {
                if(fw == nullptr) {
                    cout << "Erro: Execute Floyd-Warshall primeiro (opcao 2)!" << endl;
                    pausar();
                    break;
                }
                
                int origem, destino;
                cout << "Vertice origem: ";
                cin >> origem;
                cout << "Vertice destino: ";
                cin >> destino;
                
                if(cin.fail()) {
                    cout << "Erro: Vertices invalidos!" << endl;
                    limparBuffer();
                    break;
                }
                
                vector<int> caminho = fw->obterCaminho(origem, destino);
                if(caminho.empty()) {
                    cout << "Nao ha caminho de " << origem << " para " << destino << endl;
                } else {
                    cout << "Caminho: ";
                    for(size_t i = 0; i < caminho.size(); i++) {
                        cout << caminho[i];
                        if(i < caminho.size() - 1) cout << " -> ";
                    }
                    cout << endl;
                }
                pausar();
                break;
            }
                
            case 5:
                if(fw == nullptr) {
                    cout << "Erro: Execute Floyd-Warshall primeiro (opcao 2)!" << endl;
                } else {
                    fw->exibirMatrizDistancias();
                }
                pausar();
                break;
                
            case 6:
                if(fw == nullptr) {
                    cout << "Erro: Execute Floyd-Warshall primeiro (opcao 2)!" << endl;
                } else {
                    fw->exibirTodosCaminhos();
                }
                pausar();
                break;
                
            case 7:
                if(!grafoCarregado) {
                    cout << "Erro: Nenhum grafo carregado!" << endl;
                } else {
                    g.listarGrafo();
                }
                pausar();
                break;
                
            case 0:
                if(fw != nullptr) {
                    delete fw;
                }
                cout << "Saindo do programa..." << endl;
                break;
                
            default:
                cout << "Opcao invalida!" << endl;
                pausar();
                break;
        }
    } while(opcao != 0);
}

int main() {
    cout << "================================================" << endl;
    cout << "   SISTEMA FLOYD-WARSHALL - CAMINHOS MINIMOS" << endl;
    cout << "================================================" << endl;
    
    menuFloydWarshall();
    
    cout << "Programa encerrado." << endl;
    return 0;
}