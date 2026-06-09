#ifndef EA_H
#define EA_H

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
    int amp;
    int *vector;
    distribution_analysis distr;
}entry_analysis;

entry_analysis analyse_entry(int *arr, int n, int index);


#endif