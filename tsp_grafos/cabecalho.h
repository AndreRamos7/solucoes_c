#ifndef CABECALHO_H
#define CABECALHO_H

#include<string>
#include<vector>

using namespace std;
class Aresta; // necessário redeclarar antes pois Vertice chama Aresta e vice-versa

class Vertice{
    private:
        string dado;        
        vector<Aresta> arestasEntrada;
        vector<Aresta> arestasSaida;
    public:
        Vertice();
        Vertice(string);
        string getDado();
        vector<Aresta> getArestasEntrada();
        vector<Aresta> getArestasSaida();
        void adicionarArestasEntrada(Aresta);
        void adicionarArestasSaida(Aresta);
        bool operator==(const Vertice &other) const {
            return dado == other.dado /*&& row == other.row*/;
        };
        ~Vertice() { };    
        /*friend class Grafo;    
        friend class Aresta;    */
};
class Aresta{
    private:
        int peso;
        Vertice inicio, fim;
    public:
        Aresta();
        Aresta(double, Vertice, Vertice);
        double getPeso();
        Vertice getInicio();
        Vertice getFim();
        void setPeso(double);
        void setInicio(Vertice);
        void setFim(Vertice);
        ~Aresta() {} ;
        /*friend class Grafo;   
        friend class Vertice;   */
};


class Grafo{
    private:
        vector<Vertice> vertices;
        vector<Aresta> arestas;
    public:
        Grafo();
        void adicionarVertice(string);
        void adicionarAresta(double, string, string);
        Vertice getVertice(string);
        void buscaEmLargura(int);        
        ~Grafo(){};
       /* friend class Aresta;   
        friend class Vertice;   */
};


class Caixeiro{
    private:
        vector<string> lista_visitas;
    public:
        Caixeiro();;
        vector<string> getListaVisitas();
        void visitar();

};
#endif