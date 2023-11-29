#include <iostream>
#include "Grafo.h"

using namespace std;

    Grafo::Grafo(int max, int valorarestanula, int orientado, int ponderado) //construtor
    {
        numvertices = 0;
        maxvertices = max;
        arestanula = valorarestanula;
        this->orientado = orientado;
        this->ponderado = ponderado;

        vertices = new int[maxvertices];

        matrizadjacencias = new int*[maxvertices];
        for (int i=0 ; i<maxvertices ; i++){
            matrizadjacencias[i] = new int[maxvertices];
        }

        for (int i=0 ; i<maxvertices ; i++){
            for (int j=0 ; j<maxvertices ; j++){
                matrizadjacencias[i][j] = arestanula;
            }
            this->inserevertice(i);
        }
    }

    Grafo::~Grafo() //destrutor
    {
        delete [] vertices;
        for (int i=0 ; i<maxvertices ; i++){
            delete [] matrizadjacencias[i];
        }
        delete [] matrizadjacencias;
    }

    int Grafo::obterindice(int item)
    {
        int indice = 0;
        while (item != vertices[indice]){
            indice++;
        }
        return indice;
    }

    bool Grafo::estacheio()
    {
        return (numvertices == maxvertices);
    }

    void Grafo::inserevertice(int item)
    {
        if (estacheio()){
            cout << "O numero maximo de vertices foi alcancado!\n";
        } else{
            vertices[numvertices] = item;
            numvertices++;
        }
    }

    void Grafo::inserearesta(int Nosaida, int Noentrada, int peso)
    {
        int linha = obterindice(Nosaida);
        int coluna = obterindice(Noentrada);

        matrizadjacencias[linha][coluna] = peso;

        if(this->orientado == 0)
            matrizadjacencias[coluna][linha] = peso; //Remover se for direcionado
    }

    int Grafo::obterpeso(int Nosaida, int Noentrada)
    {
        int linha = obterindice(Nosaida);
        int coluna = obterindice(Noentrada);
        return (matrizadjacencias[linha][coluna]);        
    }

    int Grafo::obtergrau(int item)
    {
        int linha = obterindice(item);
        int grau = 0;
        for (int i=0 ; i<maxvertices ; i++){
            if (matrizadjacencias[linha][i] != arestanula){
                grau++;
            }
        }
        return grau;
    }

    void Grafo::imprimirmatriz()
    {
        cout << "Matriz de adjacencias:\n";
        for (int i=0 ; i<maxvertices ; i++){
            for (int j=0 ; j<maxvertices ; j++){
                cout << matrizadjacencias[i][j] << " ";
            }
            cout << endl;
        }
    }

    void Grafo::imprimirvertices()
    {
        cout << "Lista de Vertices:\n";
        for (int i=0 ; i<numvertices ; i++){
            cout << i << ": " << vertices[i] << endl;
        }
    }