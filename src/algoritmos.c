#include "utils.h"
#include "algoritmos.h"


//função insertion 1 -  ordena o array utlizando insertion sort. retorna struct m com métricas de execução (sem o tempo)
metrics insertionSort1(int arr[], int n){
    
    metrics m = {0};
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 ) {
            m.compare++;

            if (arr[j]>key) {
                arr[j + 1] = arr[j];
                j--;
                m.movements++;
            }

            else {
                break;
            }
            
        }

        arr[j + 1] = key;
    }
    return m;
}

//função insertionSort, retorna o struct completo (com o tempo)
metrics insertionSort(int arr[], int n){
    clock_t begin = clock();
    metrics m = insertionSort1(arr, n);
    clock_t end = clock();
    
    m.time = (double)(end - begin)/ CLOCKS_PER_SEC;
    m.max_depth++;
    m.stability = 1;
    m.method = 'i';
    m.ordered = arr;
    return m;
}

//função selection sort, retorna um struct m de métricas da execução (sem o tempo)
metrics selectionSort1(int arr[], int n) {

    metrics m = {0};

    for (int i = 0; i < n - 1; i++) {
   
        int min_idx = i;

        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                m.compare++;
                min_idx = j;
            }
        }
        
        int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
        m.movements++;
    }
    return m;
}

//função selectionSort, retorna o struct metrics m completo (com tempo).
metrics selectionSort(int arr[], int n)
{
    clock_t begin = clock();
    metrics m =selectionSort1(arr, n);
    clock_t end = clock();
    m.max_depth++;
    m.time =  (double)(end - begin)/ CLOCKS_PER_SEC;
    
    m.stability = 0;
    m.method = 's';
    m.ordered = arr;

    return m;
}
//função merge: separa o vetor arr em dois subvetores e os aloca dinamicamente, comparando seus valores e os realocando em arr. 
//sem parâmetros retornados.  
void merge(int arr[], int begin, int middle, int end, metrics *m){
    
    int i, j, k;
    int n1 = middle - begin + 1;
    int n2 = end - middle;

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    m->memory += (n1 + n2)*sizeof(int);

    if (m == NULL){
        printf("Ponteiro Metrics é NULL");
        exit(EXIT_FAILURE);
    }
 
    for (i = 0; i < n1; i++){
        L[i] = arr[begin + i];
        m->movements++;
    }
       
    for (j = 0; j < n2; j++){
        R[j] = arr[middle + 1 + j];
        m->movements++;
    }

    i = 0;
    j = 0;
    k = begin;

    while (i < n1 && j < n2){
        m->compare++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
        m->movements++;
    }

    while (i < n1){
        arr[k] = L[i];
        i++;
        k++;
        m->movements++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        m->movements++;
    }

    free(L);
    free(R);
}

//função mergeSortRec: divide recursivamente o vetor arr. sem parâmetros retornados.
void mergeSortRec(int arr[], int begin, int end, metrics *m, int depth){

    m->recursive_calls++;
    if (depth > m->max_depth){
        m->max_depth = depth;
    }


    if (begin < end){
        int middle = begin + (end - begin)/ 2;

        mergeSortRec(arr, begin, middle, m, depth + 1);
        mergeSortRec(arr, middle + 1, end, m, depth + 1);

        merge(arr, begin, middle, end, m);
    }
}

//função mergeSort: realiza a ordenação utilizando o algoritmo merge sort, chamando para isso a função recursiva mergeSortRec.
//Retorna struct m de  métricas de execução (com tempo)
metrics mergeSort (int arr[], int n){
    metrics m = {0};

    clock_t begin = clock();

    mergeSortRec(arr, 0, n-1, &m, 1);

    clock_t end = clock();

    m.time = (double)(end - begin)/ CLOCKS_PER_SEC;
    m.stability = 1;
    m.method = 'm';
    m.ordered = arr;
    return m;
}

void swap( int *a, int *b, metrics *m){
    int temp= *a;
    *a = *b;
    *b = temp;
    m->movements++;
}

//função heapify: ajusta a árvore binária para que ela satisfaça a propriedade de heap máximo (nenhum pai menor que o filho);
//sem parâmetros retornados
void heapify(int arr[], int n, int i, metrics *m, int depth)
{
    m->recursive_calls++;

    if (depth > m->max_depth)
        m->max_depth = depth;

    int max = i;

    int left = 2*i + 1;
    int right  = 2*i + 2;

    if (left < n) {

        m->compare++;

        if (arr[left] > arr[max])
            max = left;
    }

    if (right < n) {

        m->compare++;

        if (arr[right] > arr[max])
            max = right;
    }

    if (max != i) {

        swap(&arr[i], &arr[max], m);

        heapify(arr, n, max, m, depth + 1);
    }
}

//função heapSort: Converte o vetor em heap máximo chamando a função heapify recursivamente. retorna struct m de métricas de execução (com tempo)
metrics heapSort(int arr[], int n){
    metrics m = {0};

    clock_t begin = clock();

    for (int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i, &m, 1);


    for (int i = n - 1; i > 0; i--) {

        swap(&arr[0], &arr[i], &m);

        heapify(arr, i, 0, &m, 1);
    }

    clock_t end = clock();

    m.time =
        (double)(end - begin) / CLOCKS_PER_SEC;
    
    m.stability = 0;
    m.method = 'h';
    m.ordered = arr;
    return m;
}

//função countingSort1: realiza a ordenação utilizando o algoritmo de ordenação counting sort. retorna struct m de métricas de execução sem o tempo de ordenação.
metrics countingSort1(int arr[], int n){

    metrics m = {0};


    m.stability = 1;

    if (n <= 1){
        return m;
    }

    int min = arr[0];
    int max = arr[0];


    for (int i = 0; i < n; i++){

        if (arr[i] < min){
            min = arr[i];
        }

        if ( arr[i] > max){
            max = arr[i];
        }

        m.compare+=2;
    }

    
    int *aux = (int*)calloc(max - min + 1, sizeof(int));
    m.memory+=(max - min + 1)*(sizeof(int));

    if (aux == NULL){
        printf("Alocation error\n");
        return m;
    }

    
    for (int i = 0; i < n; i++){
        aux[arr[i]-min]++;
        m.movements++;
    }

    int index = 0;

    for (int i = 0; i < max-min + 1; i++){
        while (aux[i] > 0){

            arr[index++] = i + min;
            aux[i]--;
            m.movements++;
        } 
    }
    free(aux);
    return m;
}

//Função countingSort: utiliza a função countingSort1 para realizar a ordenação utilizando o algoritmo counting sort e conta o tempo de execução. retorna struct m de métricas de execução com tempo de ordenação.
metrics countingSort(int arr[], int n){
    clock_t begin = clock();
    metrics m = countingSort1(arr, n);
    clock_t end = clock();

    m.time = (double)(end - begin) / CLOCKS_PER_SEC;
    m.method = 'c';
    m.ordered = arr;
    m.max_depth = 1;
    return m;
}

//Função verify_sort: verifica se o vetor arr está ordenado. retorna 1 caso TRUE e -1 caso FALSE.
int verify_sort(int arr[], int n){
    for (int i = 1; i < n; i++){
        if (arr[i-1] > arr[i])   return -1;
    }

    return 1;
}

