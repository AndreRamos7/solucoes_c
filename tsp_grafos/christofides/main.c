#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INF 99999

// Estrutura para representar um ponto (coordenada x, coordenada y)
typedef struct {
    double x;
    double y;
} Point;

// Estrutura para representar uma aresta (vértice inicial, vértice final, peso)
typedef struct {
    int src;
    int dest;
    double weight;
} Edge;

// Função para calcular a distância Euclidiana entre dois pontos
double calculateDistance(Point p1, Point p2) {
    double x_diff = p1.x - p2.x;
    double y_diff = p1.y - p2.y;
    return sqrt(x_diff * x_diff + y_diff * y_diff);
}

// Função para encontrar o vértice mais próximo que ainda não foi visitado
int findNearestVertex(double* distance, int* visited, int n) {
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

// Função para construir a árvore mínima utilizando o algoritmo de Prim
void buildMinimumSpanningTree(double** graph, int n, int* parent) {
    double* distance = (double*)malloc(n * sizeof(double));
    int* visited = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        distance[i] = INF;
        visited[i] = 0;
    }

    distance[0] = 0;
    parent[0] = -1;

    for (int i = 0; i < n - 1; i++) {
        int u = findNearestVertex(distance, visited, n);
        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] != 0 && !visited[v] && graph[u][v] < distance[v]) {
                parent[v] = u;
                distance[v] = graph[u][v];
            }
        }
    }

    free(distance);
    free(visited);
}

// Função para verificar se um vértice é ímpar
int isOdd(int num) {
    return num % 2 == 1;
}

// Função para encontrar o vértice ímpar mais próximo
int findClosestOddVertex(double** graph, int n, int vertex) {
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

// Função para criar o grafo semi-euleriano
void createSemiEulerianGraph(double** graph, int n, int* parent) {
    int* oddVertices = (int*)malloc(n * sizeof(int));
    int oddCount = 0;

    for (int i = 0; i < n; i++) {
        if (isOdd(i)) {
            oddVertices[oddCount++] = i;
        }
    }

    for (int i = 0; i < oddCount; i++) {
        int u = oddVertices[i];
        int v = findClosestOddVertex(graph, n, u);
        parent[u] = v;
    }

    free(oddVertices);
}

// Função para encontrar o ciclo euleriano a partir do grafo semi-euleriano
void findEulerianCycle(int startVertex, double** graph, int n, int* parent, int* circuit, int* circuitIndex) {
    int u = startVertex;

    do {
        circuit[(*circuitIndex)++] = u;
        int v = parent[u];
        u = v;
    } while (u != startVertex);
}

// Função para encontrar o caminho do caixeiro viajante utilizando o algoritmo de Christofides
void tspChristofides(Point* points, int n) {
    // Criar o grafo completo com as distâncias entre os pontos
    double** graph = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        graph[i] = (double*)malloc(n * sizeof(double));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = calculateDistance(points[i], points[j]);
        }
    }

    // Construir a árvore mínima utilizando o algoritmo de Prim
    int* parent = (int*)malloc(n * sizeof(int));
    buildMinimumSpanningTree(graph, n, parent);

    // Criar o grafo semi-euleriano
    createSemiEulerianGraph(graph, n, parent);

    // Encontrar o ciclo euleriano
    int* circuit = (int*)malloc((2 * n) * sizeof(int));
    int circuitIndex = 0;
    findEulerianCycle(0, graph, n, parent, circuit, &circuitIndex);

    // Criar o caminho do caixeiro viajante a partir do ciclo euleriano
    int* visited = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    printf("Caminho do Caixeiro Viajante: ");
    for (int i = 0; i < circuitIndex; i++) {
        int vertex = circuit[i];
        if (!visited[vertex]) {
            printf("%d ", vertex);
            visited[vertex] = 1;
        }
    }

    printf("\n");

    // Liberar memória
    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);
    free(parent);
    free(circuit);
   free(visited);
}

int main() {
    int n;
    printf("Digite o número de pontos: ");
    scanf("%d", &n);

    Point* points = (Point*)malloc(n * sizeof(Point));
    printf("Digite as coordenadas dos pontos:\n");
    for (int i = 0; i < n; i++) {
        printf("Ponto %d: ", i);
        scanf("%lf %lf", &(points[i].x), &(points[i].y));
    }

    tspChristofides(points, n);

    free(points);
    return 0;
}