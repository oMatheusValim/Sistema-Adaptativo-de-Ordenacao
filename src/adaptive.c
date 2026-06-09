#include "utils.h"
#include "adaptive.h"


metrics decision_tree(entry_analysis ea, int max_size){

    // Para entradas com pouca amplitude de dados, use o counting_sort
    if (ea.amp <= ea.size){
        //printf("i: %d, n: %d, metodo: C, ", ea.index, ea.size);
        return countingSort(ea.vector, ea.size);
    }

    // Para entradas muito desordenadas e pequenas, use o selection_sort
    if (ea.distr.disorder > 0.7 && ea.size <= 0.15*max_size){
        //printf("i: %d, n: %d, metodo: S, ", ea.index, ea.size);
        return selectionSort(ea.vector, ea.size);
    }

    // Para entradas pequenas, use o insertion_sort
    if (ea.size <= 0.15*max_size){
        //printf("i: %d, n: %d, metodo: I, ", ea.index, ea.size);
        return insertionSort(ea.vector, ea.size);
    }

    // Para entradas maiores ou muito desordenadas, use o heap_sort
    if (ea.size >= 0.6*max_size || ea.distr.disorder > 0.7){
        //printf("i: %d, n: %d, metodo: H, ", ea.index, ea.size);
        return heapSort(ea.vector, ea.size);
    }

    // Caso nenhuma das condições anteriores for atendida, use o merge_sort
    //printf("i: %d, n: %d, metodo: M, ", ea.index, ea.size);
    return mergeSort(ea.vector, ea.size);
}
