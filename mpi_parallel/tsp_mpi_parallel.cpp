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
		for (int count = (totalPermutations/(num_procs-1))*(meu_ranque-1);
		 count < (totalPermutations/(num_procs-1))*(meu_ranque); count++) {
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
    //PONTOS TURÍSTICOS DE BELÉM
    int n = 11;
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