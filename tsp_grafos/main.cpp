#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include "cabecalho.h"

using namespace std;

int main(){
    int n = 0;
    string nome = "";
    Grafo grafo;

    grafo.adicionarVertice("Joao");
    grafo.adicionarVertice("Lorenzo");
    grafo.adicionarVertice("Creuza");
    grafo.adicionarVertice("Creber");
    grafo.adicionarVertice("Craudio");
    
    grafo.adicionarAresta(2.0, "Joao", "Lorenzo");
    grafo.adicionarAresta(3.0, "Lorenzo", "Creber");
    grafo.adicionarAresta(1.0, "Creber", "Creuza");
    grafo.adicionarAresta(1.0, "Joao", "Creuza");
    grafo.adicionarAresta(3.0, "Craudio", "Joao");
    grafo.adicionarAresta(2.0, "Craudio", "Lorenzo");
    grafo.buscaEmLargura(0);
/*
    vector<string> nomes = {"André", "Andrey", "Andressa", "Anderson"};

    cout << "digite um nome\n";
    cin >> nome;
    if(find(nomes.begin(), nomes.end(), nome) != nomes.end()){
        cout << "Contem" << endl;
    }else{
        cout << "Nao Contem" << endl;
    }
    //cout << "Resultado do quadrado de " << n << " é igual a: " << n*n << endl;
    */


    return 0;

}