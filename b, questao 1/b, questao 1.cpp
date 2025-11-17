#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <limits>
#include <algorithm>
using namespace std;

// Estrutura Pessoa
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

// Nó da Árvore AVL
struct NoAVL {
    Pessoa pessoa;
    NoAVL* esquerda;
    NoAVL* direita;
    int altura;
    
    NoAVL(Pessoa p) {
        pessoa = p;
        esquerda = NULL;
        direita = NULL;
        altura = 1;
    }
};

// Ponteiro RAIZ 
NoAVL* RAIZ = NULL;

// FUNÇÕES AUXILIARES DA ÁRVORE AVL
int altura(NoAVL* node) {
    return node == NULL ? 0 : node->altura;
}

int fatorBalanceamento(NoAVL* node) {
    return node == NULL ? 0 : altura(node->esquerda) - altura(node->direita);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

NoAVL* rotacaoDireita(NoAVL* y) {
    NoAVL* x = y->esquerda;
    NoAVL* T2 = x->direita;
    
    x->direita = y;
    y->esquerda = T2;
    
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    
    return x;
}

NoAVL* rotacaoEsquerda(NoAVL* x) {
    NoAVL* y = x->direita;
    NoAVL* T2 = y->esquerda;
    
    y->esquerda = x;
    x->direita = T2;
    
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    
    return y;
}

NoAVL* balancear(NoAVL* node) {
    if (node == NULL) return node;
    
    node->altura = 1 + max(altura(node->esquerda), altura(node->direita));
    
    int balance = fatorBalanceamento(node);
    
    // Caso Esquerda-Esquerda
    if (balance > 1 && fatorBalanceamento(node->esquerda) >= 0)
        return rotacaoDireita(node);
    
    // Caso Direita-Direita
    if (balance < -1 && fatorBalanceamento(node->direita) <= 0)
        return rotacaoEsquerda(node);
    
    // Caso Esquerda-Direita
    if (balance > 1 && fatorBalanceamento(node->esquerda) < 0) {
        node->esquerda = rotacaoEsquerda(node->esquerda);
        return rotacaoDireita(node);
    }
    
    // Caso Direita-Esquerda
    if (balance < -1 && fatorBalanceamento(node->direita) > 0) {
        node->direita = rotacaoDireita(node->direita);
        return rotacaoEsquerda(node);
    }
    
    return node;
}

// F1-INSERÇÃO
NoAVL* inserirAVL(NoAVL* node, Pessoa p) {
    if (node == NULL) {
        return new NoAVL(p);
    }
    
    if (p.nome < node->pessoa.nome) {
        node->esquerda = inserirAVL(node->esquerda, p);
    } else if (p.nome > node->pessoa.nome) {
        node->direita = inserirAVL(node->direita, p);
    } else {
        // Nome duplicado - não permitido em AVL
        cout << "Erro: Nome ja existe na arvore!\n";
        return node;
    }
    
    return balancear(node);
}

void inserirPessoa(Pessoa p) {
    RAIZ = inserirAVL(RAIZ, p);
}

// F3-REMOÇÃO
NoAVL* menorNo(NoAVL* node) {
    NoAVL* current = node;
    while (current->esquerda != NULL)
        current = current->esquerda;
    return current;
}

NoAVL* removerAVL(NoAVL* node, string nome) {
    if (node == NULL) return node;
    
    if (nome < node->pessoa.nome) {
        node->esquerda = removerAVL(node->esquerda, nome);
    } else if (nome > node->pessoa.nome) {
        node->direita = removerAVL(node->direita, nome);
    } else {
        // Nó encontrado
        if ((node->esquerda == NULL) || (node->direita == NULL)) {
            NoAVL* temp = node->esquerda ? node->esquerda : node->direita;
            
            if (temp == NULL) {
                temp = node;
                node = NULL;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            NoAVL* temp = menorNo(node->direita);
            node->pessoa = temp->pessoa;
            node->direita = removerAVL(node->direita, temp->pessoa.nome);
        }
    }
    
    if (node == NULL) return node;
    
    return balancear(node);
}

void removerPessoa(string nome) {
    RAIZ = removerAVL(RAIZ, nome);
}


// F4-CONSULTA
NoAVL* consultarAVL(NoAVL* node, string nome) {
    if (node == NULL || node->pessoa.nome == nome)
        return node;
    
    if (nome < node->pessoa.nome)
        return consultarAVL(node->esquerda, nome);
    else
        return consultarAVL(node->direita, nome);
}

void consultarPessoa(string nome) {
    NoAVL* resultado = consultarAVL(RAIZ, nome);
    if (resultado != NULL) {
        cout << "\n>>> PESSOA ENCONTRADA <<<\n";
        cout << "Nome: " << resultado->pessoa.nome << "\n";
        cout << "Sexo: " << resultado->pessoa.sexo << "\n";
        cout << "Idade: " << resultado->pessoa.idade << "\n";
        cout << "Peso: " << resultado->pessoa.peso << "kg\n";
    } else {
        cout << "\n? Pessoa nao encontrada!\n";
    }
}

// F2-LISTAGEM Apenas em Ordem
void listarEmOrdem(NoAVL* node) {
    if (node != NULL) {
        listarEmOrdem(node->esquerda);
        cout << "Nome: " << node->pessoa.nome 
             << " | Sexo: " << node->pessoa.sexo
             << " | Idade: " << node->pessoa.idade
             << " | Peso: " << node->pessoa.peso << "kg\n";
        listarEmOrdem(node->direita);
    }
}

// FUNÇÕES AUXILIARES
void liberarArvore(NoAVL* node) {
    if (node == NULL) return;
    liberarArvore(node->esquerda);
    liberarArvore(node->direita);
    delete node;
}

// Funções para leitura com tratamento de erro
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

// FUNÇÃO PARA CARREGAR DADOS EXEMPLO
void carregarDadosExemplo() {
    inserirPessoa(Pessoa("Carlos", 'M', 25, 72.5));
    inserirPessoa(Pessoa("Ana", 'F', 30, 60.0));
    inserirPessoa(Pessoa("Bruno", 'M', 28, 80.3));
    inserirPessoa(Pessoa("Daniela", 'F', 22, 55.1));
    inserirPessoa(Pessoa("Eduardo", 'M', 35, 90.0));
    inserirPessoa(Pessoa("Fernanda", 'F', 27, 62.7));
    inserirPessoa(Pessoa("Gabriel", 'M', 20, 68.2));
    inserirPessoa(Pessoa("Helena", 'F', 32, 58.9));
}

// FUNÇÕES DE INTERFACE DO MENU
void limparTela() {
    system("cls");
}

void exibirCabecalho() {
    cout << "========================================\n";
    cout << "         ARVORE AVL - PESSOAS\n";
    cout << "========================================\n";
    cout << " Ponteiro RAIZ: " << (RAIZ != NULL ? RAIZ->pessoa.nome : "NULL") << "\n";
    cout << " Altura da arvore: " << altura(RAIZ) << "\n";
    cout << "========================================\n";
}

void exibirMenu() {
    cout << "\n    >>> MENU PRINCIPAL <<<\n";
    cout << "    ----------------------\n";
    cout << "    F1. INSERCAO\n";
    cout << "    F2. LISTAGEM (Em Ordem)\n";
    cout << "    F3. REMOCAO\n";
    cout << "    F4. CONSULTA\n";
    cout << "    ----------------------\n";
    cout << "    5. Carregar dados exemplo\n";
    cout << "    6. Limpar arvore\n";
    cout << "    0. Sair\n";
    cout << "    ----------------------\n";
    cout << "    Escolha: ";
}

void pausar() {
    cout << "\nPressione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// FUNÇÃO PRINCIPAL
int main() {
    int opcao;
    string nome;
    
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
            case 1: // F1: INSERÇÃO
                {
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
                    cout << "? Pessoa inserida na arvore AVL!\n";
                    pausar();
                }
                break;
                
            case 2: // F2: LISTAGEM
                if (RAIZ == NULL) {
                    cout << "\n? Arvore vazia!\n";
                } else {
                    cout << "\n>>> LISTAGEM EM ORDEM <<<\n";
                    cout << "----------------------------\n";
                    listarEmOrdem(RAIZ);
                    cout << "\nTotal de pessoas: " << altura(RAIZ) << "\n";
                }
                pausar();
                break;
                
            case 3: // F3: REMOÇÃO
                cout << "\n>>> REMOVER PESSOA <<<\n";
                cout << "Nome para remover: ";
                cin.ignore();
                getline(cin, nome);
                
                removerPessoa(nome);
                cout << "? Remocao concluida!\n";
                pausar();
                break;
                
            case 4: // F4: CONSULTA
                cout << "\n>>> CONSULTAR PESSOA <<<\n";
                cout << "Nome para consultar: ";
                cin.ignore();
                getline(cin, nome);
                
                consultarPessoa(nome);
                pausar();
                break;
                
            case 5: // Carregar dados exemplo
                carregarDadosExemplo();
                cout << "\n? Dados exemplo carregados na arvore AVL!\n";
                pausar();
                break;
                
            case 6: // Limpar árvore
                liberarArvore(RAIZ);
                RAIZ = NULL;
                cout << "\n? Arvore limpa!\n";
                pausar();
                break;
                
            case 0: // Sair
                cout << "\nEncerrando programa...\n";
                break;
                
            default:
                cout << "\n? Opcao invalida!\n";
                pausar();
                break;
        }
        
    } while (opcao != 0);
    
    // Liberar memória
    liberarArvore(RAIZ);
    
    return 0;
}
