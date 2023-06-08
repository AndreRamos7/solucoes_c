#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

int caixeiroViajanteForcaBruta(const vector<vector<int>>& grafo, int n) {
    // Cria uma permutação inicial dos vértices
    vector<int> permutacao;
    for (int i = 1; i < n; i++) {
        permutacao.push_back(i);
    }

    int menorCusto = INF;

    // Testa todas as permutações possíveis
    do {
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
    } while (next_permutation(permutacao.begin(), permutacao.end()));

    return menorCusto;
}

int main() {
    int n = 6;
    vector<vector<int>> grafo = {
        {0,1545,2450,2789,3866,4396},
        {1545,0,1897,2905,3936,3759},
        {2450,1897,0,1114,2131,1973},
        {2789,2905,1114,0,1144,1917},
        {3866,3936,2131,1144,0,1758},
        {4396,3759,1973,1917,1758,0}
    };

    int menorCaminho = caixeiroViajanteForcaBruta(grafo, n);
    cout << "O menor caminho no problema do Caixeiro Viajante é: " << menorCaminho << endl;

    return 0;
}