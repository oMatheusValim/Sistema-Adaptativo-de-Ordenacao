#include "utils/headers/utils.h"
#include "headers/entry_analysis.h"

//função entry_amp: verifica a amplitude máxima dos valors do vetor (maior valor do vetor - menor valor do vetor). Retorna valor inteiro da amplitude.
int *entry_amp(int *arr, int n){

    int *min_max = (int*)calloc(2, sizeof(int));

    min_max[0] = arr[0];
    min_max[1] = arr[0];

    for (int i = 1; i < n; i++){
        if (arr[i] < min_max[0]){
            min_max[0] = arr[i];
        }

        if (arr[i] > min_max[1]){
            min_max[1] = arr[i];
        }
    }

    return min_max;
}

//Função entry_disp: coleta métricas das medidas de dispersão do vetor. retorna struct disp composta por essas medidas.
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

//função count_uniques: conta o número de valores não repetidos dentro do vetor desordenado. retorna inteiro.
int count_uniques(int *arr, int n, int *min_max){

    int offset = -1*min_max[0];

    int amp = min_max[1] - min_max[0] + 1;

    int *count = (int*)calloc(amp, sizeof(int));
    int uniques = 0;

    //conta repetições
    for (int i = 0; i<n; i++){
        count[arr[i] + offset]++;
        uniques++;

        if (count[arr[i] + offset] > 1)
            uniques--;
    }

    free(count);
    return uniques;
}

//função countInv: conta o número de vezes que um elemento é maior que seu sucessor dentro do vetor. retorna inteiro.
int countInv(int *arr, int n) {

    int count = 0;
    int i = 0;

    for (i = 0; i < n-1; i++){

        if (arr[i]>arr[i+1])
            count++;
    }

    return count;
}

/*função entry_distr: coleta:
 * métrica de desordem do vetor: calculada pela razão entre o número de inversões que ocorrem no vetor e o maior número possíveis de inversões para aquele vetor, dado por n-1;
 * densidade de duplicatas no vetor, dada pela razão entre o número de duplicatas e o tamanho n do vetor.
 * número de valores não repetidos no vetor;
*retorna struct do tipo distribution analysis que armazena as métricas de caracterização de distribuição do vetor de entrada.
*/
distribution_analysis entry_distr(int *arr, int n, int *min_max){

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
    int unique_nums_count = count_uniques(arr, n, min_max);

    distr.repetitions = n - unique_nums_count;
    distr.duplicate_density = (float)distr.repetitions/n;

    return distr;
}

//função analyse_entry: coleta todas as características do vetor de entrada. retorna um struct do tipo entry_analysis contendo:
/*
tamanho do vetor;
cópia do vetor desordenado;
index do vetor na entrada;
amplitude;
struct de características de distribuição do vetor de entrada;
*/
entry_analysis analyse_entry(int *arr, int n, int index){

    entry_analysis ea = {0};

    ea.size = n;
    ea.vector = arr;
    ea.index = index;

    int *min_max = entry_amp(ea.vector, ea.size);
    ea.amp = min_max[1] - min_max[0] + 1;
    ea.distr = entry_distr(ea.vector, ea.size, min_max);

    free(min_max);

    return ea;
}





