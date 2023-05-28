#include "cabecalho.h"
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;
/* ====================  DEFINIÇÃO DA CLASSE ARESTA ====================== */
Aresta::Aresta(){}
Aresta::Aresta(double p, Vertice ini, Vertice fm):peso(p),inicio(ini),fim(fm){}

double Aresta::getPeso(){
    return peso;
}

void Aresta::setPeso(double p){
    peso = p;
}

void Aresta::setInicio(Vertice ini){
    inicio = ini;
}

void Aresta::setFim(Vertice fm){
    fim = fm;
}

Vertice Aresta::getInicio(){    
    return inicio;
}

Vertice Aresta::getFim(){
    return fim;
}

/* ====================  DEFINIçãO DA CLASSE VERTICE ====================== */
Vertice::Vertice(){}

Vertice::Vertice(string dd):dado(dd){}

string Vertice::getDado(){
    return dado;
}
vector<Aresta> Vertice::getArestasEntrada(){
    return arestasEntrada;
}
vector<Aresta> Vertice::getArestasSaida(){
    return arestasSaida;
}
void Vertice::adicionarArestasEntrada(Aresta are){
    arestasEntrada.push_back(are);
    //cout << "arestasEntrada.size() = " << getArestasEntrada().size() << endl;
}
void Vertice::adicionarArestasSaida(Aresta ars){
    arestasSaida.push_back(ars);
    //cout << "arestasSaida.size() = " << getArestasSaida().size() << endl;
}

/* ====================  DEFINIÇÃO DA CLASSE GRAFO ====================== */

Grafo::Grafo(){}

void Grafo::adicionarVertice(string dado){
    Vertice novoVertice(dado);
    vertices.push_back(novoVertice);
}

void Grafo::adicionarAresta(double peso, string dadoInicio, string dadoFim){
    Vertice inicio = getVertice(dadoInicio);
    Vertice fim = getVertice(dadoFim);
    /*cout << "inicio: " << inicio.getDado() << endl;
    cout << "fim: " << fim.getDado() << endl;*/
    Aresta aresta(peso, inicio, fim);
    inicio.adicionarArestasSaida(aresta);
    fim.adicionarArestasEntrada(aresta);
    arestas.push_back(aresta);
}

Vertice Grafo::getVertice(string dado){
    Vertice vertice;
    for(int i = 0; i < vertices.size(); i++){
        if (vertices.at(i).getDado() == dado){
            //cout << "encontrou " << dado << endl;
            vertice = vertices.at(i);
            break;
        }
    }
    return vertice;
}

void Grafo::buscaEmLargura(int origem){
    
    vector<Vertice> marcados;
    vector<Vertice> fila;
    Vertice atual = vertices.at(origem);
    marcados.push_back(atual);
    cout << "Nome = " << atual.getDado() << endl;
    fila.push_back(atual);
    cout << "Comprimento da fila = " << fila.size() << endl;

    while(fila.size() > 0){
        vector<Aresta> a = atual.getArestasSaida();
        cout << "\n atual.getArestasSaida().size() = " << a.size() << endl;
        
        Vertice visitado = fila.at(origem);
        //cout << "\nvisitado = " << visitado.getDado();
        //cout << "\nvisitado.getArestasSaida().at(0).getPeso() = " << visitado.getArestasSaida().at(0).getPeso() << endl;
        for(int i = 0; i < visitado.getArestasSaida().size(); i++){
            cout << "Entrou no for" << endl;
            Vertice proximo = visitado.getArestasSaida().at(i).getFim();                
            auto results = find(marcados.begin(), marcados.end(), proximo);
            if (/*!marcados.contains(proximo) !(results != marcados.end())*/true){ //se o vértice ainda não foi marcado
                
                marcados.push_back(proximo);
                cout << proximo.getDado() << endl;
                fila.push_back(proximo);
            }
        }
        fila.erase(fila.begin());
    }
}



/* ====================  DEFINIÇÃO DA CLASSE CAIXEIRO ====================== */

Caixeiro::Caixeiro(){

}
vector<string> Caixeiro::getListaVisitas(){
    return lista_visitas;
}
void Caixeiro::visitar(){


}