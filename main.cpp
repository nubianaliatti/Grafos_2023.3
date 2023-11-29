#include <iostream>
#include <fstream>
#include "Grafo.h"

using namespace std;

int main(int argc, char const *argv[]){

    // Abrindo arquivo de entrada
    ifstream arquivo;
    arquivo.open(argv[1], ios::in);
    if(arquivo.is_open()){
        int ordem,opcao,orientado,ponderado,peso;;
        arquivo >> ordem;
        cout << "Digite o tipo de entrada:" << endl;
        cout << "1-Grafos simples, não-valorados e não-orientados" << endl;
        cout << "2-Digrafos simples, não-valorados" << endl;
        cout << "3-Digrafos simples, valorados" << endl;
        cin >> opcao;
        if(opcao == 1){
            orientado = 0;
            ponderado = 0;
        }else if (opcao == 2){
            orientado = 1;
            ponderado = 0;
        }else if (opcao == 3){
            orientado = 1;
            ponderado = 1;
        }else{
            cout << "Favor digitar uma opcao válida" << endl;
        }
        Grafo grafo1(ordem,0,orientado,ponderado);
        for(int i = 0; i < ordem; i++){
            for(int j = 0; j < ordem; j++){
                arquivo >> peso;
                grafo1.inserearesta(i,j,peso);
            }
        }
        grafo1.imprimirvertices();
        grafo1.imprimirmatriz();
    }
    else{
        cout << "erro leitura" << endl;
    }
    /*int max, valorarestanula;
    cout << "Digite a quantidade maxima de vertices:\n";
    cin >> max;
    cout << "Digite o valor para representar a ausencia de aresta:\n";
    cin >> valorarestanula;
    Grafo grafo1(max, valorarestanula);
    TipoItem item1, item2;
    int opcao, valor, peso;

    do{
        cout << "Digite 0 para parar o algoritmo!\n";
        cout << "Digite 1 para inserir um vertice!\n";
        cout << "Digite 2 para inserir uma aresta!\n";
        cout << "Digite 3 para imprimir o grau de um vertice!\n";
        cout << "Digite 4 para imprimir o peso de uma aresta!\n";
        cout << "Digite 5 para imprimir a matriz de adjacencias!\n";
        cout << "Digite 6 para imprimir a lista de vertices!\n";
        cin >> opcao;

        if (opcao == 1){
            cout << "Digite o elemento do vertice que sera inserido:\n";
            cin >> item1;
            grafo1.inserevertice(item1);
        } else if (opcao == 2){
            cout << "Digite o vertice de saida:\n";
            cin >> item1;
            cout << "Digite o vertice de entrada:\n";
            cin >> item2;
            cout << "Digite o peso desta aresta:\n";
            cin >> peso;
            grafo1.inserearesta(item1, item2, peso);
        } else if (opcao == 3){
            cout << "Digite o vertice que sera calculado o grau:\n";
            cin >> item1;
            valor = grafo1.obtergrau(item1);
            cout << "O grau desse vertice e: " << valor << endl;
        } else if (opcao == 4){
            cout << "Digite o vertice de saida:\n";
            cin >> item1;
            cout << "Digite o vertice de entrada:\n";
            cin >> item2;
            valor = grafo1.obterpeso(item1, item2);
            cout << "O peso dessa aresta e: " << valor << endl;
        } else if (opcao == 5){
            grafo1.imprimirmatriz();
        } else if (opcao == 6){
            grafo1.imprimirvertices();
        }
    } while (opcao != 0);*/

    arquivo.close();
    return 0;
}