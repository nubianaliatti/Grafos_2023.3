// Grafo Simples Não-Direcionado ponderado
#include <iostream>
#include <vector>

using namespace std;

typedef struct { //posicoes da matriz que simbolizam arestas -> facilitar buscas
    int x;
    int y;
} Posicoes; 
typedef struct { 
    int id;
    int visitado;
    int grau_entrada;
    int grau_saida;
} Vertice;
class Grafo{
    private:
    int ordem;
    Vertice* vertices;
    int** matrizadjacencias;
    int orientado; //0 se não é orientado e 1 se é orientado
    int num_arestas;
    void setarVisitados();

    public:
    Grafo(int ordem, int orientado);
    ~Grafo();
    void inserevertice(int vertice);
    void inserearesta(int linha, int coluna, int peso);
    void imprimirmatriz();
    void imprimirvertices();
    void busca_largura(int vertice_inicial);
    vector<Posicoes> posicoes_arestas;
    void busca_profundidade(int vertice_atual); 
    void prim(int vertice_inicial);
    void dijkstra(int vertice_inicial);
    void ordenacao_topologica();
};