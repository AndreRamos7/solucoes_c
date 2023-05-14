#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* substituir(const char* s, const char* oldW,
                  const char* newW);


int main() {
    FILE *file_i, * file_o;
    char linha[31], word[3], rpl[3];
	char* result;

    file_i = fopen("Tfile.csv", "r+"); // abre o arquivo em modo de leitura e escrita
	file_o = fopen("arquivo_saida.csv", "w+");

	puts("digite uma palavra de busca");
	scanf("%s", word);
	//fgets(word, 3, stdin);
	// removes the newline character from the string
	word[strlen(word) - 1] = word[strlen(word)];
	

	puts("digite uma palavra para substituir");
	//fgets(rpl, 3, stdin);
	scanf("%s", rpl);
	// removes the newline character from the string
	rpl[strlen(rpl) - 1] = rpl[strlen(rpl)];

	while (!feof(file_i)) { 
		fgets(linha, 31, file_i); // lê a primeira linha do arquivo

		result = substituir(linha, word, rpl);

		//fseek(file_i, 0, SEEK_SET); // volta para o início da linha no arquivo
		fputs(result, file_o); // escreve a linha modificada no arquivo
	}

    fclose(file_i); // fecha o arquivo
	fclose(file_o); // fecha o arquivo

    return 0;
}


char* substituir(const char* s, const char* oldW,
                  const char* newW)
{
    char* result;
    int i, cnt = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);
  
    // Counting the number of times old word
    // occur in the string
    for (i = 0; s[i] != '\0'; i++) {
        if (strstr(&s[i], oldW) == &s[i]) {
            cnt++;  
            // Jumping to index after the old word.
            i += oldWlen - 1;
        }
    }
  
    // Making new string of enough length
    result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1);
  
    i = 0;
    while (*s) {
        // compare the substring with the result
        if (strstr(s, oldW) == s) {
            strcpy(&result[i], newW);
            i += newWlen;
            s += oldWlen;
        }
        else
            result[i++] = *s++;
    }
  
    result[i] = '\0';
    return result;
}