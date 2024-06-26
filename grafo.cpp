#include <iostream>
#include<vector>
#include <limits>
#include "Grafo.h"

using namespace std;
#define INFINITO std::numeric_limits<int>::max()

    Grafo::Grafo(int ordem, int orientado) //construtor
    {
        this->ordem = ordem;
        this->orientado = orientado;
        num_arestas = 0;

        vertices = new Vertice[ordem];

        matrizadjacencias = new int*[ordem];
        for (int i=0 ; i < ordem ; i++){
            matrizadjacencias[i] = new int[ordem];
        }

        for (int i=0 ; i < ordem ; i++){
            for (int j=0 ; j < ordem ; j++){
                matrizadjacencias[i][j] = 0;
            }
            this->inserevertice(i);
        }
    }

    Grafo::~Grafo() //destrutor
    {
        delete [] vertices;
        for (int i=0 ; i < ordem ; i++){
            delete [] matrizadjacencias[i];
        }
        delete [] matrizadjacencias;
    }

    void Grafo::inserevertice(int vertice)
    {
        Vertice novo;
        novo.id = vertice;
        novo.visitado = 0;
        novo.grau_entrada = 0;
        novo.grau_saida = 0;
        vertices[vertice] = novo;
    }

    void Grafo::inserearesta(int linha, int coluna, int peso)
    {
        Aresta a = {peso,linha, coluna,0};

        if (linha != coluna)
        {
            if (this->orientado == 0 && matrizadjacencias[linha][coluna] == 0)
            {
                matrizadjacencias[linha][coluna] = peso;
                matrizadjacencias[coluna][linha] = peso;
                if (peso != 999)
                {
                    vertices[linha].grau_entrada++;
                    vertices[linha].grau_saida++;
                    vertices[coluna].grau_entrada++;
                    vertices[coluna].grau_saida++;
                    arestas.push_back(a);
                   Aresta a1 = {peso,coluna,linha,0}; // aresta de volta
                    arestas.push_back(a1);
                }
            }
            else if (this->orientado == 1)
            {
                matrizadjacencias[linha][coluna] = peso;
                if (peso != 999)
                {
                    vertices[linha].grau_saida++;
                    vertices[coluna].grau_entrada++;
                    arestas.push_back(a);
                }
            }
        }
    }

    void Grafo::imprimirmatriz()
    {
        cout << "Matriz de adjacencias:\n";
        for (int i=0 ; i<ordem ; i++){
            for (int j=0 ; j<ordem ; j++){
                cout << matrizadjacencias[i][j] << " ";
            }
            cout << endl;
        }
        cout << "Arestas: " << endl;
        for(int i = 0; i < arestas.size(); i++){
            cout << "{" << arestas[i].linha << arestas[i].coluna << "}";
        }
        cout << endl;
    }

    void Grafo::imprimirvertices()
    {
        cout << "Lista de Vertices:\n";
        for (int i=0 ; i<ordem ; i++){
            cout << i << ": " << vertices[i].visitado << endl;
        }
    }
    void Grafo::busca_largura(int vertice_inicial)
    {
        cout << endl << "Busca largura:" << endl;
        setarVisitados();
        vector<int> vertices_visitar;
        int vertice_atual = vertice_inicial;
        vertices_visitar.push_back(vertice_inicial);
        vertices[vertice_inicial].visitado = 1;
        do{
            vertice_atual = vertices_visitar[0];
            cout << vertice_atual << " ";
            vertices_visitar.erase(vertices_visitar.begin());
            for (int i = 0; i < ordem; i++)
            {
                if (matrizadjacencias[vertice_atual][i] != 999 && vertices[i].visitado == 0 && vertice_atual!=i)
                {
                    vertices_visitar.push_back(i);
                    vertices[i].visitado = 1;
                }
            }
        }while(vertices_visitar.size()!=0);
        setarVisitados();
        vertices_visitar.clear();
    }
    void Grafo::busca_profundidade(int vertice_atual) //nao coloquei como restricao grafo não orientado, pois a funcao foi usada na ordenacao topologica
    {
        cout << vertice_atual << " ";
        vertices[vertice_atual].visitado = 1;
        for(int i = 0; i < ordem; i ++){
            if(matrizadjacencias[vertice_atual][i] != 999 && vertices[i].visitado == 0 && vertice_atual != i){
                busca_profundidade(vertices[i].id);
            }
        }
    }
    void Grafo::setarArestas()
    {
        for (int i = 0; i < arestas.size();i++){
            arestas[i].visitado = 0;
        }
    }
    void Grafo::prim(int vertice_inicial)
    {
        setarVisitados();
        vector<Custo> aux; //imprimir arestas;
        cout << "Dijktra: " << endl;
        setarVisitados();
        vector<Aresta> custo;
        Aresta prox = {0,0,0};
        int visitados = 0;
        int total = 0;
        custo.clear();
        int vertice_atual = vertice_inicial;
        for (int i = 0; i < ordem; i++){
            Aresta c;
            c.valor = INFINITO;            
            custo.push_back(c);
            Custo a;
            aux.push_back(a);
        }
        custo[vertice_inicial].valor = 0;
        do{
            for(int i = 0; i < ordem; i ++){
                if(matrizadjacencias[vertice_atual][i]!= 999 && custo[i].valor>matrizadjacencias[vertice_atual][i] && vertice_atual!=i){
                    custo[i].valor = matrizadjacencias[vertice_atual][i];
                    custo[i].linha = vertice_atual;
                    custo[i].coluna = i;
                }
            } vertices[vertice_atual].visitado = 1;
            visitados++;
            prox.valor = INFINITO;
            for(int i = 0; i < custo.size(); i ++){
                if(custo[i].valor<prox.valor && vertices[i].visitado == 0){
                    prox.valor = custo[i].valor;
                    prox.linha = custo[i].linha;
                    prox.coluna = custo[i].coluna;
                    vertice_atual = i;
                }
            }
           if(prox.valor!=INFINITO){
            total+=prox.valor;
            cout << "{" << prox.linha << " " << prox.coluna << "}" << "Peso: " << prox.valor << endl;
            for(int i = 0; i < aux[prox.linha].arestas.size(); i ++){
                aux[prox.coluna].arestas.push_back(aux[prox.linha].arestas[i]);
            }
           aux[prox.coluna].arestas.push_back(prox);
           }
        }while(visitados < ordem);
        cout << "Total:" << total << endl;
        custo.clear();
        setarVisitados();
    }
    void Grafo::setarVisitados()
    {
        for(int i = 0; i < ordem; i++)
        vertices[i].visitado = 0;
    }
    void Grafo::dijkstra(int vertice_inicial) //da certo para orientado e nao orientado
    {
        setarVisitados();
        vector<Custo> aux; //imprimir arestas;
        cout << "Dijktra: " << endl;
        setarVisitados();
        vector<Aresta> custo;
        Aresta prox = {0,0,0};
        int visitados = 0;
        custo.clear();
        int vertice_atual = vertice_inicial;
        for (int i = 0; i < ordem; i++){
            Aresta c;
            c.valor = INFINITO;            
            custo.push_back(c);
            Custo a;
            aux.push_back(a);
        }
        custo[vertice_inicial].valor = 0;
        do{
            for(int i = 0; i < ordem; i ++){
                if(matrizadjacencias[vertice_atual][i]!= 999 && custo[i].valor>matrizadjacencias[vertice_atual][i]+prox.valor && vertice_atual!=i){
                    custo[i].valor = matrizadjacencias[vertice_atual][i]+prox.valor;
                    custo[i].linha = vertice_atual;
                    custo[i].coluna = i;
                }
            } vertices[vertice_atual].visitado = 1;
            visitados++;
            prox.valor = INFINITO;
            for(int i = 0; i < custo.size(); i ++){
                if(custo[i].valor<prox.valor && vertices[i].visitado == 0){
                    prox.valor = custo[i].valor;
                    prox.linha = custo[i].linha;
                    prox.coluna = custo[i].coluna;
                    vertice_atual = i;
                }
            }
           if(prox.valor!=INFINITO){
            for(int i = 0; i < aux[prox.linha].arestas.size(); i ++){
                aux[prox.coluna].arestas.push_back(aux[prox.linha].arestas[i]);
            }
           aux[prox.coluna].arestas.push_back(prox);
           }
        }while(visitados < ordem);
        for (int i = 0; i < ordem; i++){
            cout << "Vertice " << i << ":" << custo[i].valor << " Arestas: ";
            for(int j = 0; j < aux[i].arestas.size(); j++)
            cout << "{" << aux[i].arestas[j].linha << "-" << aux[i].arestas[j].coluna << "}";
            cout << endl;
        }
        custo.clear();
        setarVisitados();
    }

    Aresta *Grafo:: procura_aresta(int linha, int coluna)
    {
        for(int i = 0; i < arestas.size(); i++){
            if(arestas[i].linha == linha && arestas[i].coluna == coluna)
            return &arestas[i];
        }
        return nullptr;
    }

    int Grafo::ciclo_euleriano(int vertice_inicial)
    {
        //conferir se todos os vertices são pares
        for(int i = 0; i < ordem; i ++){
            if(vertices[i].grau_entrada % 2 != 0){
                cout << "Grafo com grau par em algum vertice, nao e possivel ter um ciclo euleriano" << endl;
                return -1;
            }
        }
        cout << "Ciclo euleriano:" << endl;
        setarArestas();
        setarVisitados();
        aux_ciclo_euleriano(vertice_inicial, vertice_inicial,0);
        return 0;
    }

    void Grafo::aux_ciclo_euleriano(int vertice, int vertice_inicial,int num)
    {
        if(vertices[vertice_inicial].visitado == 0){
        Aresta *aux;
        //do{
        int i;
        for (i = 0; i < ordem; i++){
            if (matrizadjacencias[vertice][i] != 999 && vertice != i && vertices[i].visitado == 0){
                if ((vertices[vertice].grau_entrada >= 1 && vertices[i].grau_entrada > 1)|| (vertices[i].grau_entrada == 1 && i == vertice_inicial && vertices[vertice].grau_entrada == 1)){
                aux = procura_aresta(vertice, i);
                if(aux->visitado == 0)
                break;
            }
        }
        }
            if (vertices[vertice].grau_entrada == 1)
                vertices[vertice].visitado = 1;
            aux->visitado = 1;
            cout << aux->linha << "-" << aux->coluna << ":" << num << endl;
            aux = procura_aresta(i, vertice);
            aux->visitado = 1;
            num++;
            vertices[vertice].grau_entrada--;
            vertices[i].grau_entrada--;
            if(num < (arestas.size()/2))
            aux_ciclo_euleriano(i, vertice_inicial,num);
        }
        //}while (vertice != 5);       
    }

    void Grafo::ordenacao_topologica()//da segmentation fault quando o grafo tem ciclo
    {
        vector<int> ordenacao;
        setarVisitados();
        int j = 0;
        do
        {
            for (int i = 0; i < ordem; i++)
            {
                if (vertices[i].grau_entrada == 0 && vertices[i].visitado == 0){
                    ordenacao.push_back(vertices[i].id);
                    vertices[i].visitado = 1;
                }
            }
            cout << ordenacao[j] << " ";
            for(int i = 0; i < ordem; i ++){
                if(matrizadjacencias[ordenacao[j]][i]!=999 && vertices[i].visitado == 0 && vertices[i].grau_entrada>0 && ordenacao[j]!=i){
                    vertices[i].grau_entrada--;
                }
            }
            j++;
        } while(ordenacao.size() < ordem);
        setarVisitados();
        ordenacao.clear();
    }