#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <omp.h>

using namespace std;

const int INF = numeric_limits<int>::max();

int caixeiroViajanteParallel(const vector<vector<int>>& grafo, int n) {
    int menorCusto = INF;

    #pragma omp parallel shared(menorCusto)
    {
        int threadMenorCusto = INF;

        #pragma omp for nowait
        for (int origem = 0; origem < n; origem++) {
            vector<bool> visitado(n, false);
            vector<int> caminho;
            caminho.push_back(origem);
            visitado[origem] = true;

            int custoParcial = 0;
            int cidadeAtual = origem;

            for (int i = 0; i < n - 1; i++) {
                int cidadeMaisProxima = -1;
                int menorDistancia = INF;

                // Encontra a cidade não visitada mais próxima
                for (int j = 0; j < n; j++) {
                    if (!visitado[j] && grafo[cidadeAtual][j] < menorDistancia) {
                        cidadeMaisProxima = j;
                        menorDistancia = grafo[cidadeAtual][j];
                    }
                }

                visitado[cidadeMaisProxima] = true;
                caminho.push_back(cidadeMaisProxima);
                custoParcial += menorDistancia;
                cidadeAtual = cidadeMaisProxima;
            }

            custoParcial += grafo[cidadeAtual][origem];

            if (custoParcial < threadMenorCusto) {
                threadMenorCusto = custoParcial;
            }
        }

        #pragma omp critical
        {
            if (threadMenorCusto < menorCusto) {
                menorCusto = threadMenorCusto;
            }
        }
    }

    return menorCusto;
}

int main(int argc, char* argv[]) {
    omp_set_num_threads(argc);
    int n = 11;
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
    double t_inicio = omp_get_wtime();
    int menorCaminho = caixeiroViajanteParallel(grafo, n);
    double t_fim = omp_get_wtime();
    cout << "O menor caminho no problema do Caixeiro Viajante é: " << menorCaminho << " em " 
    << (t_fim - t_inicio) << "s" << endl;

    return 0;
}
