#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<string.h>
#include<math.h>
#include<mpi.h>


int primo(long int);
int max(int, int);

int main(int argc, char* argv[]){
    int n = 0, x, qtdPrimos = 0;
    double t_inicial, t_final;
    int rank, size;
    int total = 0;
    char msg[200];

    if(argc < 2){
        printf("Valor de parametro indefinido\n");
        return 0;
    }else{
        n = strtol(argv[1], (char**) NULL, 10);        
    }

    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int parte = n / (size-1);

    if(rank != 0){
        for(x = max((parte*(rank-1)+1),3); x < parte*(rank); x += 2){
            if(primo(x) == 1){
                qtdPrimos++;
            }
        }  
        //sprintf(msg, "Mensagem enviada do processo %d\n", rank);
        MPI_Send(&qtdPrimos, 1, MPI_INT , 0, 99, MPI_COMM_WORLD);  
        qtdPrimos = 0;
    }else{// rank = 0
        
        for(int i = 1; i < size; i++){
            MPI_Recv(&qtdPrimos, 1, MPI_INT, i, 99, MPI_COMM_WORLD, &status);
            total += qtdPrimos;
            printf("mensagem recebida do processo %d: %d\n", i, qtdPrimos);
        }
    }

    MPI_Finalize();

    printf("%d primos\n", total);

    return 0;
}

int primo(long int n){
    long int i = 0;
    for(i = 3; i < (sqrt(n) - 1); i += 2)
        if(n % i == 0)
            return 0;                
    return 1;
}
int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}