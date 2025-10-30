#ifndef GRAFO_H
#define GRAFO_H

#define vertice int

class Grafo {
private:
    int V;  // Numero de vertices
    int A;  // Numero de arcos
    
public:
    int **adj;  // Matriz de adjacencia ponderada
    int **dist; // Matriz de distancias
    int *grau;  // Grau de saida de cada vertice
    
    // Construtores e destrutor
    Grafo();
    Grafo(int V);
    ~Grafo();
    
    // Metodos basicos
    void inicializar(int V);
    void destruir();
    
    // Operacoes com arcos
    void inserirArco(vertice v, vertice w, int peso);
    void removerArco(vertice v, vertice w);
    
    // Informacoes do grafo
    void listarGrafo();
    void exibirMatrizAdjacencia();
    void exibirMatrizDistancias();
    void exibirGrauVertices();
    void carregarDeArquivo(const char* filename);
    
    // Getters
    int getV() { return V; }
    int getA() { return A; }
};

#endif