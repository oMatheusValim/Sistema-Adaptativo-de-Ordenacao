#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "input_generator.h"

#define HAS_NEGATIVE 0.1
#define ADVERSARIAL 30
#define ALREADY_SORTED 5
#define REVERSE_SORTED 4
#define ALL_EQUAL 1

int **create_arrs(int quant, int max_size, int max_num){

    srand(time(NULL)); 

    int **arrs = (int**)malloc(quant * sizeof(int *));

    if (arrs == NULL){
        printf("ERRO! Alocação de memória para os dados de entradas falhou!\n");
        return NULL;
    }

    int choice;

    for (int i = 0; i < quant; i++){
        choice = random_int(1, 101);
        
        switch(choice){

            case 0 ... ADVERSARIAL - 1:
                arrs[i] = random_adversarial_arr(max_num, max_size);
                break;
            
            case ADVERSARIAL ... ADVERSARIAL + ALREADY_SORTED - 1:
                arrs[i] = random_sorted_arr(max_num, max_size);
                break;

            case ADVERSARIAL + ALREADY_SORTED ... ADVERSARIAL + ALREADY_SORTED + REVERSE_SORTED - 1:
                arrs[i] = random_reverse_arr(max_num, max_size);
                break;

            case ADVERSARIAL + ALREADY_SORTED + REVERSE_SORTED ... ADVERSARIAL + ALREADY_SORTED + REVERSE_SORTED + ALL_EQUAL - 1:
                arrs[i] = random_equal_arr(max_num, max_size);
                break;
            
            default:
                arrs[i] = random_arr(max_num, max_size);
                break;
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

float random_float(int lower_odds, int upper_odds){
    float odds = (float)(random_int(lower_odds, upper_odds+1)/100.0);
    return odds;
}

int *random_arr(int max_num, int max_size){

    int n = max_size;
    int *arr = (int *)calloc(n, sizeof(int));

    if (arr == NULL){
        printf("ERRO! Alocação de memória para os dados de entradas falhou!\n");
        return NULL;
    }

    // Decide a amplitude do vetor
    int range_amp = random_int(0, 101);
    int max_amp;
    int min_amp;

    switch (range_amp){
        case 0 ... 30:
            min_amp = 0;
            max_amp = max_num/5;
            break;
        case 31 ... 70:
            min_amp = max_num/5;
            max_amp = 4*max_num/5;
            break;
        case 71 ... 100:
            min_amp = 4*max_num/5;
            max_amp = max_num;
            break;
    }
    
    // Decide o menor e o maior valor presente no vetor
    int min = random_int(0, (max_num-max_amp));
    float negative = random_float(0, 100);

    if (negative < HAS_NEGATIVE){
        min = random_int(-1*max_num, 1);
    }

    int max = min + random_int(min_amp, max_amp);

    if (max > max_num){
        max = max_num - 1;
    }

    // Preenche o vetor
    for (int i = 0; i < n; i++){
        arr[i] = random_int(min, max+1);
    }

    return arr;
}

int *random_sorted_arr(int max_num, int max_size){

    int n = max_size;
    int *arr = (int *)calloc(n, sizeof(int));

    if (arr == NULL){
        printf("ERRO! Alocação de memória para os dados de entradas falhou!\n");
        return NULL;
    }

    // Decide a amplitude do vetor
    int range_amp = random_int(0, 101);
    int max_amp = 0;
    int min_amp = 0;

    switch (range_amp){
        case 0 ... 30:
            min_amp = 0;
            max_amp = max_num/5;
            break;
        case 31 ... 70:
            min_amp = max_num/5;
            max_amp = 4*max_num/5;
            break;
        case 71 ... 100:
            min_amp = 4*max_num/5;
            max_amp = max_num;
            break;
    }
    
    // Decide o menor e o maior valor presente no vetor
    int min = random_int(0, (max_num-max_amp));
    float negative = random_float(0, 100);

    if (negative < HAS_NEGATIVE){
        min = random_int(-1*max_num, 1);
    }

    int max = min + random_int(min_amp, max_amp);

    if (max > max_num){
        max = max_num - 1;
    }
    
    // Encontra o passo ideal para que o vetor fique ordenado
    int step = (max-min)/n;
    if (step < 0){
        step = -1*step;
    }

    int duplications = 1;
    int count = 0;
    while (step == 0){
        count++;
        step = (pow(2, count)*(max - min))/n;
        duplications = 2*duplications;
    }    

    int duplicate_count = 1;
    int last_to_duplicate = min;

    // Preenche o vetor
    for (int i = 0; i < n; i++){
        if (duplicate_count % duplications == 0){
            arr[i] = min + i*step;
            last_to_duplicate = arr[i];
        } else {
            arr[i] = last_to_duplicate;
        }
        duplicate_count++;
    }

    return arr;
}

int *random_reverse_arr(int max_num, int max_size){

    int n = max_size;
    int *arr = (int *)calloc(n, sizeof(int));

    if (arr == NULL){
        printf("ERRO! Alocação de memória para os dados de entradas falhou!\n");
        return NULL;
    }

    // Decide a amplitude do vetor
    int range_amp = random_int(0, 101);
    int max_amp = 0;
    int min_amp = 0;

    switch (range_amp){
        case 0 ... 30:
            min_amp = 0;
            max_amp = max_num/5;
            break;
        case 31 ... 70:
            min_amp = max_num/5;
            max_amp = 4*max_num/5;
            break;
        case 71 ... 100:
            min_amp = 4*max_num/5;
            max_amp = max_num;
            break;
    }
    
    // Decide o menor e o maior valor presente no vetor
    int min = random_int(0, (max_num-max_amp));
    float negative = random_float(0, 100);

    if (negative < HAS_NEGATIVE){
        min = random_int(-1*max_num, 1);
    }

    int max = min + random_int(min_amp, max_amp);

    if (max > max_num){
        max = max_num - 1;
    }
    
    // Encontra o passo ideal para que o vetor fique reversamente ordenado
    int step = (max-min)/n;
    if (step < 0){
        step = -1*step;
    }

    int duplications = 1;
    int count = 0;
    while (step == 0){
        count++;
        step = (pow(2, count)*(max - min))/n;
        duplications = 2*duplications;
    }    

    int duplicate_count = 1;
    int last_to_duplicate = max;

    for (int i = 0; i < n; i++){
        if (duplicate_count % duplications == 0){
            arr[i] = max - i*step;
            last_to_duplicate = arr[i];
        } else {
            arr[i] = last_to_duplicate;
        }
        duplicate_count++;
    }

    return arr;
}

int *random_equal_arr(int max_num, int max_size){

    int n = max_size;
    int *arr = (int *)calloc(n, sizeof(int));

    if (arr == NULL){
        printf("ERRO! Alocação de memória para os dados de entradas falhou!\n");
        return NULL;
    }

    int num = random_int(0, max_num);
    float negative = random_float(0, 100);
    
    if (negative < HAS_NEGATIVE){
        num = random_int(-1*max_num, 1);
    }

    for (int i = 0; i < n; i++){
        arr[i] = num;
    }

    return arr;
}

int *random_adversarial_arr(int max_num, int max_size){

    int n = max_size;
    int *arr = (int *)calloc(n, sizeof(int));

    if (arr == NULL){
        printf("ERRO! Alocação de memória para os dados de entradas falhou!\n");
        return NULL;
    }

    int min = random_float(0, 10) * max_num;
    int max = random_float(90, 100) * max_num;
    float negative = random_float(0, 100);

    if (negative < HAS_NEGATIVE){
        min = -1 * min;
    }

    int step = (max - min) / n;

    if (step < 0){
        step = -1 * step;
    }

    int duplications = 1;
    int count = 0; 

    while (step == 0){
        count++;
        step = (pow(2, count) * (max - min)) / n;
        duplications = 2 * duplications;
    }
    
    float sequential;
    int duplicate_count = duplications;
    int last_to_duplicate = min;

    for (int i = 0; i < n; i++){
        sequential = random_float(0, 100);

        if (sequential < 0.3){
            arr[i] = random_int(min, max);
        }
        else{
            if (duplicate_count % duplications == 0){
                arr[i] = min + i * step;
                last_to_duplicate = arr[i];
            }
            else{
                arr[i] = last_to_duplicate;
            }
            duplicate_count++;
        }
    }

    return arr;
}