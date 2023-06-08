#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

#define INF std::numeric_limits<double>::infinity()

struct Point {
    double x;
    double y;
};

struct Edge {
    int src;
    int dest;
    double weight;
};

double calculateDistance(Point p1, Point p2) {
    double x_diff = p1.x - p2.x;
    double y_diff = p1.y - p2.y;
    return std::sqrt(x_diff * x_diff + y_diff * y_diff);
}

int findNearestVertex(std::vector<double>& distance, std::vector<bool>& visited, int n) {
    int nearestVertex = -1;
    double minDistance = INF;

    for (int i = 0; i < n; i++) {
        if (!visited[i] && distance[i] < minDistance) {
            nearestVertex = i;
            minDistance = distance[i];
        }
    }

    return nearestVertex;
}

void buildMinimumSpanningTree(std::vector<std::vector<double>>& graph, int n, std::vector<int>& parent) {
    std::vector<double> distance(n, INF);
    std::vector<bool> visited(n, false);

    distance[0] = 0;
    parent[0] = -1;

    for (int i = 0; i < n - 1; i++) {
        int u = findNearestVertex(distance, visited, n);
        visited[u] = true;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] != 0 && !visited[v] && graph[u][v] < distance[v]) {
                parent[v] = u;
                distance[v] = graph[u][v];
            }
        }
    }
}

bool isOdd(int num) {
    return num % 2 == 1;
}

int findClosestOddVertex(std::vector<std::vector<double>>& graph, int n, int vertex) {
    int closestVertex = -1;
    double minDistance = INF;

    for (int i = 0; i < n; i++) {
        if (vertex != i && isOdd(i) && graph[vertex][i] < minDistance) {
            closestVertex = i;
            minDistance = graph[vertex][i];
        }
    }

    return closestVertex;
}

void createSemiEulerianGraph(std::vector<std::vector<double>>& graph, int n, std::vector<int>& parent) {
    std::vector<int> oddVertices;
    for (int i = 0; i < n; i++) {
        if (isOdd(i)) {
            oddVertices.push_back(i);
        }
    }

    for (int i = 0; i < oddVertices.size(); i++) {
        int u = oddVertices[i];
        int v = findClosestOddVertex(graph, n, u);
        parent[u] = v;
    }
}

void findEulerianCycle(int startVertex, std::vector<std::vector<double>>& graph, int n, std::vector<int>& parent, std::vector<int>& circuit) {
    int u = startVertex;

    do {
        circuit.push_back(u);
        int v = parent[u];
        u = v;
    } while (u != startVertex);
}

void tspChristofides(std::vector<Point>& points) {
    int n = points.size();

    std::vector<std::vector<double>> graph(n, std::vector<double>(n, 0.0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = calculateDistance(points[i], points[j]);
        }
    }

    std::vector<int> parent(n, -1);
    buildMinimumSpanningTree(graph, n, parent);

    createSemiEulerianGraph(graph, n, parent);

    std::vector<int> circuit;
    findEulerianCycle(0, graph, n, parent, circuit);

    std::vector<bool> visited(n, false);

    std::cout << "Caminho do Caixeiro Viajante: ";
    for (int i = 0; i < circuit.size(); i++) {
        int vertex = circuit[i];
        if (!visited[vertex]) {
            std::cout << vertex << " ";
            visited[vertex] = true;
        }
    }
    std::cout << std::endl;
}

int main() {
    int n;
    std::cout << "Digite o número de pontos: ";
    std::cin >> n;

    std::vector<Point> points(n);
    std::cout << "Digite as coordenadas dos pontos:\n";
    for (int i = 0; i < n; i++) {
        std::cout << "Ponto " << i << ": ";
        std::cin >> points[i].x >> points[i].y;
    }

    tspChristofides(points);

    return 0;
}