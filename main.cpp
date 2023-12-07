#include <iostream>
#include <fstream>
#include "Grafo.h"

using namespace std;

int main(){

    //Escolhendo qual será a maneira de ler o arquivo e armazenas o grafo
    int opcao,orientado,peso;

    cout << "Digite o tipo de entrada:" << endl;
    cout << "1-Grafos simples, valorados" << endl;
    cout << "2-Digrafos simples, valorados" << endl;
    cin >> opcao;
    if (opcao == 1){
        orientado = 0;
    }else if (opcao == 2){
        orientado = 1;
    }else{
        cout << "Favor digitar uma opcao válida" << endl;
    }

    // Abrindo arquivo de entrada
    ifstream arquivo;
    string nome_arquivo;
    cout << "Digite o nome do arquivo" << endl;
    cin >> nome_arquivo;
    arquivo.open(nome_arquivo, ios::in);
    if(arquivo.is_open()){
        int ordem;
        arquivo >> ordem;
        Grafo grafo1(ordem,orientado);
        for(int i = 0; i < ordem; i++){
            for(int j = 0; j < ordem; j++){
                arquivo >> peso;
                grafo1.inserearesta(i,j,peso);
            }
        }
        grafo1.imprimirvertices();
        grafo1.imprimirmatriz();
        grafo1.busca_largura(0);
        cout << "Busca profundidade: " << endl;
        grafo1.busca_profundidade(0);
        grafo1.dijkstra(6);
        grafo1.prim(5);
        //grafo1.ordenacao_topologica();
    }
    else{
        cout << "erro leitura" << endl;
    }

    arquivo.close();
    /*Grafo g1(5,0,1,1);
    int k = 0;
    for(int i = 0; i < 5; i ++){
        for(int j = 0; j < 5; j ++){
            if(i!=j)
            g1.inserearesta(i,j,i*j+k);
            k++;
        }
    }
    g1.imprimirmatriz();
    g1.ordenacao_topologica();*/
    return 0;
}