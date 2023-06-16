#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <mpi.h>

using namespace std;

const int INF = numeric_limits<int>::max();
double t_inicio, t_fim;

int fatorial(int);
void mostrar_permutacao(vector<int>);


int caixeiroViajanteForcaBruta(const vector<vector<int>>& grafo, int n, double* t_inicio, double* t_fim) {
    const int totalPermutations = fatorial(n-1)/2;
    cout << "totalPermutations: " << totalPermutations << endl;
    int menorCusto = INF;
    vector<int> permutacao;

    // Cria uma permutação inicial dos vértices
    for (int i = 1; i < n; i++) {
        permutacao.push_back(i);
    }
    	int meu_ranque, num_procs;
	int origem, destino = 0, etiq = 1;
	char mensagem[200];
	int menor_custo;
	MPI_Status estado;
	/* Chamada inicial para o MPI */
	MPI_Init(NULL, NULL); /* Determina o ranque e número de processos em execução */

	MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);


	if (meu_ranque != destino) {
		*t_inicio = MPI_Wtime();

		// Testa todas as permutações possíveis
		for (int count = (totalPermutations/num_procs)*(meu_ranque-1);
		 count < (totalPermutations/num_procs)*(meu_ranque); count++) {
		    int custo = 0;

		    // Calcula o custo da permutação atual
		    int origem = 0; // Vértice de origem (inicial)

		    for (int i = 0; i < n - 1; i++) {
		        int destino = permutacao[i];
		        custo += grafo[origem][destino];
		        origem = destino;
		    }
		    // Adiciona o custo do último vértice de volta à origem
		    custo += grafo[origem][0];

		    // Atualiza o menor custo, se necessário

		    menorCusto = min(menorCusto, custo);


		    //mostrar_permutacao(permutacao);
		    next_permutation(permutacao.begin(), permutacao.end());
		}
		
		*t_fim = MPI_Wtime();

		//sprintf(mensagem, "%d", menorCusto);

		MPI_Send(&menorCusto, 1, MPI_INT, destino, etiq, MPI_COMM_WORLD);
	}else {
		/* Processo com ranque 0 recebe num_procs-1 mensagens */
		for (origem = 1; origem < num_procs; origem++) {
			MPI_Recv(&menor_custo, 1, MPI_INT, origem, etiq, MPI_COMM_WORLD, &estado);
			/* Imprime as mensagens recebidas */
			printf("menor_custo = %d\n", menor_custo);
		}
	}

    MPI_Finalize();

    return menorCusto;
}

int main(int argc, char* argv[]) {
	/*int n = 6;
    vector<vector<int>> grafo = {
        {0,1545,2450,2789,3866,4396},
        {1545,0,1897,2905,3936,3759},
        {2450,1897,0,1114,2131,1973},
        {2789,2905,1114,0,1144,1917},
        {3866,3936,2131,1144,0,1758},
        {4396,3759,1973,1917,1758,0}
    };*/
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

    int menorCaminho = caixeiroViajanteForcaBruta(grafo, n, &t_inicio, &t_fim);


    cout << "O menor caminho no problema do Caixeiro Viajante é: " << menorCaminho << " em "
    << (t_fim - t_inicio) << "s" << endl;

    return 0;
}


int fatorial(int n){
    int fat;
    if ( n <= 1 )
        return (1);
    else{
       return n * fatorial(n - 1);
    }
}

void mostrar_permutacao(vector<int> perm){
    for(int i = 0; i < perm.size(); i++)
        cout << perm.at(i) << "-";
    cout << endl;
}