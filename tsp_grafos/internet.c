#include <stdio.h>
#include <limits.h>

#define V 4 // Número de vértices do grafo

// Função para encontrar a permutação mínima do Caixeiro Viajante
int tsp(int grafo[][V], int partida)
{
    int visitado[V];
    for (int i = 0; i < V; i++)
        visitado[i] = 0;

    visitado[partida] = 1; // Marca o vértice de partida como visitado

    int percursoMinimo = INT_MAX; // Inicializa a variável do percurso mínimo

    // Função auxiliar para encontrar a permutação mínima do Caixeiro Viajante
    int tspUtil(int grafo[][V], int partida, int visitado[], int percursoAtual, int cont)
    {
        if (cont == V && grafo[partida][percursoAtual] > 0)
            return grafo[partida][percursoAtual];

        for (int i = 0; i < V; i++)
        {
            if (visitado[i] == 0 && grafo[partida][i] > 0)
            {
                visitado[i] = 1;
                int custo = grafo[partida][i] + tspUtil(grafo, i, visitado, percursoAtual, cont + 1);
                if (custo < percursoMinimo)
                    percursoMinimo = custo;
                visitado[i] = 0;
            }
        }

        return percursoMinimo;
    }

    return tspUtil(grafo, partida, visitado, partida, 1);
}

// Função principal
int main()
{
    int grafo[V][V] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}};

    int partida = 0; // Vértice de partida

    int menorPercurso = tsp(grafo, partida);

    printf("Menor percurso: %d\n", menorPercurso);

    return 0;
}