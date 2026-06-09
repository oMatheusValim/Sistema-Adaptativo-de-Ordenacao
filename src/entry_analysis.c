#include "utils.h"
#include "entry_analysis.h"

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

int count_uniques(int *arr, int n, int *min_max){

    int offset = -1*min_max[0];

    int amp = min_max[1] - min_max[0] + 1;

    int *count = (int*)calloc(amp, sizeof(int));
    int i;
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


int countInv(int *arr, int n) {

    int count = 0;
    int i = 0;

    for (i = 0; i < n-1; i++){

        if (arr[i]>arr[i+1])
            count++;
    }

    return count;
}

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





