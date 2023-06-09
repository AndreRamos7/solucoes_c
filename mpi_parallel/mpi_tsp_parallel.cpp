#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <mpi.h>

using namespace std;

const int INF = numeric_limits<int>::max();

int calcularCusto(const vector<vector<int>>& grafo, const vector<int>& caminho) {
    int custo = 0;
    int n = caminho.size();

    for (int i = 0; i < n - 1; i++) {
        int origem = caminho[i];
        int destino = caminho[i + 1];
        custo += grafo[origem][destino];
    }

    int origem = caminho[n - 1];
    int destino = caminho[0];
    custo += grafo[origem][destino];

    return custo;
}

int caixeiroViajanteMPI(const vector<vector<int>>& grafo, int numCidades) {
    int numProcessos, idProcesso;
    MPI_Comm_size(MPI_COMM_WORLD, &numProcessos);
    MPI_Comm_rank(MPI_COMM_WORLD, &idProcesso);

    vector<int> caminho(numCidades);
    for (int i = 0; i < numCidades; i++) {
        caminho[i] = i;
    }

    int menorCustoGlobal = INF;

    do {
        int custoParcial = calcularCusto(grafo, caminho);

        int menorCustoParcial;
        MPI_Reduce(&custoParcial, &menorCustoParcial, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

        if (idProcesso == 0 && menorCustoParcial < menorCustoGlobal) {
            menorCustoGlobal = menorCustoParcial;
        }

        MPI_Bcast(&menorCustoGlobal, 1, MPI_INT, 0, MPI_COMM_WORLD);

    } while (next_permutation(caminho.begin() + 1, caminho.end()));

    return menorCustoGlobal;
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    double t_inicio, t_fim;
    

    int idProcesso;
    MPI_Comm_rank(MPI_COMM_WORLD, &idProcesso);
/*
    int numCidades = 6;
    vector<vector<int>> grafo = {
        {0,1545,2450,2789,3866,4396},
        {1545,0,1897,2905,3936,3759},
        {2450,1897,0,1114,2131,1973},
        {2789,2905,1114,0,1144,1917},
        {3866,3936,2131,1144,0,1758},
        {4396,3759,1973,1917,1758,0}
    };
    
    //PONTOS TURÍSTICOS DE BELÉM
    int numCidades = 11;
    vector<vector<int>> grafo = {
        {0,17730,2180,7170,8890,570,2530,5760,10140,1470,1120},
        {17730,0,19640,23450,15710,17300,17730,15620,10790,19140,17700},
        {2180,19640,0,6060,10180,2640,3130,6840,12050,778,2240},
        {7170,23450,6060,0,10490,7230,5900,7950,13590,3920,6480},
        {8890,15710,10180,10490,0,9620,5200,1650,5110,8210,6410},
        {570,17300,2640,7230,9620,0,2140,5140,9910,1930,821},
        {2530,17730,3130,5900,5200,2140,0,3560,9040,3090,1410},
        {5760,15620,6840,7950,1650,5140,3560,0,5710,6710,4810},
        {10140,10790,12050,13590,5110,9910,9040,5710,0,11590,9910},
        {1470,19140,778,3920,8210,1930,3090,6710,11590,0,1800},
        {1120,17700,2240,6480,6410,821,1410,4810,9910,1800,0}
    };
*/

    int numCidades = 11;
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

    };
    
    t_inicio = MPI_Wtime();
    int menorCaminho = caixeiroViajanteMPI(grafo, numCidades);
    t_fim = MPI_Wtime();
    
    if (idProcesso == 0) {
        cout << "O menor caminho no problema do Caixeiro Viajante é: " << menorCaminho << ". em " << (t_fim - t_inicio) << "s" << endl;
    }

    MPI_Finalize();

    return 0;
}
