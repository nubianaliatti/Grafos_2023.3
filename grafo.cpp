#include <iostream>
#include<vector>
#include <limits>
#include "Grafo.h"

using namespace std;
#define INFINITO std::numeric_limits<int>::max()

    Grafo::Grafo(int max, int valorarestanula, int orientado, int ponderado) //construtor
    {
        numvertices = 0;
        maxvertices = max;
        arestanula = valorarestanula;
        this->orientado = orientado;
        this->ponderado = ponderado;
        num_arestas = 0;

        vertices = new Vertice[maxvertices];

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
        while (item != vertices[indice].id){
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
            Vertice novo;
            novo.id = item;
            novo.visitado = 0;
            novo.grau_entrada = 0;
            novo.grau_saida = 0;
            vertices[numvertices] = novo;
            numvertices++;

        }
    }

    void Grafo::inserearesta(int Nosaida, int Noentrada, int peso)
    {
        if (Nosaida != Noentrada){
            int linha = obterindice(Nosaida);
            int coluna = obterindice(Noentrada);
            Posicoes p = {linha, coluna};

            if (this->orientado == 0 && this->ponderado == 0 && peso == 1){
                matrizadjacencias[linha][coluna] = peso;
                matrizadjacencias[coluna][linha] = peso;
                vertices[linha].grau_entrada++;
                vertices[linha].grau_saida++;
                vertices[coluna].grau_entrada++;
                vertices[coluna].grau_saida++;
                posicoes_arestas.push_back(p);
                Posicoes p1 = {coluna, linha}; // aresta de volta
                posicoes_arestas.push_back(p1);

            }else if (this->orientado == 1 && this->ponderado == 0 && peso == 1){
                matrizadjacencias[linha][coluna] = peso;
                vertices[linha].grau_saida++;
                vertices[coluna].grau_entrada++;
                posicoes_arestas.push_back(p);

            }else if (this->orientado == 1 && this->ponderado == 1 && peso != 999){
                matrizadjacencias[linha][coluna] = peso;
                posicoes_arestas.push_back(p);
                vertices[linha].grau_saida++;
                vertices[coluna].grau_entrada++;
            }else if (this->orientado == 0 && this->ponderado == 1){
                matrizadjacencias[linha][coluna] = peso;
                matrizadjacencias[coluna][linha] = peso;
                posicoes_arestas.push_back(p);
                Posicoes p1 = {coluna, linha}; // aresta de volta
                posicoes_arestas.push_back(p1);
                vertices[linha].grau_entrada++;
                vertices[linha].grau_saida++;
                vertices[coluna].grau_entrada++;
                vertices[coluna].grau_saida++;
        }
    }
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
        cout << "Arestas: " << endl;
        for(int i = 0; i < posicoes_arestas.size(); i++){
            cout << "{" << posicoes_arestas[i].x << posicoes_arestas[i].y << "}";
        }
        cout << endl;
    }

    void Grafo::imprimirvertices()
    {
        cout << "Lista de Vertices:\n";
        for (int i=0 ; i<numvertices ; i++){
            cout << i << ": " << vertices[i].visitado << endl;
        }
    }
    void Grafo::busca_largura(int vertice_inicial)
    {
        vector<int> vertices_visitar;
        int vertice_atual = vertice_inicial;
        vertices_visitar.push_back(vertice_inicial);
        vertices[vertice_inicial].visitado = 1;
        do{
            vertice_atual = vertices_visitar[0];
            cout << vertice_atual << " ";
            vertices_visitar.erase(vertices_visitar.begin());
            for(int i = 0; i < maxvertices; i ++){
                if(ponderado == 0){
                    if(matrizadjacencias[vertice_atual][i] == 1 && vertices[i].visitado == 0){
                        vertices_visitar.push_back(i);
                        vertices[i].visitado = 1;
                    }
                }else{
                    if(matrizadjacencias[vertice_atual][i] != 999 && vertices[i].visitado == 0){
                        vertices_visitar.push_back(i);
                        vertices[i].visitado = 1;
                    }
                }
            }
        }while(vertices_visitar.size()!=0);
        vertices_visitar.clear();
    }
    void Grafo::busca_profundidade(int vertice_atual)
    {
        cout << vertice_atual << " ";
        vertices[vertice_atual].visitado = 1;
        for(int i = 0; i < maxvertices; i ++){
            if(matrizadjacencias[vertice_atual][i] != 0 && vertices[i].visitado == 0){
                busca_profundidade(vertices[i].id);
            }
        }
    }
    void Grafo::arvore_steiner ()
    {
        /*int qtd;
        cout << "Digite quantos vertices terminais:";
        cin >> qtd;
        vector<Terminal> terminais;
        Terminal terminal;
        for(int i = 0; i < qtd; i ++){
            cout << "Digite o " << i+1 << "vertice terminal:";
            cin >> terminal.id;
            terminal.terminal = 1;
            terminais.push_back(terminal);
        }
        setarVisitados();
        vector<int> custo;
        int visitados = 0;
        int prox = 0;
        custo.clear();
        int vertice_atual = vertice_inicial;
        for (int i = 0; i < maxvertices; i++){
            custo.push_back(INFINITO);
        }
        custo[vertice_inicial] = 0;
        do{
            for(int i = 0; i < maxvertices; i ++){
                if(matrizadjacencias[vertice_atual][i]!=0 && custo[i]>matrizadjacencias[vertice_atual][i]+prox){
                    custo[i] = matrizadjacencias[vertice_atual][i]+prox;
                }
            } vertices[vertice_atual].visitado = 1;
            visitados++;
            prox = INFINITO;
            for(int i = 0; i < custo.size(); i ++){
                if(custo[i]<prox && vertices[i].visitado == 0){
                    prox = custo[i];
                    vertice_atual =i;
                }
            }
        }while(visitados < maxvertices);
        cout << custo[vertice_final] << endl;
        custo.clear();*/
    }
    void Grafo::prim(int vertice_inicial)
    {
        cout << "Prim: " << endl;
        setarVisitados();
        vector<int> custo;
        int visitados = 0;
        int prox;
        int custo_total = 0;
        custo.clear();
        int vertice_atual = vertice_inicial;
        for (int i = 0; i < maxvertices; i++){
            custo.push_back(INFINITO);
        }
        custo[vertice_inicial] = 0;
        do{
            prox = INFINITO;
            vertices[vertice_atual].visitado = 1;
            visitados++;
            for(int i = 0; i < maxvertices; i ++){
                if(matrizadjacencias[vertice_atual][i]!=0 && custo[i]>matrizadjacencias[vertice_atual][i] && vertices[i].visitado == 0){
                    custo[i] = matrizadjacencias[vertice_atual][i];
                }
            }
            for(int i = 0; i < custo.size(); i ++){
                        if(custo[i]<prox && vertices[i].visitado == 0){
                            prox = custo[i];
                            vertice_atual = i;
                        }
                    }
            if(prox!=INFINITO)
            custo_total+=prox;
        }while(visitados != maxvertices);
        cout << custo_total << endl;
    }
    void Grafo::setarVisitados()
    {
        for(int i = 0; i < maxvertices; i++)
        vertices[i].visitado = 0;
    }
    void Grafo::dijkstra(int vertice_inicial, int vertice_final)
    {
        cout << "Dijktra: " << endl;
        setarVisitados();
        vector<int> custo;
        int visitados = 0;
        int prox = 0;
        custo.clear();
        int vertice_atual = vertice_inicial;
        for (int i = 0; i < maxvertices; i++){
            custo.push_back(INFINITO);
        }
        custo[vertice_inicial] = 0;
        do{
            for(int i = 0; i < maxvertices; i ++){
                if(matrizadjacencias[vertice_atual][i]!=0 && custo[i]>matrizadjacencias[vertice_atual][i]+prox){
                    custo[i] = matrizadjacencias[vertice_atual][i]+prox;
                }
            } vertices[vertice_atual].visitado = 1;
            visitados++;
            prox = INFINITO;
            for(int i = 0; i < custo.size(); i ++){
                if(custo[i]<prox && vertices[i].visitado == 0){
                    prox = custo[i];
                    vertice_atual =i;
                }
            }
        }while(visitados < maxvertices);
        cout << custo[vertice_final] << endl;
        custo.clear();
    }
    void Grafo::ordenacao_topologica(int vertice_inicial)
    {
        vector<int> ordenacao;
        setarVisitados();
        int j = 0;
        do
        {
            for (int i = 0; i < maxvertices; i++)
            {
                if (vertices[i].grau_entrada == 0 && vertices[i].visitado == 0){
                    ordenacao.push_back(vertices[i].id);
                    vertices[i].visitado = 1;
                }
            }
            cout << ordenacao[j] << " ";
            for(int i = 0; i < maxvertices; i ++){
                if(matrizadjacencias[ordenacao[j]][i]!=0 && vertices[i].visitado == 0 && vertices[i].grau_entrada>0){
                    vertices[i].grau_entrada--;
                }
            }
            j++;
        } while(ordenacao.size() < maxvertices);
    }