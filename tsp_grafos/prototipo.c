typedef struct no No;
struct no {//vertice ligados a um vertice em forma de lista encadeada
  int rotulo; //nome da aresta
  int peso;  //peso da ligação dela
  No *prox;   //endereço da proxima aresta ligada ao vertice
};
typedef struct lista *Lista;
struct lista {
  No **A;                          //este apontador apota para umas lsita de elementos que representam os vertices, para o qual o vertice esta ligado.
  int n;                      // numero de vertices
  int m;                     // numero de arestas
};

typedef struct caminho *Caminho;
struct caminho{
int distancia;                   //peso total do caminho
No *pri;                 //primeiro vertice do caminho
}
Custo(Lista L){
    int cinza[L ->n]; //essa lista recebe o numero de vertices do grafo para que possamos checar quais vertices já foram visatados e não os repetir
    int cont = 0;  //esse parametro é um contador de quantos nos já foram visitados
    int no = 0; // esse é o primeiro no que vamos visitar
    
    
    //agora podemos explorar o grafo para encontrar os caminhos

    explorar(L -> [0], cont, cinza, no)                //essa função explora os vertices começando pelo vertice 0 como vamos começar incrementamos para dizer que estamos no primeiro vertice

}

explorar(No L, int cont, int cinza [], int no ){
    No *i; // essa variavel vai nos auxiliar a acessar outros vertics do grafo
    int igual = 0;
    Caminho comparador, comparado; //Essas duas variaveis comparam dois caminhos para encontra um mais eficiente
    
    cinza[cont] == no; //adicionamos o no do caminho a nossa lista de checados


    if(cont == L -> n){         //caso tenhamos percorrido todos os elementos da lista podemos criar um caminho com a soma dos custos dos elementos
        Caminho C = CriarCaminho()
        No primeiro; //criamos um tipo no para ser o primeiro no do nosso caminho
        primeiro->rotulo no; //para esse primeiro só precisamos identificar o rotulo já que ele não aponta para nada, e não precisa ter custo já que a soma dos custos esta esta na estrutura caminho
        C -> pri = primeiro;
        return C;
    }

    comparadoR = CriarCaminho();
    comparadoR -> distancia = 200000000;
    /*Para compara os caminho nos criaremos um cujo o custo seja o mais alto possive, assim na primeira comparação validade o parametro sera trocado
    caso a funão não tenha percorrido o grafo todo e nem encontrado um caminho para outro vertice,
     ele retorna um caminho com o peso maximo pemitido por um inteiro assim caso qualquer caminho é melhor que ele*/


    for(p = L->A[no]; p != NULL; p = p->prox){ //este nó vai verificar todoso os vertices que o nó tem ligação
        for(int i = 0; i < l ->n;i++){ //Esse laço percorre o array para verificar se o vertice já foi adicionado ao caminho
            if(p -> rotulo == i){ //caso ele já esteja então a variavel igual é incrementada
                igual++;
            }      
        }
        if(igual < 0){ //sifnifica que este vertice não foi adicionado ao caminho
            comparado = explorar( p, cont++, cinza, l->p->rotulo);// então usamos a recursividade para ver o tamanho do caminho do proximo vertice
            comparado->distancia += p->prox ->peso; //o peso do proximo vertice é adicionado a distancia do caminho
            if(comparado->distancia < comparadoR->distancia){
                comparadoR = comparado;
            }
        }
        igual--; //zeramos o contador que indica repetição de vertice
    }
    /*ao Fim do processo o menor caminho valido sera selecionado*/

     i -> rotulo = 0; //ele Recebe a aresta inicial como aresta primaria
     comparadoR -> pri = i;
     return comparadoR; // e é retornado;
}