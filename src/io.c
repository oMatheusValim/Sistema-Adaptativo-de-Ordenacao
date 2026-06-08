#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "io.h"


void write_csv(int **arrs, int quant, char* filename, int max_num){
    FILE *fptr;

    fptr = fopen(filename, "w");

    if (fptr == NULL) {
        printf("Erro ao abrir o arquivo de entrada\n");
        return;
    }

    fprintf(fptr, "index,nums...\n");
    for (int i = 0; i < quant; i++){
        fprintf(fptr, "%d,", i);

        int j = 0;
        int size = sizeof(arrs[i]) / sizeof(arrs[i][0]);

        while(arrs[i][j] <= max_num){
            if (arrs[i][j+1] <= max_num)
                fprintf(fptr, "%d,", arrs[i][j]);

            else{
                fprintf(fptr, "%d\n", arrs[i][j]);
                break;
            }

            j++;
        }
    }

    fclose(fptr);
}

char **read_data_input(char* file_name, int quant, int max_num, int max_size){

    FILE *fptr;
    //char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t length;

    int decimal_places = (int)log10(max_num) + 1;

    int buffers_size = max_size*(decimal_places + 1) + 210;

    char buffer[buffers_size];
  
    char **lines = (char **)malloc(quant * sizeof(char *));

    if (lines == NULL){
        printf("Erro ao alocar memória para o csv\n");
        return NULL;
    }

    for (int j = 0; j < quant; j++){
        lines[j] = NULL;
    }

    fptr = fopen(file_name, "r");
    if (fptr == NULL) {
        printf("Erro ao abrir o arquivo\n");
        free(lines);
        return NULL;
    }

    int i = 0;

    //while (fgets(buffer, 1000000, fptr) != NULL && i < quant) 
    while (fgets(buffer, buffers_size, fptr) != NULL && i < quant){
        int length = strlen(buffer);
        lines[i] = malloc((length + 1) * sizeof(char));
        if (lines[i]==NULL){
            printf("Erro na alocação de memória\n");
        }

        lines[i] = malloc((size_t)length + 1);
        if (lines[i] == NULL){
            printf("Erro na alocação de memória\n");
            break;
        }

        strcpy(lines[i], buffer);
        i++;
    }

    //free(buffer);
    fclose(fptr);

    return lines;
}
