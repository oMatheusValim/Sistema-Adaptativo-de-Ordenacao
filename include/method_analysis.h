#ifndef MA_H
#define MA_H

#include "entry_analysis.h"
#include "algoritmos.h"

typedef struct{
    char method;
    int *arr;
    int index;
    int size;
}method_arr;

method_arr *find_methods(int algs_count);
method_arr *allocate_arrs(char *line, method_arr *arrs, int algs_count);

#endif