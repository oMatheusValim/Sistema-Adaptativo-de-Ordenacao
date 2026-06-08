#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "input_generator.h"
#include "io.h"
#include "adaptive.h"


#define QUANT 500
#define MAX_NUM 5000
#define MAX_SIZE 1000

int main(){

    printf("Gerando os dados aleatoriamente ...\n");
    int **arrs = create_arrs(QUANT, MAX_SIZE, MAX_NUM);
    

    printf("Colocando os dados no csv ...\n");
    write_csv(arrs, QUANT, "entrada.csv", MAX_NUM);

    printf("Lendo os dados do csv...\n");
    char **lines = read_data_input("entrada.csv", QUANT, MAX_NUM, MAX_SIZE);
    entry_analysis ea = {0};

    int i = 1;

    int count_c = 0;
    int count_h = 0;
    int count_i = 0;
    int count_m = 0;
    int count_s = 0;


    
    printf("Inicio da análise...\n");
    for (i=1; i<QUANT; i++){
        if (lines[i] != NULL){
            int arr_size = entry_size(lines[i]);
            ea = analyse_entry(lines[i]);
            int arr_index = entry_index(lines[i]);
            int *arr = allocate_arr(lines[i], arr_size, arr_index);

            int *desordem = copy_vector(arr, arr_size);

            //for (int j = 1; j < entry_size(lines[i]); j++)
            //{
                //printf("%d ", desordem[j]);
            //}
printf("\n");

            //PARA TESTAR SÓ UM ALGORITMO, DESCOMENTE ELE ABAIXO E O PRINTF QUE COMEÇA COM COMP...
                //metrics m = countingSort(ea.vector, ea.size);
                //metrics m = heapSort(ea.vector, ea.size);
                //metrics m = mergeSort(ea.vector, ea.size);
                //metrics m = selectionSort(ea.vector, ea.size);
                //metrics m = insertionSort(ea.vector, ea.size);
                //printf("Index: %d, Size: %d, Comp: %lld, Movements: %lld, time: %f \n", ea.index, ea.size, m.compare, m.movements, m.tempo);

                
            //PARA TESTAR A ÁRVORE DE DECISÃO, DESCOMENTE AS PRÓXIMAS 2 LINHAS DE CÓDIGO
                metrics m = decision_tree(ea, MAX_SIZE);
                //printf("time: %f \n", m.tempo);

            
            switch (m.metodo){
                case 'c':
                    //count_c++;
                    //break;
                
                case 'h':
                    count_h++;
                    break;

                case 'i':
                    count_i++;
                    break;

                case 'm':
                    count_m++;
                    break;

                case 's':
                    count_s++;
                    break;
            }
            
            if (ea.vector != NULL){
                free(ea.vector);
            }
            free(desordem);
        }
    }

    //printf("STATS: c: %d, h: %d, i: %d, m: %d, s: %d\n", count_c, count_h, count_i, count_m, count_s);

    //printf("Liberando memória ...\n");
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