#include "utils/headers/utils.h"
#include "headers/method_compare.h"

//função find_methods: obtém do arquivo config.txt quais métodos de ordenação o usuário deseja comparar. Retorna struct do tipo alg_ctx.
alg_ctx *find_methods(int algs_count){

    alg_ctx *arrs = (alg_ctx *)malloc(algs_count * sizeof(alg_ctx));
    if (arrs == NULL){
        printf("ERRO! Não foi possível alocar memória (find_methods)\n ");
        return NULL;
    }

    int i = 0;
    int j = 0;
    char algs[6] = "ACHIMS";

    while (i < algs_count && j < 6){
        if (atoi(getenv((char[]){algs[j], '\0'})) == 1) {
            arrs[i].method = algs[j];
            i++;
        }

        j++;
    }

    return arrs;

}

//Função entry_index: Retorna o valor antes da primeira virgula, que representa o index da entrada
int entry_index(char *line){
    // Retorna o valor antes da primeira virgula, que representa o index da entrada
    char *token = strtok(line, ",");
    return atoi(token);

}

//função entry_size: retorna contagem do numero de colunas no csv, desconsiderando a ultima coluna
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


//função allocate_arr: converte a linha csv em um vetor de inteiros e o retorna.
int *allocate_arr(char *line, int n, int index){

    // Alocacao do vetor de ints
    int *arr = (int*)calloc((n+1), sizeof(int));

    if (arr == NULL){
        printf("ERRO! Não foi possível alocar memória (allocate_arr)\n");
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

//função cpy_arrs: copia o array desordenado para a comparação com métodos de ordenação escolhidos manualmente. retorna struct alg_ctx.
alg_ctx *cpy_arrs(char *line, alg_ctx *arrs, int algs_count){

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
