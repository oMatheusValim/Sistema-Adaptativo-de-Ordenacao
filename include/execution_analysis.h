#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct{
    char metodo;
    int count;

    float t_sum;

    int n_sum;
    float t_per_n_sum;

    int amp_sum;
    float t_per_amp_sum;

    float distr_sum;
    float t_per_distr_sum;

}output_analysis;