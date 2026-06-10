#ifndef ALG_H
#define ALG_H

//Armazena as métricas de execução do algoritmos de ordenação
typedef struct {
    long long int compare;
    long long int movements;
    long long int recursive_calls;
    int max_depth;
    float time;
    int memory;
    int stability;
    int *ordered;
    char method;
} metrics;

metrics insertionSort(int arr[], int n);
metrics selectionSort(int arr[], int n);
metrics mergeSort (int arr[], int n);
metrics heapSort(int arr[], int n);
metrics countingSort(int arr[], int n);
int verify_sort(int arr[], int n);

#endif