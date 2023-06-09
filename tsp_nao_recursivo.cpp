#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <omp.h>

using namespace std;

const int INF = numeric_limits<int>::max();
double t_inicio, t_fim;
int totalPermutations;

double fatorial(int n){
    double fat;
    if ( n <= 1 )
        return (1);
    else{
       return n * fatorial(n - 1);
    }
}

int caixeiroViajanteForcaBruta(const vector<vector<int>>& grafo, int n) {
    totalPermutations = fatorial(n);
    int menorCusto = INF;

    // Cria uma permutação inicial dos vértices
    vector<int> permutacao;
    for (int i = 1; i < n; i++) {
        permutacao.push_back(i);
    }
    
    // Testa todas as permutações possíveis
    for (int count = 0; count < totalPermutations; count++) {
        int custo = 0;

        // Calcula o custo da permutação atual
        int origem = 0; // Vértice de origem (inicial)
        for (int i = 0; i < n - 1; i++) {
            int destino = permutacao[i];
            custo += grafo[origem][destino];
            origem = destino;
        }

        // Adiciona o custo do último vértice de volta à origem
        custo += grafo[origem][0];

        // Atualiza o menor custo, se necessário
        menorCusto = min(menorCusto, custo);

        next_permutation(permutacao.begin(), permutacao.end());
        
    } 

    return menorCusto;
}

int main(int argc, char* argv[]) {
    omp_set_num_threads(argc);
    int n = 6;
    vector<vector<int>> grafo = {
        {0,1545,2450,2789,3866,4396},
        {1545,0,1897,2905,3936,3759},
        {2450,1897,0,1114,2131,1973},
        {2789,2905,1114,0,1144,1917},
        {3866,3936,2131,1144,0,1758},
        {4396,3759,1973,1917,1758,0}
    };/*
    int n = 11;
    vector<vector<int>> grafo = {
        {0,1545,2450,2789,3866,4396,1234,5431,4545,1594,2131},
        {1545,0,1897,2905,3936,3759,2211,5285,3574,1232,2312},
        {2450,1897,0,1114,2131,1973,1235,2105,7538,158,21598},
        {2789,2905,1114,0,1144,1917,1235,4545,12455,1231,3221},
        {3866,3936,2131,1144,0,1758,2554,24544,1234,4878,566},
        {4396,3759,1973,1917,1758,0,1597,2558,5452,65454,1234},
        {1234,2211,1235,1235,2554,1597,0,2547,2548,2310,6541},
        {5431,5285,2105,4545,24544,2558,2547,0,5421,2123,35789},
        {4545,3574,7538,12455,1234,5452,2548,5421,0,1698,1559},
        {1594,1232,158,1231,4878,65454,2310,2123,1698,0,3541},
        {2131,2312,21598,3221,566,1234,6541,35789,1559,3541,0}

    };*/
    
    t_inicio = omp_get_wtime();
    int menorCaminho = caixeiroViajanteForcaBruta(grafo, n);
    t_fim = omp_get_wtime();

    cout << "O menor caminho no problema do Caixeiro Viajante é: " << menorCaminho << " em " 
    << (t_fim - t_inicio) << "s" << endl;

    return 0;
}