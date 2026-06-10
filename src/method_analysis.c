#include "utils.h"
#include "method_analysis.h"

//função find_methods: obtém do arquivo config.txt quais métodos de ordenação o usuário deseja comparar com a árvore de ordenação. Retorna struct do tipo alg_ctx.
alg_ctx *find_methods(int algs_count){

    alg_ctx *arrs = (alg_ctx *)malloc(algs_count * sizeof(alg_ctx));
    if (arrs == NULL){
        printf("Erro! Não foi possível alocar memória para os vetores de inteiros!\n ");
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
    for (int k = 0; k < algs_count; k++)
    {
        printf("arrs[%d].method = %c\n", k, arrs[k].method);
        
    }
    
    return arrs;

}

//Função entry_index: Retorna o valor antes da primeira virgula, que representa o index da entrada
int entry_index(char *line){

    char *token = strtok(line, ",");
    return atoi(token);

}
//função entry_size: retorna contagem do numero de colunas no csv, desconsiderando a ultima coluna
int entry_size(char *line){
    int i = 0;
    int num_colums_csv = 0;

    
    while(line[i] != '\n' && line[i] != '\0'){
        if (line[i] == ',')
            num_colums_csv++;

        i++;
    }

    return (num_colums_csv+1);
}

//função allocate_arr: converte a linha csv em um vetor de inteiros e o retorna.
int *allocate_arr(char *line, int n, int index){

    // Alocacao do vetor de ints 
    int *arr = (int*)calloc((n), sizeof(int));

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

//função cpy_arrs: copia o array desordenado para a comparação com métodos de ordenação escolhidos manualmente. retorna struct alg_ctx.
alg_ctx *cpy_arrs(char *line, alg_ctx *arrs, int algs_count){

    int index = entry_index(line);
    int size = entry_size(line);

    arrs[0].arr = allocate_arr(line, size, index);
    arrs[0].index = index;
    arrs[0].size = size;

    for (int i = 1; i < algs_count; i++){
        arrs[i].arr = malloc((size) * sizeof(int));
        memcpy(arrs[i].arr, arrs[0].arr, size * sizeof(int));

        arrs[i].index = index;
        arrs[i].size = size;
    }

    return arrs;
}
