#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "io.h"

void write_csv(int **arrs, int quant, char* filename, int max_num, int max_size){
    FILE *fptr = fopen(filename, "w");

    if (fptr == NULL) {
        printf("Erro ao abrir o arquivo de entrada para escrita\n");
        return;
    }

    fprintf(fptr, "index,nums...\n");
    for (int i = 0; i < quant; i++){
        fprintf(fptr, "%d,", i);

        // Como removemos o código de parada (max_num + 10) antes,
        // agora iteramos usando o max_size exato para não ler lixo
        for (int j = 0; j < max_size; j++) {
            if (j < max_size - 1) {
                fprintf(fptr, "%d,", arrs[i][j]);
            } else {
                fprintf(fptr, "%d\n", arrs[i][j]);
            }
        }
    }

    fclose(fptr);
}

char **read_data_input(char* file_name, int quant, int max_num, int max_size){

    FILE *fptr = fopen(file_name, "r");
    if (fptr == NULL) {
        printf("Erro: O arquivo '%s' não foi encontrado ou não pode ser lido.\n", file_name);
        return NULL;
    }

    char **lines = (char **)malloc(quant * sizeof(char *));
    if (lines == NULL){
        printf("Erro ao alocar memória para a matriz do csv\n");
        fclose(fptr);
        return NULL;
    }

    for (int j = 0; j < quant; j++){
        lines[j] = NULL;
    }

    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t length;
    int i = 0;

    while ((length = getline(&buffer, &buffer_size, fptr)) != -1 && i < quant) {
        lines[i] = (char *)malloc((length + 1) * sizeof(char));
        
        if (lines[i] == NULL){
            printf("Erro na alocação de memória para a linha %d\n", i);
            break;
        }

        strcpy(lines[i], buffer);
        i++;
    }

    free(buffer);
    fclose(fptr);

    return lines;
}