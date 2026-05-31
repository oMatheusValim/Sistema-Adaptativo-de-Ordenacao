#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "entry_analysis.h"
#include "io.h"
#include "../include/algoritmos.h"


int main(){
    
    char **lines = read_data_input("output.csv", 60);
    entry_analysis ea;

    int i = 1;

    for (i=1; i<60; i++){
        if (lines[i] != NULL)
            ea = analyse_entry(lines[i]);
            metrics m = countingSort(ea.vector, ea.size);
            printf("Comp: %lld, Movements: %lld, time: %f ", m.compare, m.movements, m.tempo);
            //printf("i:%d - dis:%f - n:%d\n", ea.index, ea.distr.disorder, ea.size);
    }
    

    for (i=0; i<60; i++){
        if (lines[i] != NULL)
            free(lines[i]);
    }

    free(lines);
    free(ea.vector);

    return 0;
}