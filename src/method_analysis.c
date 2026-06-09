#include "utils.h"
#include "method_analysis.h"


method_arr *find_methods(int algs_count){

    method_arr *arrs = (method_arr *)malloc(algs_count * sizeof(method_arr));
    if (arrs == NULL){
        printf("Erro! Não foi possível alocar memória para os vetores de inteiros!\n Fim de execução\n");
        return NULL;
    }

    int i = 0;
    int j = 0;
    char algs[6] = "ACHIMS";

    while (i < algs_count && j < 6){
        if (atoi(getenv((char[]){algs[i], '\0'})) == 1) {
            arrs[i].method = algs[i];
            i++;
        }

        j++;
    }

    return arrs;

}

int entry_index(char *line){
    // Retorna o valor antes da primeira virgula, que representa o index da entrada
    char *token = strtok(line, ",");
    return atoi(token);

}

int entry_size(char *line){
    int i = 0;
    int num_colums_csv = 0;

    // Contagem do numero de colunas no csv, desconsiderando a ultima coluna
    while(line[i] != '\n'){
        if (line[i] == ',')
            num_colums_csv++;

        i++;
    }

    return (num_colums_csv);
}


int *allocate_arr(char *line, int n, int index){

    // Alocacao do vetor de ints
    int *arr = (int*)calloc((n+1), sizeof(int));

    if (arr == NULL){
        printf("Erro na alocacao do vetor de index #%d (float, size = %d)\n", index, n);
        return NULL;
    }

    // Transferencia da linha do csv para floats
    char *token = strtok(NULL, ",");
    int i = 0;

    while ((token != NULL) && i < n){
        arr[i] = atoi(token);
        token = strtok(NULL, ",");
        i++;
    }

    return arr;
}

method_arr *allocate_arrs(char *line, method_arr *arrs, int algs_count){

    int index = entry_index(line);
    int size = entry_size(line);

    arrs[0].arr = allocate_arr(line, size, index);
    arrs[0].index = index;
    arrs[0].size = size;

    for (int i = 1; i < algs_count; i++){
        arrs[i].arr = malloc((size + 1) * sizeof(int));
        memcpy(arrs[i].arr, arrs[0].arr, size * sizeof(int));

        arrs[i].index = index;
        arrs[i].size = size;
    }

    return arrs;
}
