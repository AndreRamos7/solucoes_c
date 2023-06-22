#include<stdlib.h>
#include<stdio.h>
#include<omp.h>
#define NN 100
#define N 100

void exibe_vetor(int[], int);

int main(int argc, char *argv[])
{
	int secao = 0, impares = 0, pares = 0;
	int vImpar[N], vPar[N], soma[N], subtracao[N];
	double ts1_fim, ts1_inicio, ts2_fim, ts2_inicio, t_sub, t_soma;


	/*Inicializando os vetores Impares e pares*/
	for (int i=0; i < N*2; i++){
		//printf("%d %d\n", impares, pares);
		if(i % 2 == 0){
			vPar[pares] = i;
			pares++;
		}else{
			vImpar[impares] = i;
			impares++;		
		}
	}

/*
	for (int i=0; i < N*2;i++){
		if(i % 2 != 0){
			vImpar[impares] = i;
			impares++;		
		}
	}*/
	#pragma omp parallel //default (none) shared(secao) private(t_soma, t_sub, ts1_inicio, ts2_inicio, ts1_fim, ts2_fim, vPar, vImpar, soma, subtracao)
	{
		#pragma omp sections
		{
			#pragma omp section
			{
				ts1_inicio = omp_get_wtime();
				for (int i=0; i<N; i++){
					soma[i] = vPar[i] + vImpar[i];					
				}
				ts1_fim = omp_get_wtime();
				t_soma = ts1_fim - ts1_inicio;
				#pragma omp critical (secao_1)
				{
					secao++;
					printf("tempo da seção %d = %lf\n", secao, t_soma);
				}
				
			}
			#pragma omp section
			{	
				ts2_inicio = omp_get_wtime();
				for (int i=0; i<N; i++){
					subtracao[i] = vPar[i] - vImpar[i];				
				}
				ts2_fim = omp_get_wtime();
				t_sub = ts2_fim - ts2_inicio;
				#pragma omp critical (secao_2)
				{
					secao++;
					printf("tempo da seção %d = %lf\n", secao, t_sub);
				}
			}
		}
	}

	//t_soma = ts1_fim - ts1_inicio;
	//t_sub = ts2_fim - ts2_inicio;

	int tamanho = sizeof(vPar) /sizeof(vPar[0]);
	printf("%d\n", tamanho);
	printf("========== vetores impares e pares ===========\n");
	exibe_vetor(vPar, N);
	exibe_vetor(vImpar, N);
	
	printf("========== vetores soma e subtração ===========\n");
	exibe_vetor(soma, N);
	exibe_vetor(subtracao, N);

	printf("========== imformações da execução paralela ===========\n");
	//printf("%lf, %lf", t_soma, t_sub);
	

}

void exibe_vetor(int vetor[], int n){
	for(int i = 0; i < n; i++){
		printf("%d, ", vetor[i]);
	}
	printf("\n");
}