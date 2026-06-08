#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "entry_analysis.h"


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
    int *arr = malloc(n * sizeof(int));

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


amp_analysis entry_amp(int *arr, int n){
    amp_analysis amp;

    amp.min = arr[0];
    amp.max = arr[0];

    amp.min_idx = 0;
    amp.max_idx = 0;

    for (int i = 1; i < n; i++){
        if (arr[i] < amp.min){
            amp.min = arr[i];
            amp.min_idx = i;
        }

        if (arr[i] > amp.max){
            amp.max = arr[i];
            amp.max_idx = i;
        }
    }

    amp.amp = amp.max - amp.min;

    return amp;
}

dispersion_analysis entry_disp(int *arr, int n){

    float sum = 0.0;
    float avg = 0.0;
    float var = 0.0;
    float sd = 0.0;
    int i;

    // Calcular média
    for (i = 0; i < n; ++i) {
        sum += arr[i];
    }
    avg = sum / n;

    // Calcular a soma dos quadrados das diferenças
    for (i = 0; i < n; ++i) {
        var += pow(arr[i] - avg, 2);
    }

    // Dividir por (n) para desvio padrão 
    var = var / (n);

    // Extrair a raiz quadrada
    sd = sqrt(var);

    dispersion_analysis disp;

    disp.avg = avg;
    disp.sd = sd;

    return disp;            
}

int count_uniques(int *arr, int n, amp_analysis amp){
    int offset = -1*amp.min;
    int count[amp.amp + 1];
    int i;
    int uniques = 0;

    //inicializa o vetor para zero
    for(i = 0; i<= amp.amp; i++){
        count[i] = 0;
    }

    //conta repetições
    for (int i = 0; i<n; i++){
        count[arr[i] + offset]++;
        uniques++;


        if (count[arr[i] + offset] > 1)
            uniques--;

    }
    return uniques;

}


int countInv(int *arr, int n) {

    int count = 0;
    int i = 0;

    for (i = 0; i < n-1; i++){

        if (arr[i]>arr[i+1])
            count++;
    }

    return count;
}

distribution_analysis entry_distr(int *arr, int n, amp_analysis amp){

    distribution_analysis distr = {0};   

    distr.disorder = 0.0;

    if (n==2){
        if (arr[0]>arr[1])
            distr.disorder = 1.0;
    }

    if (n>2){
        int inversions = countInv(arr, n);
        float max_inversions = (n-1);
        distr.disorder = inversions/max_inversions;
    }

    distr.disp = entry_disp(arr, n);
    int unique_nums_count = count_uniques(arr, n, amp);

    distr.repetitions = n - unique_nums_count;
    distr.duplicate_density = (float)distr.repetitions/n;

    return distr;
}


entry_analysis analyse_entry(char *line){

    entry_analysis ea = {0};

    ea.size = entry_size(line);
    ea.index = entry_index(line);

    ea.vector = allocate_arr(line, ea.size, ea.index);

    ea.amp = entry_amp(ea.vector, ea.size);
    ea.distr = entry_distr(ea.vector, ea.size, ea.amp);

    return ea;
}

int *copy_vector (int *arr, int n){

   int *desordem = malloc(n * sizeof(int));
   if (desordem == NULL)
   {
    printf("Erro na alocacao de memória");
    return NULL;
   }
   for (int i =0 ; i < n; i++)
   {
    desordem[i] = arr[i];

   }
    
    return desordem;
}



