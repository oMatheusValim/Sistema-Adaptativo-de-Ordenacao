#ifndef ALG_H
#define ALG_H

//cria struct de métricas
typedef struct {
    long long int compare;
    long long int movements;
    long long int chamadas_recursivas;
    int max_depth;
    float tempo;
    int memory;
    int stability;
    int *ordenado;
    char metodo;
} metrics;

metrics insertionSort(int arr[], int n);
metrics selectionSort(int arr[], int n);
metrics mergeSort (int arr[], int n);
metrics heapSort(int arr[], int n);
metrics countingSort(int arr[], int n);
int verify_sort(int arr[], int n);

#endif