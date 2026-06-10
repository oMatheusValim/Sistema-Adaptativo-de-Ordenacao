#include "utils/headers/utils.h"
#include "utils/headers/config.h"
#include "utils/headers/input_generator.h"
#include "utils/headers/io.h"
#include "headers/adaptive.h"
#include "headers/method_compare.h"
#include "headers/algoritmos.h"
#include "headers/entry_analysis.h"

int verbose;

static int generate_and_write_csv( char *csv_path, int quant, int max_size, int max_num){
    
    if (verbose != 0) printf("Gerando os dados aleatoriamente ...\n");
    int **arrs = create_arrs(quant, max_size, max_num);

    if (arrs == NULL) {
        printf("Erro! Não foi possível gerar os arrays.\n");

        return -1;
    }
 
    if (verbose != 0) printf("Colocando os arrays desordenados no csv de entrada %s ...\n", csv_path);
    if (write_csv(arrs, csv_path, quant, max_size, max_num) < 0) return -1;

    for (int i = 0; i < quant; i++) free(arrs[i]);

    free(arrs);
    return 0;
}


static char *resolve_csv(int *out_quant, int *out_max_size, int *out_max_num){

    char *env_csv = getenv("CSV_FILE");
    if (env_csv != NULL && env_csv[0] != '\0') {
        return strdup(env_csv);
    }
 
    int quant = convert_env("QUANT", 1, 80000); if (quant < 0) return NULL;
    int max_num  = convert_env("MAX_NUM", 100, 100000); if (max_num  < 0) return NULL;
    int max_size = convert_env("MAX_SIZE", 10,  25000); if (max_size < 0) return NULL;
 
    char *csv_path = (char*)malloc(64*sizeof(char));

    if (csv_path == NULL){
        printf("Erro! Falha na alocação de memória para a análise.\n"); 
        return NULL;
    }

    char* date_time = datetime_stamp();
    snprintf(csv_path, 64, "experiments/datasets/%s.csv", date_time);
    free(date_time);
 
    if (generate_and_write_csv(csv_path, quant, max_size, max_num) < 0) {
        free(csv_path);
        printf("Erro! Falha na alocação de memória para a análise.\n");
        return NULL;
    }
 
    *out_quant    = quant;
    *out_max_size = max_size;
    *out_max_num  = max_num;

    return csv_path;
}


static metrics **alloc_metrics(int algs_count, int quant){
    metrics **m = calloc(algs_count, sizeof(metrics *));
    if (m == NULL) return NULL;
 
    for (int i = 0; i < algs_count; i++) {
        m[i] = calloc(quant, sizeof(metrics));

        if (m[i] == NULL) {
            for (int k = 0; k < i; k++) free(m[k]);
            free(m);
            return NULL;
        }
    }
    return m;
}


static void free_metrics(metrics **m, int algs_count){
    if (m == NULL) return;

    for (int i = 0; i < algs_count; i++) { 
        if(m[i] != NULL) free(m[i]);
    }

    free(m);
}

static metrics run_algorithm(alg_ctx *alg, entry_analysis *ea_out, int max_size){
    switch (alg->method) {
        case 'A':
            *ea_out = analyse_entry(alg->arr, alg->size, alg->index);
            return decision_tree(*ea_out, max_size);
        case 'C': return countingSort(alg->arr, alg->size);
        case 'H': return heapSort(alg->arr, alg->size);
        case 'I': return insertionSort(alg->arr, alg->size);
        case 'M': return mergeSort(alg->arr, alg->size);
        case 'S': return selectionSort(alg->arr, alg->size);
        default:  return (metrics){0};
    }
}

static int run_analysis(csv_line *cl, alg_ctx *algs, int algs_count, metrics **m, entry_analysis *ea, int method_count[6]){
 
    for (int i = 0; i < cl->quant; i++) {
        if (cl->lines[i] == NULL) continue;

        if (verbose != 0) printf("ordenados: %d/%d\n",i, cl->quant);
 
        /* Fill each alg's arr with a fresh copy of this input */
        algs = cpy_arrs(cl->lines[i], algs, algs_count);
 
        for (int j = 0; j < algs_count; j++) {
            m[j][i] = run_algorithm(&algs[j], &ea[i], cl->max_size);
 
            if (verify_sort(algs[j].arr, algs[j].size) < 0)
                printf("Erro! O algoritmo %c não ordenou corretamente o vetor #%d\n", m[j][i].metodo, algs[j].index);

            if (algs[j].method == 'A') {
                method_count[char_to_int(m[j][i].metodo)]++;
            }
 
            free(algs[j].arr);
            algs[j].arr = NULL;
        }
    }
 
    return 0;
}


int main(int argc, char *argv[]){    

    int algs_count = load_envs(argc, argv);
    
    if (algs_count < 0) return -1;

    verbose = (getenv("VERBOSE") != NULL) ? atoi(getenv("VERBOSE")) : 0;
    int out_txt = (getenv("OUT_TXT") != NULL) ? atoi(getenv("OUT_TXT")) : 0;

    int quant = 0;
    int max_size = 0;
    int max_num = 0;

    char *csv_path = resolve_csv(&quant, &max_size, &max_num);
    if (csv_path == NULL) return -1;

    if (verbose != 0) printf("Lendo os dados do arquivo %s...\n", csv_path);
    csv_line cl = read_csv(csv_path);
    free(csv_path);
    if (cl.quant < 0) return -1;

    quant = cl.quant;
    max_size = cl.max_size;
    max_num = cl.max_num;

    alg_ctx *algs = find_methods(algs_count);
    entry_analysis *ea = calloc(quant, sizeof(entry_analysis));
    metrics **m = alloc_metrics(algs_count, quant);
    int method_count[6] = {0};

    if (algs == NULL || ea == NULL || m == NULL) {
        printf("Erro! Falha na alocação de memória para a análise.\n");

        free(algs); free(ea); free_metrics(m, algs_count);
        for (int i = 0; i < quant; i++) free(cl.lines[i]);
        free(cl.lines);

        return -1;
    }

    if (verbose != 0) printf("Inicio da análise...\n");
    run_analysis(&cl, algs, algs_count, m, ea, method_count);

    
    adaptive_comparison(m, quant, algs_count, verbose, out_txt);

    for (int i = 0; i < algs_count; i++) {
        if (algs[i].method == 'A') {
            decision_tree_statistics(ea, m[i], method_count, quant, verbose, out_txt);
        }
    }


    if (verbose != 0) printf("\nLiberando memória ...\n");
    free(algs);
    free(ea);
    free_metrics(m, algs_count);
    for (int i = 0; i < quant; i++) free(cl.lines[i]);
    free(cl.lines);
 
    if (verbose != 0) printf("Execução realizada com sucesso!\n");

    return 0;

    
}