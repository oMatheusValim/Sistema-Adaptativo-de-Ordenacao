#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "entry_analysis.h"
#include "input_generator.h"
#include "io.h"


int main(){

    //int **arrs = create_arrs(80, 100, 1000);

    //write_csv(arrs, 80, "entrada.csv", 1000);

    
    char **lines = read_data_input("entrada.csv", 80);
    entry_analysis ea;

    int i = 1;

    for (i=1; i<80; i++){
        if (lines[i] != NULL){
            ea = analyse_entry(lines[i]);
            printf("i:%d - dis:%f - n:%d\n", ea.index, ea.distr.disorder, ea.size);
        }
    }

    for (int i = 0; i<80; i++){
        if (lines[i] != NULL)
            free(lines[i]);

        //if (arrs[i] != NULL)
        //    free(arrs[i]);
    }

    //free(arrs);
    free(lines);

    return 0;
}