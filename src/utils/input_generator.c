#include "headers/utils.h"
#include "headers/input_generator.h"


int *random_arr(int max_num, int max_size){

    // Decide o tamanho do vetor
        int n = random_int(1, max_size);

    // Aloca o vetor com uma posicao a mais para o codigo de parada
        int *arr = (int *)malloc((n+1) * sizeof(int));

        if (arr == NULL){
            printf("ERRO! Alocação de memória para os dados de entradas falhou!");
            return NULL;
        }

    // Decide o menor e o maior valor presente no vetor
        int amp = random_float(0, 95) * max_num;
        int has_negative = atoi(getenv("NEGATIVE"));
        int negative = random_int(0, 101);

        int min = (negative < has_negative) ? random_int(0, (max_num-amp)) : random_int(-1 * max_num + 1, 1);

        int max = min + amp;

        if (max >= max_num)
            max = max_num - 1;
        
    // Preenche o vetor
        for (int i = 0; i < n; i++)
            arr[i] = random_int(min, max);

    // Coloca o código de parada (qualquer numero maior que o max_num)
        arr[n] = max_num + 10; 

    return arr;
}


int *random_sorted_arr(int max_num, int max_size){

    // Decide o tamanho do vetor
        int n = random_int(1, max_size);

    // Aloca o vetor com uma posição a mais para o código de parada
        int *arr = (int *)malloc((n+1) * sizeof(int));

        if (arr == NULL){
            printf("ERRO! Alocação de memória para os dados de entradas falhou!");
            return NULL;
        }

    // Decide o menor e o maior valor presente no vetor
        int amp = random_float(0, 95) * max_num;
        int has_negative = atoi(getenv("NEGATIVE"));
        int negative = random_int(0, 101);

        int min = (negative < has_negative) ? random_int(0, (max_num-amp)) : random_int(-1 * max_num + 1, 1);
        int max = (amp > 0) ? min + amp : min + 1;

        if (max >= max_num)
            max = max_num - 1;
    
    // Encontra o passo ideal para que o vetor fique ordenado
        int step = (max-min)/n;

        if (step < 0)
            step = -1*step;

        int duplications = 1;
        int i = 0;

        while (step == 0){
            i++;
            step = (pow(2, i)*(max - min))/n;
            duplications = 2*duplications;
        }    

        int duplicate_count = 1;
        int last_to_duplicate = min;

    // Preenche o vetor
        for (int i = 0; i < n; i++){
            if (duplicate_count % duplications == 0){
                arr[i] = min + i*step;
                last_to_duplicate = arr[i];
            }

            else{
                arr[i] = last_to_duplicate;
            }

            duplicate_count++;
        }

    // Coloca o código de parada
        arr[n] = max_num + 10;

    return arr;
}


int *random_reverse_arr(int max_num, int max_size){

    // Decide o tamanho do vetor
        int n = random_int(1, max_size);

    // Aloca o vetor com uma posição a mais para o código de parada
        int *arr = (int *)malloc((n+1) * sizeof(int));

        if (arr == NULL){
            printf("ERRO! Alocação de memória para os dados de entradas falhou!");
            return NULL;
        }

    // Decide o menor e o maior valor presente no vetor
        int amp = random_float(0, 95) * max_num;
        int has_negative = atoi(getenv("NEGATIVE"));
        int negative = random_int(0, 101);

        int min = (negative < has_negative) ? random_int(0, (max_num-amp)) : random_int(-1 * max_num + 1, 1);
        int max = (amp > 0) ? min + amp : min + 1;

        if (max >= max_num)
            max = max_num - 1;
    
    // Encontra o passo ideal para que o vetor fique ordenado
        int step = (max-min)/n;

        if (step < 0)
            step = -1*step;

        int duplications = 1;
        int i = 0;

        while (step == 0){
            i++;
            step = (pow(2, i)*(max - min))/n;
            duplications = 2*duplications;
        }    

        int duplicate_count = 1;
        int last_to_duplicate = max;

    // Preenche o vetor
        for (int i = 0; i < n; i++){
            if (duplicate_count % duplications == 0){
                arr[i] = max - i*step;
                last_to_duplicate = arr[i];
            }

            else{
                arr[i] = last_to_duplicate;
            }

            duplicate_count++;
        }

    // Coloca o código de parada
        arr[n] = max_num + 10;

    return arr;
}


int *random_equal_arr(int max_num, int max_size){

    // Decide o tamanho do vetor
        int n = random_int(1, max_size);

    // Aloca o vetor com uma posição a mais para o código de parada
        int *arr = (int *)malloc((n+1) * sizeof(int));

        if (arr == NULL){
            printf("ERRO! Alocação de memória para os dados de entradas falhou!");
            return NULL;
        }

    // Decide o valor que ocupara todas as posicoes do vetor
        int has_negative = atoi(getenv("NEGATIVE"));
        int negative = random_int(0, 101);
        int num = (negative < has_negative) ? random_int(0, max_num) : random_int(-1*max_num + 1, 1);

    // Preenche o vetor com o num
        for (int i = 0; i < n; i++)
            arr[i] = num;

    // Coloca o código de parada
        arr[n] = max_num + 10;

    return arr;
}


int *random_adversarial_arr(int max_num, int max_size){

    // Escolhe o tamanho do vetor
    // Ou vai ser entre 55% - 65% do maximo, para provocar a divisa merge/heap
    // Ou vai ser entre 1% - 15% do maximo, para provocar a divisa selection/insertion

        int which_adv = random_int(0, 101);
        int n =  max_size;

        n = (which_adv < 50) ? n*random_float(55, 65) : n*random_float(1, 15);

        if (n == 0)
            n = 1;


    // Aloca o vetor com uma posição a mais para o código de parada

        int *arr = (int *)malloc((n+1) * sizeof(int));

        if (arr == NULL){
            printf("ERRO! Alocação de memória para os dados de entradas falhou!");
            return NULL;
        }


    // Escolhe o min e o max bem separados para aumentar a amplitude e não cair no counting sort
        int min = random_float(0, 10) * max_num;
        int max = random_float(90, 100) * max_num;

    
    // Roda a probabilidade de incluir números negativos no array
        int has_negative = atoi(getenv("NEGATIVE"));
        int negative = random_int(0, 101);

        if (negative < has_negative)
                min = -1 * min;


    // Encontra o passo ideal para que o vetor fique reversamente ordenado
        int step = (max-min)/n;

        int duplications = 1;
        int i = 0;
        while (step == 0){
            i++;
            step = (pow(2, i)*(max - min))/n;
            duplications = 2*duplications;
        }    
        
    int pick_sequential;

    int duplicate_count = duplications;
    int last_to_duplicate = max;

    // Preenche o vetor
    for (int i = 0; i < n; i++){

        pick_sequential = random_int(0, 101);

        if (pick_sequential < 20){
            arr[i] = random_int(min, max);
        }

        else{
            if (duplicate_count % duplications == 0){
                arr[i] = max - i*step;
                last_to_duplicate = arr[i];
            }

            else{
                arr[i] = last_to_duplicate;
            }

            duplicate_count++;
        }
    }

    // Coloca o código de parada
        arr[n] = max_num + 10;

    return arr;
}


int **create_arrs(int quant, int max_size, int max_num){

    srand(time(NULL)); 

    int **arrs = (int**)malloc(quant * sizeof(int *));

    if (arrs == NULL){
        printf("ERRO! Alocação de memória para os dados de entradas falhou!");
        return NULL;
    }

    int choice;

    int adversarial = atoi(getenv("ADV"));
    int sorted = atoi(getenv("SRT"));
    int reverse_sorted = atoi(getenv("R_SRT"));
    int all_equal = atoi(getenv("EQUAL"));

    for (int i = 0; i < quant; i++){
        choice = random_int(1, 101);

        if (choice < adversarial){
            arrs[i] = random_adversarial_arr(max_num, max_size);
        } 
        
        else if (choice < adversarial + sorted){
            arrs[i] = random_sorted_arr(max_num, max_size);
        }
    
        else if (choice < adversarial + sorted + reverse_sorted){
            arrs[i] = random_reverse_arr(max_num, max_size);
        }

        else if (choice < adversarial + sorted + reverse_sorted + all_equal){
            arrs[i] = random_equal_arr(max_num, max_size);
        }
            
        else{
            arrs[i] = random_arr(max_num, max_size);
        }

    }
        

    return arrs;
}

