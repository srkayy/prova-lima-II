#include <iostream>
#include <fstream>
#include <iomanip>
#include <climits>
#include "Grafo.h"

using namespace std;

// Construtor padrao
Grafo::Grafo() {
    V = 0;
    A = 0;
    adj = nullptr;
    dist = nullptr;
    grau = nullptr;
}

// Construtor com numero de vertices
Grafo::Grafo(int V) {
    inicializar(V);
}

// Destrutor
Grafo::~Grafo() {
    destruir();
}

// Inicializa o grafo
void Grafo::inicializar(int V) {
    this->V = V;
    this->A = 0;
    
    // Aloca matriz de adjacencia ponderada
    adj = new int*[V];
    for(int i = 0; i < V; i++) {
        adj[i] = new int[V];
        for(int j = 0; j < V; j++) {
            adj[i][j] = 0; // 0 indica ausencia de arco
        }
    }
    
    // Aloca matriz de distancias
    dist = new int*[V];
    for(int i = 0; i < V; i++) {
        dist[i] = new int[V];
        for(int j = 0; j < V; j++) {
            if(i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = INT_MAX; // INT_MAX indica distancia infinita
        }
    }
    
    // Aloca vetor de graus
    grau = new int[V];
    for(int i = 0; i < V; i++) {
        grau[i] = 0;
    }
}

// Libera memoria
void Grafo::destruir() {
    if(adj != nullptr) {
        for(int i = 0; i < V; i++) {
            delete[] adj[i];
        }
        delete[] adj;
        adj = nullptr;
    }
    
    if(dist != nullptr) {
        for(int i = 0; i < V; i++) {
            delete[] dist[i];
        }
        delete[] dist;
        dist = nullptr;
    }
    
    if(grau != nullptr) {
        delete[] grau;
        grau = nullptr;
    }
    
    V = 0;
    A = 0;
}

// Insere arco ponderado
void Grafo::inserirArco(vertice v, vertice w, int peso) {
    if(v < 0 || v >= V || w < 0 || w >= V) {
        cout << "Vertice invalido!" << endl;
        return;
    }
    
    if(peso == 0) {
        cout << "Erro: Grafo e ponderado, peso nao pode ser zero!" << endl;
        return;
    }
    
    // Se ja existe arco, atualiza o peso
    if(adj[v][w] == 0) {
        A++; // Novo arco
    } else {
        cout << "Atualizando peso do arco " << v << "->" << w << endl;
    }
    
    adj[v][w] = peso;
    dist[v][w] = peso;
    
    // Atualiza grau (conta apenas arcos de saida)
    grau[v] = 0;
    for(int j = 0; j < V; j++) {
        if(adj[v][j] != 0) {
            grau[v]++;
        }
    }
}

// Remove arco
void Grafo::removerArco(vertice v, vertice w) {
    if(v < 0 || v >= V || w < 0 || w >= V) {
        cout << "Vertice invalido!" << endl;
        return;
    }
    
    if(adj[v][w] != 0) {
        adj[v][w] = 0;
        dist[v][w] = INT_MAX;
        A--;
        
        // Atualiza grau
        grau[v] = 0;
        for(int j = 0; j < V; j++) {
            if(adj[v][j] != 0) {
                grau[v]++;
            }
        }
        cout << "Arco " << v << "->" << w << " removido com sucesso!" << endl;
    } else {
        cout << "Arco " << v << "->" << w << " nao existe!" << endl;
    }
}

// Lista o grafo em formato de lista de adjacencia
void Grafo::listarGrafo() {
    cout << "=== LISTAGEM DO GRAFO ===" << endl;
    cout << "Grafo (Lista de Adjacencia Ponderada):" << endl;
    for(int i = 0; i < V; i++) {
        cout << "Vertice " << i << " (grau " << grau[i] << "): ";
        bool temArco = false;
        for(int j = 0; j < V; j++) {
            if(adj[i][j] != 0) {
                cout << j << "[" << adj[i][j] << "] ";
                temArco = true;
            }
        }
        if(!temArco) {
            cout << "Nenhum arco de saida";
        }
        cout << endl;
    }
    cout << "Total: " << V << " vertices, " << A << " arcos" << endl << endl;
}

// Exibe a matriz de adjacencia
void Grafo::exibirMatrizAdjacencia() {
    cout << "=== MATRIZ DE ADJACENCIA ===" << endl;
    cout << "    ";
    for(int i = 0; i < V; i++) {
        cout << setw(4) << i;
    }
    cout << endl;
    
    for(int i = 0; i < V; i++) {
        cout << setw(3) << i << " ";
        for(int j = 0; j < V; j++) {
            if(adj[i][j] == 0) {
                cout << setw(4) << "0";
            } else {
                cout << setw(4) << adj[i][j];
            }
        }
        cout << endl;
    }
    cout << endl;
}

// Exibe a matriz de distancias
void Grafo::exibirMatrizDistancias() {
    cout << "=== MATRIZ DE DISTANCIAS ===" << endl;
    cout << "    ";
    for(int i = 0; i < V; i++) {
        cout << setw(4) << i;
    }
    cout << endl;
    
    for(int i = 0; i < V; i++) {
        cout << setw(3) << i << " ";
        for(int j = 0; j < V; j++) {
            if(dist[i][j] == INT_MAX) {
                cout << setw(4) << "INF";
            } else {
                cout << setw(4) << dist[i][j];
            }
        }
        cout << endl;
    }
    cout << endl;
}

// Exibe o grau dos vertices
void Grafo::exibirGrauVertices() {
    cout << "=== GRAU DOS VERTICES ===" << endl;
    for(int i = 0; i < V; i++) {
        cout << "Vertice " << i << ": grau " << grau[i] << " (saida)" << endl;
    }
    cout << endl;
}

// Carrega grafo de arquivo
void Grafo::carregarDeArquivo(const char* filename) {
    ifstream arquivo(filename);
    if(!arquivo.is_open()) {
        cout << "Erro ao abrir arquivo: " << filename << endl;
        return;
    }
    
    // Destroi grafo atual se existir
    destruir();
    
    // Le numero de vertices
    arquivo >> V;
    inicializar(V);
    
    // Le arcos ponderados
    int v, w, peso;
    
    cout << "Carregando grafo ponderado de " << filename << "..." << endl;
    
    while(arquivo >> v >> w >> peso) {
        if(peso == 0) {
            cout << "Aviso: Peso zero ignorado para arco " << v << "->" << w << endl;
            continue;
        }
        inserirArco(v, w, peso);
    }
    
    arquivo.close();
    cout << "Grafo carregado com sucesso!" << endl;
    cout << "Vertices: " << V << ", Arcos: " << A << endl << endl;
}