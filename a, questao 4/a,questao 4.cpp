#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

class No {
public:
    int valor;
    int cont; // contador de repeticoes
    No* esq;
    No* dir;

    No(int v) {
        valor = v;
        cont = 1;
        esq = NULL;
        dir = NULL;
    }
};

class ArvoreBST {
private:
    No* raiz;

    No* inserir(No* no, int v) {
        if (no == NULL) {
            return new No(v);
        }
        if (v < no->valor) {
            no->esq = inserir(no->esq, v);
        } else if (v > no->valor) {
            no->dir = inserir(no->dir, v);
        } else {
            // valor repetido
            no->cont++;
        }
        return no;
    }

    No* menorNo(No* no) {
        while (no != NULL && no->esq != NULL)
            no = no->esq;
        return no;
    }

    No* remover(No* no, int v) {
        if (no == NULL) return no;

        if (v < no->valor) {
            no->esq = remover(no->esq, v);
        } else if (v > no->valor) {
            no->dir = remover(no->dir, v);
        } else {
            if (no->cont > 1) {
                no->cont--;
                return no;
            }

            if (no->esq == NULL) {
                No* temp = no->dir;
                delete no;
                return temp;
            } else if (no->dir == NULL) {
                No* temp = no->esq;
                delete no;
                return temp;
            }

            No* temp = menorNo(no->dir);
            no->valor = temp->valor;
            no->cont = temp->cont;
            temp->cont = 1;
            no->dir = remover(no->dir, temp->valor);
        }
        return no;
    }

    void emOrdem(No* no) {
        if (no != NULL) {
            emOrdem(no->esq);
            cout << no->valor << "(" << no->cont << ") ";
            emOrdem(no->dir);
        }
    }

public:
    ArvoreBST() {
        raiz = NULL;
    }

    void inserir(int v) {
        raiz = inserir(raiz, v);
    }

    void remover(int v) {
        raiz = remover(raiz, v);
    }

    void mostrar() {
        if (raiz == NULL) {
            cout << "Arvore vazia!\n";
        } else {
            cout << "\n========================================\n";
            cout << "            ARVORE ATUAL\n";
            cout << "========================================\n";
            cout << "Valores ordenados: ";
            emOrdem(raiz);
            cout << "\n\nOBSERVACOES SOBRE REPETICOES:\n";
            cout << "----------------------------------------\n";
            
            // Coletar e mostrar informações sobre repetições
            vector<pair<int, int> > ocorrencias;
            coletarOcorrencias(raiz, ocorrencias);
            
            bool temRepeticao = false;
            for (vector<pair<int, int> >::iterator it = ocorrencias.begin(); it != ocorrencias.end(); ++it) {
                if (it->second > 1) {
                    cout << "- Valor " << it->first << " aparece " << it->second << " vezes\n";
                    temRepeticao = true;
                }
            }
            
            if (!temRepeticao) {
                cout << "Nenhum valor repetido encontrado.\n";
            }
            
            cout << "========================================\n";
        }
    }

    void coletarOcorrencias(No* no, vector<pair<int, int> >& ocorrencias) { // CORREÇÃO: espaço entre > >
        if (no != NULL) {
            coletarOcorrencias(no->esq, ocorrencias);
            ocorrencias.push_back(make_pair(no->valor, no->cont));
            coletarOcorrencias(no->dir, ocorrencias);
        }
    }

    void mostrarSequenciaOriginal() {
        cout << "\nSEQUENCIA ORIGINAL CARREGADA:\n";
        cout << "{10, 5, 15, 3, 7, 12, 18, 7, 10, 15, 15}\n";
        cout << "\nLOCALIZACAO DAS REPETICOES:\n";
        cout << "- 7: posicoes 5 e 8\n";
        cout << "- 10: posicoes 1 e 9\n"; 
        cout << "- 15: posicoes 3, 10 e 11\n";
    }

    void carregarPadrao() {
        int valores[] = {10, 5, 15, 3, 7, 12, 18, 7, 10, 15, 15};
        int tamanho = sizeof(valores) / sizeof(valores[0]);
        for (int i = 0; i < tamanho; i++) {
            inserir(valores[i]);
        }
    }
};

void menu() {
    cout << "=====================================\n";
    cout << "        ARVORE BINARIA DE BUSCA      \n";
    cout << "=====================================\n";
    cout << "1 - Inserir valor\n";
    cout << "2 - Remover valor\n";
    cout << "3 - Mostrar arvore (em ordem)\n";
    cout << "4 - Mostrar sequencia original\n";
    cout << "0 - Sair\n";
    cout << "=====================================\n";
    cout << "Escolha uma opcao: ";
}

int main() {
    ArvoreBST arvore;
    int opcao, valor;

    // Carrega automaticamente alguns numeros
    arvore.carregarPadrao();

    do {
        system("cls");
        menu();
        cin >> opcao;

        switch (opcao) {
        case 1:
            cout << "Digite o valor para inserir: ";
            cin >> valor;
            arvore.inserir(valor);
            cout << "Valor inserido com sucesso!\n";
            system("pause");
            break;

        case 2:
            cout << "Digite o valor para remover: ";
            cin >> valor;
            arvore.remover(valor);
            cout << "Remocao concluida!\n";
            system("pause");
            break;

        case 3:
            cout << "\nArvore atual:\n";
            arvore.mostrar();
            system("pause");
            break;

        case 4:
            arvore.mostrarSequenciaOriginal();
            system("pause");
            break;

        case 0:
            cout << "Encerrando o programa...\n";
            break;

        default:
            cout << "Opcao invalida!\n";
            system("pause");
            break;
        }
    } while (opcao != 0);

    return 0;
}
