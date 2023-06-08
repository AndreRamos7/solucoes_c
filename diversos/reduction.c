#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#define SOMA_INICIAL 1000

int main(int argc, char* argv[]){
    int i, n = 25;
    int a[n], soma;
    int ref = SOMA_INICIAL + ((n-1)*n)/2;

    omp_set_num_threads(4);

    for(i = 0; i < n; i++)
        a[i] = i;
    soma = SOMA_INICIAL;
    printf("Valor da soma antes da região paralela: %d\n", soma);

    #pragma omp parallel default(none) shared(n,a) reduction(+:soma)
    {
        soma = 0;
        #pragma omp for
            for(i = 0; i < n; i++)
                soma += a[i];
        printf("Valor da soma na Thread: %d é igual %d\n", omp_get_thread_num(), soma);

    }
    printf("Valor da soma depois da região paralela: %d\n", soma);
    printf("Verificação do resultado: soma %d (deveria ser %d)\n", soma, ref);
    return 0;
}