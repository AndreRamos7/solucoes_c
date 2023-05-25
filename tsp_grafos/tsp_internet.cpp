#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

const int INF = std::numeric_limits<int>::max();

int tsp(std::vector<std::vector<int>>& graph, std::vector<bool>& visited, int currPos, int n, int count, int cost, int& minCost) {
    if (count == n && graph[currPos][0] != 0) {
        minCost = std::min(minCost, cost + graph[currPos][0]);
        return minCost;
    }

    for (int i = 0; i < n; ++i) {
        if (!visited[i] && graph[currPos][i] != 0) {
            visited[i] = true;
            tsp(graph, visited, i, n, count + 1, cost + graph[currPos][i], minCost);
            visited[i] = false;
        }
    }

    return minCost;
}

int main() {
    int n;
    std::cout << "Digite o número de cidades: ";
    std::cin >> n;

    std::vector<std::vector<int>> graph(n, std::vector<int>(n));

    std::cout << "Digite a matriz de adjacência:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> graph[i][j];
        }
    }

    std::vector<bool> visited(n, false);
    visited[0] = true;
    int minCost = INF;

    tsp(graph, visited, 0, n, 1, 0, minCost);

    std::cout << "Custo mínimo do percurso: " << minCost << std::endl;

    return 0;
}