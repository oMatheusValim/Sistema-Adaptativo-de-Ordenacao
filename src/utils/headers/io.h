#ifndef IO_H
#define IO_H

#include "../../headers/entry_analysis.h"
#include "../../headers/algoritmos.h"

typedef struct{
    int quant;
    int max_size;
    int max_num;
    char **lines;
}csv_line;

typedef struct {
    char method;
    float avg_t;
    int avg_n;
    int avg_amp;
    float avg_distr;
    long long int avg_cmp;
    long long int avg_mov;
    long long int avg_mem;
    long long int avg_rec;
    int avg_max_depth;    

}tree_statistics;

typedef struct {
    char method;
    float avg_t;
    long long int avg_cmp;
    long long int avg_mov;
    long long int avg_mem;
    long long int avg_rec;
    int avg_max_depth;    

}adaptive_statistics;

csv_line read_csv(char* file_name);
int write_csv(int **arrs, char* filename, int quant, int max_size, int max_num);
void decision_tree_statistics(entry_analysis *ea, metrics *m, int *method_count, int quant, int verbose, int out_txt);
void adaptive_comparison(metrics **m, int quant, int algs_count, int verbose, int out_txt);
void print_progress_bar(int current, int total);

#endif