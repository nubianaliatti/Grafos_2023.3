// Grafo Simples Não-Direcionado ponderado
#include <iostream>

using namespace std;

class Grafo{
    private:
    int arestanula;
    int maxvertices;
    int numvertices;
    int* vertices;
    int** matrizadjacencias;
    int orientado; //0 se não é orientado e 1 se é orientado
    int ponderado; //0 se não é ponderado e 1 se é ponderado

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

};