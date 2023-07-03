#include<stdio.h>
#include<stdlib.h>
#include<math.h>


int primo(long int);

int main(int argc, char* argv[]){
    int n = 0, qtdPrimos = 0;
    double t_inicial, t_final;
    if(argc < 2){
        printf("Valor de parametro indefinido\n");
        return 0;
    }else{
        n = strtol(argv[1], (char**) NULL, 10);        
    }

    //printf("digite um numero\n");
    //scanf("%d", &n);   
    
    for(int x = 3; x < n; x += 2){
        if(primo(x) == 1){
            qtdPrimos++;
        }
    }    

    printf("%d primos", qtdPrimos);

    return 0;
}

int primo(long int n){
    long int i = 0;
    for(i = 3; i < (sqrt(n) - 1); i += 2)
        if(n % i == 0)
            return 0;                
    return 1;
}