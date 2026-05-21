#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "entry_analysis.h"
#include "io.h"


int main(){

    char **lines = read_data_input("output.csv", 60);
    entry_analysis ea;

    int i = 1;

    for (i=1; i<60; i++){
        if (lines[i] != NULL)
            ea = analyse_entry(lines[i]);
            printf("i:%d - dis:%f - n:%d\n", ea.index, ea.distr.disorder, ea.size);
    }

    for (i=0; i<60; i++){
        if (lines[i] != NULL)
            free(lines[i]);
    }

    free(lines);

    return 0;
}