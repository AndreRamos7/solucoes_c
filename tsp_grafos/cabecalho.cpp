#include "cabecalho.h"
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;
/* ====================  DEFINI��O DA CLASSE ARESTA ====================== */
Aresta::Aresta(double p, Vertice ini, Vertice fim){
    this->peso = p;
    this->inicio = ini;
    this->fim = fim;
}

double Aresta::getPeso(){
    return this->peso;
}

void Aresta::setPeso(double p){
    this->peso = p;
}

void Aresta::setInicio(Vertice ini){
    this->inicio = ini;
}

void Aresta::setFim(Vertice fim){
    this->fim = fim;
}

Vertice Aresta::getInicio(){    
    return this->inicio;
}

Vertice Aresta::getFim(){
    return this->fim;
}

/* ====================  DEFINI��O DA CLASSE VERTICE ====================== */
Vertice::Vertice(){}

Vertice::Vertice(string dd){
    this->dado = dd;
}

string Vertice::getDado(){
    return this->dado;
}
vector<Aresta> Vertice::getArestasEntrada(){
    return arestasEntrada;

}
vector<Aresta> Vertice::getArestasSaida(){
    return arestasSaida;
}
void Vertice::addArestasEntrada(Aresta are){
    arestasEntrada.push_back(are);
}
void Vertice::addArestasSaida(Aresta ars){
    arestasEntrada.push_back(ars);
}

/* ====================  DEFINI��O DA CLASSE GRAFO ====================== */

Grafo::Grafo(){}

void Grafo::adicionarVertice(string dado){
    Vertice novoVertice(dado);
    vertices.push_back(novoVertice);
}

void Grafo::adicionarAresta(double peso, string dadoInicio, string dadoFim){
    Vertice inicio = getVertice(dadoInicio);
    Vertice fim = getVertice(dadoFim);
    Aresta aresta(peso, inicio, fim);
    inicio.addArestasSaida(aresta);
    fim.addArestasEntrada(aresta);
    arestas.push_back(aresta);
}

Vertice Grafo::getVertice(string dado){
    Vertice vertice;
    for(int i=0; i < this->vertices.size(); i++){
        if (this->vertices[i].getDado() == dado){
            vertice = this->vertices[i];
            break;
        }
    }
    return vertice;
}

void Grafo::buscaEmLargura(){
    vector<Vertice> marcados;
    vector<Vertice> fila;
    Vertice atual = this->vertices[0];
    marcados.push_back(atual);
    cout << atual.getDado() << endl;
    fila.push_back(atual);

    while(fila.size() > 0){
        Vertice visitado = fila[0];
        for(int i=0; i < visitado.getArestasSaida().size(); i++){
            Vertice proximo = visitado.getArestasSaida()[i].getFim();                
            auto results = find(marcados.begin(), marcados.end(), proximo);
            if (/*!marcados.contains(proximo)*/!(results != marcados.end())){ //se o vértice ainda não foi marcado
                cout << "Entrou" << endl;
                marcados.push_back(proximo);
                cout << proximo.getDado() << endl;
                fila.push_back(proximo);
            }
        }
        fila.erase(fila.begin());
    }
}



/* ====================  DEFINI��O DA CLASSE CAIXEIRO ====================== */

Caixeiro::Caixeiro(){

}
vector<string> Caixeiro::getListaVisitas(){
    return lista_visitas;
}
void Caixeiro::visitar(){


}