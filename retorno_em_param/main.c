#include <stdio.h>
#include <stdlib.h>


void retornarPorParam(int* a, int *b){
	*a = 345;
	*b = 50;
}

int main(void){
    int num = 1202;
    int* pont = &num;
    int** pontPont = &pont;
	int a, b;
	    
    printf("pont = %d\n", pont);
    printf("*pont = %d\n", *pont);
    printf("pontPont = %d\n", pontPont);
    printf("*pontPont = %d\n", *pontPont);
    printf("**pontPont = %d\n", **pontPont);
	
	retornarPorParam(&a, &b);
	printf("%d %d", a, b);

    
    return 0;
}

