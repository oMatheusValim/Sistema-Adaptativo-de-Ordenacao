#include <stdio.h>
#include <stdlib.h>
#include "adaptive.h"

#define MAX_SIZE 10000

void decision_tree(entry_analysis ea, int* arr){

    // Para entradas com pouca amplitude de dados, use o counting_sort
    if (ea.amp.amp <= 1.5*ea.size){
        return run_counting_sort(ea.size, arr);
    }

    // Para entradas muito desordenadas, use o heap_sort
    if (ea.distr.disorder > 0.85){
        return run_heap_sort(ea.size, arr);
    }

    // Para entradas com muitos valores duplicados, use o heap_sort
    if (ea.distr.duplicate_density > 0.85){
        return run_heap_sort(ea.size, arr);  
    }

    // Para entradas quase ordenadas ...
    if (ea.distr.disorder < 0.3){

        // ... e pequenas, use o insertion_sort
        if (ea.size <= MAX_SIZE/5){
            return run_insertion_sort(ea.size, arr);
        }

        // ... e grandes, use o selection_sort
        else{
            return run_selection_sort(ea.size, arr);
        }
    }

    // Caso nenhuma das condições anteriores for atendida, use o merge_sort
    return run_merge_sort(ea.size, arr);

}
