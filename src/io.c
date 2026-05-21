#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"


char **read_data_input(char* file_name, int rows){

    FILE *fptr;
    char buffer[10010];
    char **lines = (char **)malloc(rows * sizeof(char *));

    if (lines == NULL){
        printf("Erro ao alocar memória para o csv");
        return NULL;
    }

    fptr = fopen(file_name, "r");

    if (fptr == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return NULL;
    }

    int i = 0;

    while (fgets(buffer, 10000, fptr) != NULL && i < rows) {
        int length = strlen(buffer);
        lines[i] = malloc((length + 1) * sizeof(char));
        if (lines[i] != NULL) 
            strcpy(lines[i], buffer);
            
        i++;
    }

    fclose(fptr);

    return lines;
}
