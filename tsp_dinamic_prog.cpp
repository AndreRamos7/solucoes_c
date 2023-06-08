#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int INF = 1e9; // Valor grande o suficiente

int caixeiroViajante(const vector<vector<int>>& grafo, int n) {
    vector<vector<int>> dp(1 << n, vector<int>(n, INF));
    dp[1][0] = 0;

    for (int mask = 1; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if ((mask & (1 << i)) == 0)
                continue;

            for (int j = 0; j < n; j++) {
                if ((mask & (1 << j)) == 0 || i == j)
                    continue;

                int prevMask = mask ^ (1 << i);
                dp[mask][i] = min(dp[mask][i], dp[prevMask][j] + grafo[j][i]);
            }
        }
    }

    int minCost = INF;
    int finalMask = (1 << n) - 1;
    for (int i = 1; i < n; i++) {
        minCost = min(minCost, dp[finalMask][i] + grafo[i][0]);
    }

    return minCost;
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

    int menorCaminho = caixeiroViajante(grafo, n);
    if (menorCaminho == INF) {
        cout << "Não existe caminho que visite todos os vértices." << endl;
    } else {
        cout << "O menor caminho no problema do Caixeiro Viajante é: " << menorCaminho << endl;
    }

    return 0;
}