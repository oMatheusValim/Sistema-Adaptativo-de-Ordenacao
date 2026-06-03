#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "input_generator.h"
#include "io.h"
#include "adaptive.h"


#define QUANT 4000
#define MAX_NUM 10000
#define MAX_SIZE 3200

int main(){

    printf("Gerando os dados aleatoriamente ...\n");
    int **arrs = create_arrs(QUANT, MAX_SIZE, MAX_NUM);

    printf("Colocando os dados no csv ...\n");
    write_csv(arrs, QUANT, "entrada.csv", MAX_NUM);

    printf("Lendo os dados do csv...\n");
    char **lines = read_data_input("entrada.csv", QUANT, MAX_NUM, MAX_SIZE);
    entry_analysis ea = {0};

    int i = 1;
    printf("Inicio da análise...\n");
    for (i=1; i<1000; i++){
        if (lines[i] != NULL){
            ea = analyse_entry(lines[i]);
            //metrics m = countingSort(ea.vector, ea.size);
            //metrics m = heapSort(ea.vector, ea.size);
            //metrics m = mergeSort(ea.vector, ea.size); //BUGADO!!!
            //metrics m = selectionSort(ea.vector, ea.size);
            //metrics m = insertionSort(ea.vector, ea.size);

            metrics m = decision_tree(ea, MAX_SIZE);

            printf("time: %f \n", m.tempo);
            
            if (ea.vector != NULL){
                free(ea.vector);
            }
 
        }
    }

    printf("Liberando memória ...\n");
    for (int i = 0; i<QUANT; i++){
        if (lines[i] != NULL)
            free(lines[i]);

        if (arrs[i] != NULL)
            free(arrs[i]);
    }

    free(arrs);
    free(lines);

    printf("Fim da execução\n");

    return 0;
}