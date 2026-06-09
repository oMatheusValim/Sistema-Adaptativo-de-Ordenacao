#include "utils.h"
#include "input_generator.h"
#include "io.h"
#include "adaptive.h"
#include "method_analysis.h"

#define QUANT 1000
#define MAX_NUM 10000
#define MAX_SIZE 1000

int main(int argc, char *argv[]){    

    int algs_count = load_envs(argc, argv);
    if (algs_count < 0) return -1;

    int verbose = (getenv("VERBOSE") != NULL) ? atoi(getenv("VERBOSE")) : 0;
    char *csv = getenv("CSV_FILE");
    
    int quant; 
    int max_size;
    int max_num;

    if ((csv == NULL) || (strlen(csv) == 0) || (csv[0] == '\0')){

        sprintf(csv, "%s.env", datetime_stamp());

        quant = convert_env("QUANT", 1, 10, 80000); if (quant < 0) return -1;
        max_num = convert_env("MAX_NUM", 1, 100, 100000); if (max_num < 0) return -1;
        max_size = convert_env("MAX_SIZE", 1, 10, 25000); if (max_size < 0) return -1;

        if (verbose != 0) printf("Gerando os dados aleatoriamente ...\n");
        int **arrs = create_arrs(quant, max_size, max_num);

        if (verbose != 0) printf("Colocando os arrays desordenados no csv de entrada %s ...\n", csv);
        write_csv(arrs, csv, quant, max_size, max_num);

        for (int i = 0; i<quant; i++){        
            if (arrs[i] != NULL){
                free(arrs[i]);
            }
        }free(arrs);

    }

    if (verbose != 0) printf("Lendo os dados do arquivo %s...\n", csv);
    csv_extraction csv_results = read_csv(csv); if (csv_results.quant < 0) return -1;

    quant = csv_results.quant;
    max_size = csv_results.max_size;
    max_num = csv_results.max_num;

    method_arr *arrs_full = find_methods(algs_count);

    int method_count[5] = {0, 0, 0, 0, 0};
    entry_analysis *ea = (entry_analysis*)calloc(quant, sizeof(entry_analysis));
    metrics **m = (metrics**)calloc(algs_count, sizeof(metrics*));

    for (int i = 0; i< algs_count; i++){
        m[i] = (metrics*)calloc(quant, sizeof(metrics));
    }
    
    if (verbose != 0) printf("Inicio da análise...\n");
    for (int i = 0; i < quant; i++){
        if (csv_results.lines[i] != NULL){
            arrs_full = allocate_arrs(csv_results.lines[i], arrs_full, algs_count);

            for (int j = 0; j<algs_count; j++){

                switch (arrs_full[j].method){
                    case 'A':
                        ea[i] = analyse_entry(arrs_full[j].arr, arrs_full[j].size, arrs_full[j].index);
                        m[j][i] = decision_tree(ea[i], max_size);
                        //printf("time: %f \n", m[j][i].tempo);
                        method_count[char_to_int(m[j][i].metodo)]++;
                        break;

                    case 'C':
                        m[j][i] = countingSort(arrs_full[j].arr, arrs_full[j].size);
                        break;

                    case 'H':
                        m[j][i] = heapSort(arrs_full[j].arr, arrs_full[j].size);
                        break;

                    case 'I':
                        m[j][i] = insertionSort(arrs_full[j].arr, arrs_full[j].size);
                        break;

                    case 'M':
                        m[j][i] = mergeSort(arrs_full[j].arr, arrs_full[j].size);
                        break;

                    case 'S':
                        m[j][i] = selectionSort(arrs_full[j].arr, arrs_full[j].size);
                        break;

                }

                if (arrs_full[j].arr != NULL) free(arrs_full[j].arr);
            } 
        }
    }

    adaptive_comparison(m, quant, algs_count);

    for (int i = 0; i < algs_count; i++){
        if (arrs_full[i].method == 'A'){
            decision_tree_statistics(ea, m[i], method_count, quant);
        }
        if (m[i] != NULL) free(m[i]);
    }

    if (verbose != 0) printf("Liberando memória ...\n");
    for (int i = 0; i<quant; i++){
        if (csv_results.lines[i] != NULL) free(csv_results.lines[i]);

    }

    free(arrs_full);
    free(csv_results.lines);
    free(ea);
    free(csv);
    free(m);

    printf("Fim da execução\n");

    return 0;

    
}