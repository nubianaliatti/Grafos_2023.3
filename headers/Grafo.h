// Grafo Simples Não-Direcionado ponderado
#include <iostream>
#include <vector>

using namespace std;

typedef struct { 
    int id;
    int visitado;
    int grau_entrada;
    int grau_saida;
} Vertice;

typedef struct { 
    int valor;
    int linha;
    int coluna;
    int visitado;
} Aresta;
typedef struct { 
    vector<Aresta> arestas;
} Custo;
class Grafo{
    private:
    int ordem;
    Vertice* vertices;
    int** matrizadjacencias;
    int num_arestas;
    void setarVisitados();

    public:
    Grafo(int ordem, int orientado);
    ~Grafo();
    int orientado; //0 se não é orientado e 1 se é orientado
    void inserevertice(int vertice);
    void inserearesta(int linha, int coluna, int peso);
    void imprimirmatriz();
    void imprimirvertices();
    void busca_largura(int vertice_inicial);
    vector<Aresta> arestas;
    void busca_profundidade(int vertice_atual); 
    void prim(int vertice_inicial);
    void dijkstra(int vertice_inicial);
    void ordenacao_topologica();
    int ciclo_euleriano(int vertice_inicial);
    void aux_ciclo_euleriano(int vertice,int vertice_inicial,int num);
    void restaura_graus();
    Aresta * procura_aresta(int linha, int coluna);
    void setarArestas();
};