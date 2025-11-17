#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <limits>
using namespace std;


struct Pessoa {
    string nome;
    char sexo;
    int idade;
    double peso;
    
    Pessoa(string n = "", char s = ' ', int i = 0, double p = 0.0) {
        nome = n;
        sexo = s;
        idade = i;
        peso = p;
    }
};

// Nó da Árvore Binária
struct NoArvore {
    Pessoa pessoa;
    NoArvore* esquerda;
    NoArvore* direita;
    
    NoArvore(Pessoa p) {
        pessoa = p;
        esquerda = NULL;
        direita = NULL;
    }
};

// Nó da Lista Encadeada
struct NoLista {
    Pessoa pessoa;
    NoLista* proximo;
    
    NoLista(Pessoa p) {
        pessoa = p;
        proximo = NULL;
    }
};

// Ponteiro RAIZ 
NoArvore* RAIZ = NULL;

// Funções da Árvore
NoArvore* inserirArvore(NoArvore* node, Pessoa p) {
    if (node == NULL) {
        return new NoArvore(p);
    }
    
    if (p.nome < node->pessoa.nome) {
        node->esquerda = inserirArvore(node->esquerda, p);
    } else if (p.nome > node->pessoa.nome) {
        node->direita = inserirArvore(node->direita, p);
    }
    
    return node;
}

void inserirPessoa(Pessoa p) {
    RAIZ = inserirArvore(RAIZ, p);
}

// Função para inserir ordenado na lista
void inserirOrdenadoLista(NoLista** lista, Pessoa p) {
    NoLista* novo = new NoLista(p);
    
    if (*lista == NULL) {
        *lista = novo;
        return;
    }
    
    NoLista* atual = *lista;
    NoLista* anterior = NULL;
    
    // Encontrar posição correta para manter ordenado por nome
    while (atual != NULL && atual->pessoa.nome < p.nome) {
        anterior = atual;
        atual = atual->proximo;
    }
    
    if (anterior == NULL) {
        // Inserir no início
        novo->proximo = *lista;
        *lista = novo;
    } else {
        // Inserir no meio ou final
        anterior->proximo = novo;
        novo->proximo = atual;
    }
}

// Função recursiva para percorrer a árvore em ordem
void percorrerInOrder(NoArvore* node, NoLista** listaHomens, NoLista** listaMulheres) {
    if (node == NULL) return;
    
    percorrerInOrder(node->esquerda, listaHomens, listaMulheres);
    
    // Insere na lista correspondente de forma ordenada
    if (node->pessoa.sexo == 'M' || node->pessoa.sexo == 'm') {
        inserirOrdenadoLista(listaHomens, node->pessoa);
    } else if (node->pessoa.sexo == 'F' || node->pessoa.sexo == 'f') {
        inserirOrdenadoLista(listaMulheres, node->pessoa);
    }
    
    percorrerInOrder(node->direita, listaHomens, listaMulheres);
}

void gerarListasOrdenadas(NoLista** listaHomens, NoLista** listaMulheres) {
    *listaHomens = NULL;
    *listaMulheres = NULL;
    percorrerInOrder(RAIZ, listaHomens, listaMulheres);
}

// Funções para exibir listas
void exibirLista(NoLista* lista, string titulo) {
    cout << "\n" << titulo << ":\n";
    cout << "----------------------------------------\n";
    
    if (lista == NULL) {
        cout << "Lista vazia!\n";
        return;
    }
    
    NoLista* atual = lista;
    while (atual != NULL) {
        cout << "Nome: " << atual->pessoa.nome 
             << " | Sexo: " << atual->pessoa.sexo
             << " | Idade: " << atual->pessoa.idade
             << " | Peso: " << atual->pessoa.peso << "kg\n";
        atual = atual->proximo;
    }
}

void liberarLista(NoLista* lista) {
    while (lista != NULL) {
        NoLista* temp = lista;
        lista = lista->proximo;
        delete temp;
    }
}

void carregarDadosExemplo() {
    // Não limpa mais a árvore atual, apenas adiciona
    inserirPessoa(Pessoa("Carlos", 'M', 25, 72.5));
    inserirPessoa(Pessoa("Ana", 'F', 30, 60.0));
    inserirPessoa(Pessoa("Bruno", 'M', 28, 80.3));
    inserirPessoa(Pessoa("Daniela", 'F', 22, 55.1));
    inserirPessoa(Pessoa("Eduardo", 'M', 35, 90.0));
    inserirPessoa(Pessoa("Fernanda", 'F', 27, 62.7));
    inserirPessoa(Pessoa("Gabriel", 'M', 20, 68.2));
    inserirPessoa(Pessoa("Helena", 'F', 32, 58.9));
}

// Função para limpar a árvore (nova funcionalidade)
void limparArvore(NoArvore* node) {
    if (node == NULL) return;
    
    limparArvore(node->esquerda);
    limparArvore(node->direita);
    delete node;
}

void limparArvoreCompleta() {
    limparArvore(RAIZ);
    RAIZ = NULL;
}

// Função para ler número inteiro com tratamento de erro
int lerInteiro(const string& mensagem) {
    int valor;
    while (true) {
        cout << mensagem;
        cin >> valor;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Erro: Por favor, digite um numero inteiro valido.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
    }
}

// Função para ler número decimal com tratamento de erro
double lerDecimal(const string& mensagem) {
    double valor;
    while (true) {
        cout << mensagem;
        cin >> valor;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Erro: Por favor, digite um numero valido.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
    }
}

// Função para ler caractere com tratamento de erro
char lerChar(const string& mensagem) {
    string entrada;
    while (true) {
        cout << mensagem;
        getline(cin, entrada);
        
        if (entrada.length() == 1 && (entrada[0] == 'M' || entrada[0] == 'm' || 
                                     entrada[0] == 'F' || entrada[0] == 'f')) {
            return toupper(entrada[0]);
        } else {
            cout << "Erro: Por favor, digite 'M' para masculino ou 'F' para feminino.\n";
        }
    }
}

void limparTela() {
    system("cls");
}

void exibirCabecalho() {
    cout << "========================================\n";
    cout << "  ARVORE BINARIA + LISTAS ORDENADAS\n";
    cout << "========================================\n";
    cout << " Ponteiro RAIZ: " << (RAIZ != NULL ? "Ativo" : "NULL") << "\n";
}

void exibirMenu() {
    cout << "\n    >>> MENU PRINCIPAL <<<\n";
    cout << "    ----------------------\n";
    cout << "    1. Carregar dados exemplo\n";
    cout << "    2. Gerar listas ordenadas\n";
    cout << "    3. Inserir nova pessoa\n";
    cout << "    4. Limpar arvore\n";
    cout << "    5. Sair\n";
    cout << "    ----------------------\n";
    cout << "    Escolha: ";
}

void pausar() {
    cout << "\nPressione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int main() {
    NoLista* listaHomens = NULL;
    NoLista* listaMulheres = NULL;
    
    int opcao;
    
    do {
        limparTela();
        exibirCabecalho();
        exibirMenu();
        
        cin >> opcao;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcao = -1;
        }
        
        switch (opcao) {
            case 1:
                carregarDadosExemplo();
                cout << "\n? Dados exemplo carregados na arvore!\n";
                pausar();
                break;
                
            case 2:
                // ALGORITMO PRINCIPAL
                gerarListasOrdenadas(&listaHomens, &listaMulheres);
                
                cout << "\n? Listas geradas com sucesso!\n";
                exibirLista(listaHomens, "HOMENS (Ordenados por Nome)");
                exibirLista(listaMulheres, "MULHERES (Ordenadas por Nome)");
                pausar();
                break;
                
            case 3: {
                string nome;
                char sexo;
                int idade;
                double peso;
                
                cout << "\n>>> INSERIR NOVA PESSOA <<<\n";
                
                cout << "Nome: ";
                cin.ignore();
                getline(cin, nome);
                
                sexo = lerChar("Sexo (M/F): ");
                
                idade = lerInteiro("Idade: ");
                
                peso = lerDecimal("Peso: ");
                
                inserirPessoa(Pessoa(nome, sexo, idade, peso));
                cout << "? Pessoa inserida na arvore!\n";
                pausar();
                break;
            }
            
            case 4:
                limparArvoreCompleta();
                liberarLista(listaHomens);
                liberarLista(listaMulheres);
                listaHomens = NULL;
                listaMulheres = NULL;
                cout << "\n? Arvore e listas limpas!\n";
                pausar();
                break;
                
            case 5:
                cout << "\nEncerrando programa...\n";
                break;
                
            default:
                cout << "\n? Opcao invalida!\n";
                pausar();
                break;
        }
        
    } while (opcao != 5);
    
    liberarLista(listaHomens);
    liberarLista(listaMulheres);
    limparArvoreCompleta();
    
    return 0;
}
