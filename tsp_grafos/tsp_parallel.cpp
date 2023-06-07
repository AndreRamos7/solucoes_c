#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <omp.h>
using namespace std;
const int infin = numeric_limits<int>::max();
double t_inicio, t_fim;

int tsp(vector<vector<int>>& graph, vector<bool>& visited, int currPos, int n, int count, int cost, int& minCost) {
    if (count == n && graph[currPos][0] != 0) {
        #pragma omp critical
        {
            minCost = min(minCost, cost + graph[currPos][0]);
        }
        return minCost;
    }
    //cout << " -- " << cost;
    
    #pragma omp parallel for num_threads(4) shared(visited,graph,n,minCost)
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && graph[currPos][i] != 0) {
                visited[i] = true;
                tsp(graph, visited, i, n, count + 1, cost + graph[currPos][i], minCost);
                visited[i] = false;
            }
        }
    

    return minCost;
}

int main(int argc, char* argv[]) {
    int n;
    cout << "Digite o número de vértices: ";
    cin >> n;
    //omp_set_num_threads(4);

    vector<vector<int>> graph(n, vector<int>(n));

    cout << "Digite a matriz de adjacência:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> graph[i][j];
        }
        //cout << "Proxima linha" << endl;
    }

    vector<bool> visited(n, false);
    visited[0] = true;
    int minCost = infin;
    
    t_inicio = omp_get_wtime();
    
    tsp(graph, visited, 0, n, 1, 0, minCost);
    
    t_fim = omp_get_wtime();

    cout << "Custo mínimo do percurso: " << minCost << " em " << (t_fim - t_inicio) << endl;

    return 0;
}
