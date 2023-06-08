#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAX_CITIES 100
//#define INFINITY 1000000

// Estrutura para representar uma cidade
typedef struct {
    int x;
    int y;
} City;

// Função para calcular a distância entre duas cidades
double calculateDistance(City city1, City city2) {
    int dx = city1.x - city2.x;
    int dy = city1.y - city2.y;
    return sqrt(dx * dx + dy * dy);
}

// Função para encontrar o índice da cidade mais próxima que ainda não foi visitada
int findNearestCity(bool visited[], double distances[], int numCities) {
    int nearestCity = -1;
    double minDistance = -1;

    for (int i = 0; i < numCities; i++) {
        if (!visited[i] && (minDistance == -1 || distances[i] < minDistance)) {
            nearestCity = i;
            minDistance = distances[i];
        }
    }

    return nearestCity;
}

// Função para encontrar o caminho do caixeiro viajante usando a abordagem dos vizinhos mais próximos
void tspNearestNeighbor(City cities[], int numCities) {
    bool visited[MAX_CITIES] = { false }; // Array para rastrear cidades visitadas
    double distances[MAX_CITIES]; // Array para armazenar as distâncias das cidades mais próximas
    int path[MAX_CITIES]; // Array para armazenar o caminho percorrido

    // Inicialização das distâncias com infinito e do caminho com -1
    for (int i = 0; i < numCities; i++) {
        distances[i] = INFINITY;
        path[i] = -1;
    }

    // Inicialização com a primeira cidade
    visited[0] = true;
    distances[0] = 0;
    path[0] = 0;

    int currentCity = 0;

    // Iteração sobre todas as cidades
    for (int i = 1; i < numCities; i++) {
        // Atualizar as distâncias das cidades não visitadas
        for (int j = 0; j < numCities; j++) {
            if (!visited[j]) {
                double distance = calculateDistance(cities[currentCity], cities[j]);
                if (distance < distances[j]) {
                    distances[j] = distance;
                    path[j] = currentCity;
                }
            }
        }

        // Encontrar a cidade mais próxima que ainda não foi visitada
        int nearestCity = findNearestCity(visited, distances, numCities);

        // Marcar a cidade como visitada e atualizar a cidade atual
        visited[nearestCity] = true;
        currentCity = nearestCity;
    }

    // Imprimir o caminho percorrido
    printf("Caminho do Caixeiro Viajante: ");
    for (int i = 0; i < numCities; i++) {
        printf("%d ", path[i]);
    }
    printf("%d\n", path[0]);
}

int main() {
    int numCities;
    printf("Digite o número de cidades: ");
    scanf("%d", &numCities);

    City cities[MAX_CITIES];

    printf("Digite as coordenadas das cidades:\n");
    for (int i = 0; i < numCities; i++) {
        printf("Cidade %d: ", i);
        scanf("%d %d", &cities[i].x, &cities[i].y);
    }

    tspNearestNeighbor(cities, numCities);

    return 0;
}