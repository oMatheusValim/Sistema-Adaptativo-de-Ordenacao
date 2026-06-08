#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct{
    int min;
    int min_idx;
    int max;
    int max_idx;
    int amp;
}amp_analysis;

typedef struct{
    float avg;
    float sd;
}dispersion_analysis;

typedef struct{
    int repetitions;
    float duplicate_density;
    float disorder;
    dispersion_analysis disp;
}distribution_analysis;

typedef struct{
    int index;
    int size;
    amp_analysis amp;
    int *vector;
    distribution_analysis distr;
}entry_analysis;

entry_analysis analyse_entry(char *line);
int entry_size(char *line);
int *allocate_arr(char *line, int n, int index);

int *copy_vector (int *str, int n);
int entry_index(char *line);


