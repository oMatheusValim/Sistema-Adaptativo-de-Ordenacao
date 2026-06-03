#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//cria struct de métricas
typedef struct {
    long long int compare;
    long long int movements;
    long long chamadas_recursivas;
    int max_depth;
    float tempo;
    int memory;
    int stability;
    int *ordenado;
} metrics;

metrics countingSort(int *vector, int size);
metrics insertionSort1(int arr[], int n);
metrics insertionSort(int arr[], int n);
metrics selectionSort1(int arr[], int n);
metrics selectionSort(int arr[], int n);
void merge(int arr[], int inicio, int meio, int fim, metrics *m);
void mergeSortRec(int arr[], int inicio, int fim, metrics *m, int profundidade);
metrics mergeSort (int arr[], int n);
void swap( int *a, int *b, metrics *m);
void heapify(int arr[],int n,int i,metrics *m,int profundidade);
metrics heapSort(int arr[], int n);
metrics countingSort1(int arr[], int n);
metrics countingSort(int arr[], int n);