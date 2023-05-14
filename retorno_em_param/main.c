#include <stdio.h>
#include <stdlib.h>


void retornarPorParam(int* a, int *b){
	*a = 345;
	*b = 50;
}

int main(void){
    int num = 1202;
	int a, b;
    int* pont = &num;
    int** pontPont = &pont;
	    
    printf("%d\n", pont);
    printf("%d\n", pontPont);
	
	retornarPorParam(&a, &b);
	printf("%d %d", a, b);

    
    return 0;
}

