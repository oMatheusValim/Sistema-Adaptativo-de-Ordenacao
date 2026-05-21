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

    // Desconsiderando a coluna de index
    return (num_colums_csv + 1);
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
        arr[i] = atof(token);
        token = strtok(NULL, ",");
        i++;
    }

    return arr;
}


amp_analysis entry_amp(int *arr, int n){
    amp_analysis amp;

    amp.min = arr[0];
    amp.max = arr[0];

    for (int i = 1; i < n-1; i++){
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
    sd = sqrt(sd);

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

//CÓDIGO DA INTERNET!!!!!!

    // This function merges two sorted subarrays arr[l..m] and arr[m+1..r] 
    // and also counts inversions in the whole subarray arr[l..r]
    int countAndMerge(int arr[], int l, int m, int r) {
    
        // Counts in two subarrays
        int n1 = m - l + 1, n2 = r - m;

        // Set up two arrays for left and right halves
        int left[n1], right[n2];
        for (int i = 0; i < n1; i++)
            left[i] = arr[i + l];
        for (int j = 0; j < n2; j++)
            right[j] = arr[m + 1 + j];

        // Initialize inversion count (or result)
        // and merge two halves
        int res = 0;
        int i = 0, j = 0, k = l;
        while (i < n1 && j < n2) {

            // No increment in inversion count
            // if left[] has a smaller or equal element
            if (left[i] <= right[j]) 
                arr[k++] = left[i++];
        
            // If right is smaller, then it is smaller than n1-i 
            // elements because left[] is sorted
            else {
                arr[k++] = right[j++];
                res += (n1 - i);
            }
        }

        // Merge remaining elements
        while (i < n1)
            arr[k++] = left[i++];
        while (j < n2)
            arr[k++] = right[j++];

        return res;
    }

    // Function to count inversions in the array
    int countInv(int arr[], int l, int r) {
        int res = 0;
        if (l < r) {
            int m = (r + l) / 2;

            // Recursively count inversions
            // in the left and right halves
            res += countInv(arr, l, m);
            res += countInv(arr, m + 1, r);

            // Count inversions such that greater element is in 
            // the left half and smaller in the right half
            res += countAndMerge(arr, l, m, r);
        }
        return res;
    }

distribution_analysis entry_distr(int *arr, int n, amp_analysis amp){
    distribution_analysis distr;   

    distr.disorder = 0.0;
    if (n==2){
        if (arr[0]>arr[1])
        distr.disorder = 1.0;
    }
    if (n>2){
        int inversions = countInv(arr, 0, n);
        float max_inversions = n*(n-1)/2;
        distr.disorder = inversions/max_inversions;
    }

    distr.disp = entry_disp(arr, n);
    int unique_nums_count = count_uniques(arr, n, amp);

    distr.repetitions = n - unique_nums_count;
    distr.duplicate_density = distr.repetitions/n;


    return distr;
}


entry_analysis analyse_entry(char *line){

    entry_analysis ea;

    ea.index = entry_index(line);
    ea.size = entry_size(line);

    int *vector = allocate_arr(line, ea.size, ea.index);

    ea.amp = entry_amp(vector, ea.size);
    ea.distr = entry_distr(vector, ea.size, ea.amp);
        
    return ea;
}

