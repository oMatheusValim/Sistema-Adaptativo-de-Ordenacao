#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "input_generator.h"

#define HAS_NEGATIVE 0.1
#define ADVERSARIAL 0.3

int **create_arrs(int quant, int max_size, int max_num){

    srand(time(NULL)); 

    int **arrs = (int**)malloc(quant * sizeof(int *));

    if (arrs == NULL){
        printf("ERRO! Alocação de memória para os dados de entradas falhou!");
        return NULL;
    }

    float adversarial;

    for (int i = 0; i < quant; i++){

        adversarial = chance(0, 100);

        if (adversarial > ADVERSARIAL){
            arrs[i] = random_arr(max_num, max_size);
        }

        else{
            arrs[i] = random_adversarial_arr(max_num, max_size);
        }
    }

    return arrs;
}

//Gera int aleatorio entre min (inclusivo) e max (exclusivo)
int random_int(int min, int max){
    if (min==max){
        return min;
    }

    return ((rand() % (max - min)) + min);
}

float chance(int lower_odds, int upper_odds){
    float odds = (float)(random_int(lower_odds, upper_odds+1)/100.0);
    return odds;
}

int *random_arr(int max_num, int max_size){

    int n_range = random_int(0, 5);

    int min_n = max_size * n_range/5;
    int max_n = max_size * (n_range+1)/5;

    int n = random_int(min_n, max_n+1);

    int *arr = (int *)malloc((n+1) * sizeof(int));

    if (arr == NULL){
        printf("ERRO! Alocação de memória para os dados de entradas falhou!");
        return NULL;
    }

    int size_amp = random_int(0, 101);
    int amp;
    int lower_amp;

    switch (size_amp){
        case 0 ... 30:
            lower_amp = 0;
            amp = max_num/5;
            break;

        case 31 ... 70:
            lower_amp = max_num/5;
            amp = 4*max_num/5;
            break;

        case 71 ... 100:
            lower_amp = 4*max_num/5;
            amp = max_num;
    }
    
    int min = random_int(0, (max_num-amp));
    float negative = chance(0, 100);

    if (negative < HAS_NEGATIVE){
        min = random_int(-1*max_num, 1);
    }

    int max = min + random_int(lower_amp, amp);

    if (max > max_num){
        max = max_num;
    }

    for (int i = 0; i < n; i++){
        arr[i] = random_int(min, max+1);
    }

    arr[n] = max_num + 10;
    return arr;
}

int *random_adversarial_arr(int max_num, int max_size){
    int n = chance(50, 100)* max_size;
    //printf("ARR2 n: %d\n", n);
    int *arr = (int *)malloc((n+1) * sizeof(int));

    if (arr == NULL){
        printf("ERRO! Alocação de memória para os dados de entradas falhou!");
        return NULL;
    }

    int min = chance(0, 10)*max_num;
    int max = chance(90, 100)*max_num;

    float negative = chance(0,100);

    if (negative < HAS_NEGATIVE){
        float shift_both = chance(0, 100);

        if (shift_both > 0.5){
            min = -1 * min;
            max = -1 * max;
        }

        else{
            min = -1 * min;
        }

    }

    int step = (max-min)/n;
    if (step < 0){
        step = -1*step;
    }

    float sequential;

    for (int i = 0; i < n; i++){
        sequential = chance(0, 100);

        if (sequential > 0.7){
            arr[i] = random_int(min, max);
        }

        else{
            arr[i] = min + i*step;
        }
    }

    arr[n] = max_num+1;

    return arr;
}