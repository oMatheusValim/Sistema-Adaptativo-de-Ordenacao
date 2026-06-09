#ifndef MA_H
#define MA_H

#include "entry_analysis.h"
#include "algoritmos.h"

typedef struct{
    char method;
    int *arr;
    int index;
    int size;
}alg_ctx;

alg_ctx *find_methods(int algs_count);
alg_ctx *cpy_arrs(char *line, alg_ctx *arrs, int algs_count);

#endif