#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "entry_analysis.h"
#include "input_generator.h"
#include "io.h"
#include "algoritmos.h"


#define QUANT 4000
#define MAX_NUM 1000
#define MAX_SIZE 3500

int main(){

    printf("Gerando os dados aleatoriamente ...\n");
    int **arrs = create_arrs(QUANT, MAX_SIZE, MAX_NUM);

    printf("Colocando os dados no csv\n");
    write_csv(arrs, QUANT, "entrada.csv", MAX_NUM);

    printf("Lendo os dados do csv...\n");
    char **lines = read_data_input("entrada.csv", QUANT, MAX_NUM, MAX_SIZE);
    entry_analysis ea = {0};

    int i = 1;
    printf("Inicio da análise...\n");
    for (i=1; i<1000; i++){
        if (lines[i] != NULL){
            ea = analyse_entry(lines[i]);
            metrics m = countingSort(ea.vector, ea.size);
            printf("i: %d, n: %d, Comp: %lld, Movements: %lld, time: %f \n", ea.index, ea.size, m.compare, m.movements, m.tempo);
            
            if (ea.vector != NULL){
                free(ea.vector);
            }
 
        }
    }

    printf("Liberando memória...\n");
    for (int i = 0; i<QUANT; i++){
        if (lines[i] != NULL)
            free(lines[i]);

        if (arrs[i] != NULL)
            free(arrs[i]);
    }

    free(arrs);
    free(lines);

    printf("Fim da execução ...\n");

    return 0;
}