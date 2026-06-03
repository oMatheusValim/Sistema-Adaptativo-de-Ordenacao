#include <stdio.h>
#include <stdlib.h>
#include "adaptive.h"

metrics decision_tree(entry_analysis ea, int max_size){

    // Para entradas com pouca amplitude de dados, use o counting_sort
    if (ea.amp.amp <= 1.5*ea.size){
        printf("i: %d, n: %d, metodo: COUNTING, ", ea.index, ea.size);
        return countingSort(ea.vector, ea.size);
    }

    // Para entradas muito desordenadas, use o heap_sort
    if (ea.distr.disorder > 0.85){
        printf("i: %d, n: %d, metodo: HEAP1, ", ea.index, ea.size);
        return heapSort(ea.vector, ea.size);
    }

    // Para entradas quase ordenadas ...
    if (ea.distr.disorder < 0.3){

        // ... e pequenas, use o insertion_sort
        if (ea.size <= max_size/4){
            printf("i: %d, n: %d, metodo: INSERTION, ", ea.index, ea.size);
            return insertionSort(ea.vector, ea.size);
        }

        // ... e grandes, use o selection_sort
        else{
            printf("i: %d, n: %d, metodo: SELECTION, ", ea.index, ea.size);
            return selectionSort(ea.vector, ea.size);
        }
    }

    // Caso nenhuma das condições anteriores for atendida, use o merge_sort
    printf("i: %d, n: %d, metodo: MERGE, ", ea.index, ea.size);
    return mergeSort(ea.vector, ea.size);

}
