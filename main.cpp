#include <iostream>
#include <fstream>
#include "Grafo.h"

using namespace std;

int main(){

    int opcao,orientado,ponderado,peso;
    cout << "Digite o tipo de entrada:" << endl;
    cout << "1-Grafos simples, não-valorados e não-orientados" << endl;
    cout << "2-Digrafos simples, não-valorados" << endl;
    cout << "3-Digrafos simples, valorados" << endl;
    cout << "4-Grafos simples, valorados" << endl;
    cin >> opcao;
    if (opcao == 1){
        orientado = 0;
        ponderado = 0;
    }else if (opcao == 2){
        orientado = 1;
        ponderado = 0;
    }else if (opcao == 3){
        orientado = 1;
        ponderado = 1;
    }else if(opcao == 4){
        orientado = 0;
        ponderado = 1;
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
        Grafo grafo1(ordem,0,orientado,ponderado);
        for(int i = 0; i < ordem; i++){
            for(int j = 0; j < ordem; j++){
                arquivo >> peso;
                grafo1.inserearesta(i,j,peso);
            }
        }
        grafo1.imprimirvertices();
        grafo1.imprimirmatriz();
        //grafo1.busca_largura(0);
        //cout << "Busca profundidade: " << endl;
        //grafo1.busca_profundidade(0);
        //grafo1.dijkstra(6,0);
        grafo1.ordenacao_topologica(0);
    }
    else{
        cout << "erro leitura" << endl;
    }

    arquivo.close();
    /*Grafo g1(200,0,0,1);
    for(int i = 0; i < 200; i ++){
        for(int j = 0; j < 200; j ++){
            if(i!=j)
            g1.inserearesta(i,j,i*j+2);
        }
    }
    g1.dijkstra(80,100);*/
    return 0;
}