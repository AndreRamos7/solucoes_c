// C program to find and replace a word
// in a File by another given word
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
// Function to find and
// replace a word in File
void findAndReplaceInFile()
{    
    char word[100], ch, read[100], replace[100];
    int word_len, i, p = 0;
 
    
    puts("\n\nEnter the word to find:");
    fgets(word, 100, stdin);

    for(int i = 0; i < strlen(word); i++){
	    printf("%d - %c\n", i, word[i]);
    }
    printf("word[strlen(word)-2] = %c\n", word[strlen(word)-2]);
    printf("word[0] = %c\n", word[0]);
    printf("strlen(word) = %d\n", (int) strlen(word));
    printf("word[strlen(word)] = %c\n", word[strlen(word)]);
    // removes the newline character from the string
    word[strlen(word) - 1] = word[strlen(word)];
    printf("%s\n", word);

    puts("Enter the word to replace it with :");
    fgets(replace, 100, stdin);
 
    // removes the newline character from the string
    replace[strlen(replace) - 1] = replace[strlen(replace)];

    char str[] ="This is a simple string";
    char * pch;
    pch = strstr (str,"simple");
    if (pch != NULL)
        strncpy (pch,"sample",6);
    puts (str);
    return 0;
 
    
}
 
void testes(){
    char string[100];
    char ch1;
    char ch2;
    int x, tam;

    printf ("Digite uma frase:\n");
    gets(string);
    printf ("Digite alguma letra q exista na frase acima:\n");
    scanf ("%c", &ch1);
    printf ("Digite alguma letra q exista ou nao na frase acima:\n");
    scanf (" %c", &ch2);
    tam=strlen(string);
    for (x=0;x<tam;x++){
        if (string[x]==ch1){ // Comparação usando dois símbolos de igual (==)
            string[x]=ch2; // Você quer substituir a letra dentro da string, e não a variável ch1
        }
    }
    printf ("%s", string);

}

// Driver code
int main()
{
    testes();

    //findAndReplaceInFile();
    return 0;
}
