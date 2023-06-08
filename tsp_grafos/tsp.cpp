#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;
const int infin = numeric_limits<int>::max();

int tsp(vector<vector<int>>& grafo, vector<bool>& visited, int currPos, int n, int count, int cost, int& custoMin) {
    if (count == n && grafo[currPos][0] != 0) {
        custoMin = min(custoMin, cost + grafo[currPos][0]);
        return custoMin;
    }
    //cout << " -- " << cost;

    for (int i = 0; i < n; ++i) {
        if (!visited[i] && grafo[currPos][i] != 0) {
            visited[i] = true;
            tsp(grafo, visited, i, n, count + 1, cost + grafo[currPos][i], custoMin);
            visited[i] = false;
        }
    }

    return custoMin;
}

int main() {
    int n;
    cout << "Digite o número de vértices: ";
    cin >> n;

    vector<vector<int>> grafo(n, vector<int>(n));

    cout << "Digite a matriz de adjacência:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grafo[i][j];
        }
        //cout << "Proxima linha" << endl;
    }

    vector<bool> visited(n, false);
    visited[0] = true;
    int custoMin = infin;

    tsp(grafo, visited, 0, n, 1, 0, custoMin);

    cout << "Custo mínimo do percurso: " << custoMin << endl;

    return 0;
}