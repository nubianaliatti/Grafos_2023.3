// Grafo Simples Não-Direcionado ponderado
#include <iostream>
#include <vector>

using namespace std;

typedef struct { //posicoes da matriz que simbolizam arestas -> facilitar buscas
    int x;
    int y;
} Posicoes; 
typedef struct { //posicoes da matriz que simbolizam arestas -> facilitar buscas
    int id;
    int visitado;
} Vertice; 

class Grafo{
    private:
    int arestanula;
    int maxvertices;
    int numvertices;
    Vertice* vertices;
    int** matrizadjacencias;
    int orientado; //0 se não é orientado e 1 se é orientado
    int ponderado; //0 se não é ponderado e 1 se é ponderado
    int num_arestas;
    void setarVisitados();

    public:
    Grafo(int max, int valorarestanula, int orientado, int ponderado);
    ~Grafo();
    int obterindice(int item);
    bool estacheio();
    void inserevertice(int item);
    void inserearesta(int Nosaida, int Noentrada, int peso);
    int obterpeso(int Nosaida, int Noentrada);
    int obtergrau(int item);
    void imprimirmatriz();
    void imprimirvertices();
    void busca_largura(int vertice_inicial);
    vector<Posicoes> posicoes_arestas;
    void busca_profundidade(int vertice_atual);
    void prim(int vertice_inicial);
    void dijkstra(int vertice_inicial, int vertice_final);
    void arvore_steiner ();

};