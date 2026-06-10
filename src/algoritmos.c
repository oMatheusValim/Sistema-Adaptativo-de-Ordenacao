#include "utils/headers/utils.h"
#include "headers/algoritmos.h"


//função insertion 1 - faz e retorna nmr de comparações e número de movimentações.
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
    clock_t inicio = clock();
    metrics m = insertionSort1(arr, n);
    clock_t fim = clock();
    
    m.tempo = (double)(fim - inicio)/ CLOCKS_PER_SEC;
    m.max_depth++;
    m.stability = 1;
    m.metodo = 'i';
    m.ordenado = arr;
    return m;
}

//primeira função de inserção, retorna o struct m sem o tempo
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

//função selectionSort, retorna o struct completo (com o tempo)
metrics selectionSort(int arr[], int n)
{
    clock_t inicio = clock();
    metrics m =selectionSort1(arr, n);
    clock_t fim = clock();
    m.max_depth++;
    m.tempo =  (double)(fim - inicio)/ CLOCKS_PER_SEC;
    
    m.stability = 0;
    m.metodo = 's';
    m.ordenado = arr;

    return m;
}

void merge(int arr[], int inicio, int meio, int fim, metrics *m){
    
    int i, j, k;
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    int current_memory = (n1 + n2) * sizeof(int);
    if(current_memory > m->memory) m->memory = current_memory;

    if (m == NULL){
        printf("Ponteiro Metrics é NULL");
        exit(EXIT_FAILURE);
    }
 
    for (i = 0; i < n1; i++){
        L[i] = arr[inicio + i];
        m->movements++;
    }
       
    for (j = 0; j < n2; j++){
        R[j] = arr[meio + 1 + j];
        m->movements++;
    }

    i = 0;
    j = 0;
    k = inicio;

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

void mergeSortRec(int arr[], int inicio, int fim, metrics *m, int profundidade){

    m->chamadas_recursivas++;
    if (profundidade > m->max_depth){
        m->max_depth = profundidade;
    }


    if (inicio < fim){
        int meio = inicio + (fim - inicio)/ 2;

        mergeSortRec(arr, inicio, meio, m, profundidade + 1);
        mergeSortRec(arr, meio + 1, fim, m, profundidade + 1);

        merge(arr, inicio, meio, fim, m);
    }
}

metrics mergeSort (int arr[], int n){
    metrics m = {0};

    clock_t inicio = clock();

    mergeSortRec(arr, 0, n-1, &m, 1);

    clock_t fim = clock();

    m.tempo = (double)(fim - inicio)/ CLOCKS_PER_SEC;
    m.stability = 1;
    m.metodo = 'm';
    m.ordenado = arr;
    return m;
}

void swap( int *a, int *b, metrics *m){
    int temp= *a;
    *a = *b;
    *b = temp;
    m->movements++;
}

void heapify(int arr[], int n, int i, metrics *m, int profundidade)
{
    m->chamadas_recursivas++;

    if (profundidade > m->max_depth)
        m->max_depth = profundidade;

    int maior = i;

    int esquerda = 2*i + 1;
    int direita  = 2*i + 2;

    if (esquerda < n) {

        m->compare++;

        if (arr[esquerda] > arr[maior])
            maior = esquerda;
    }

    if (direita < n) {

        m->compare++;

        if (arr[direita] > arr[maior])
            maior = direita;
    }

    if (maior != i) {

        swap(&arr[i], &arr[maior], m);

        heapify(arr, n, maior, m, profundidade + 1);
    }
}

metrics heapSort(int arr[], int n){
    metrics m = {0};

    clock_t inicio = clock();

    for (int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i, &m, 1);


    for (int i = n - 1; i > 0; i--) {

        swap(&arr[0], &arr[i], &m);

        heapify(arr, i, 0, &m, 1);
    }

    clock_t fim = clock();

    m.tempo =
        (double)(fim - inicio) / CLOCKS_PER_SEC;
    
    m.stability = 0;
    m.metodo = 'h';
    m.ordenado = arr;
    return m;
}

metrics countingSort1(int arr[], int n){

    metrics m = {0};


    m.stability = 1;

    if (n <= 1){
        return m;
    }

    int menor = arr[0];
    int maior = arr[0];


    for (int i = 0; i < n; i++){

        if (arr[i] < menor){
            menor = arr[i];
        }

        if ( arr[i] > maior){
            maior = arr[i];
        }

        m.compare+=2;
    }

    
    int *aux = calloc(maior - menor + 1, sizeof(int));
    m.memory+=(maior - menor + 1)*(sizeof(int));

    if (aux == NULL){
        printf("Alocation error\n");
        return m;
    }

    
    for (int i = 0; i < n; i++){
        aux[arr[i]-menor]++;
        m.movements++;
    }

    int index = 0;

    for (int i = 0; i < maior-menor + 1; i++){
        while (aux[i] > 0){

            arr[index++] = i + menor;
            aux[i]--;
            m.movements++;
        } 
    }
    free(aux);
    return m;
}

metrics countingSort(int arr[], int n){
    clock_t inicio = clock();
    metrics m = countingSort1(arr, n);
    clock_t fim = clock();

    m.tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    m.metodo = 'c';
    m.ordenado = arr;
    m.max_depth = 1;
    return m;
}

int verify_sort(int arr[], int n){
    for (int i = 1; i < n; i++){
        if (arr[i-1] > arr[i])   return -1;
    }

    return 1;
}

