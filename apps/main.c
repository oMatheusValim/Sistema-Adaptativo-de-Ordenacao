#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "../include/input_generator.h"
#include "../include/io.h"
#include "../include/adaptive.h"
#include "../include/algoritmos.h"

// Constantes baseadas no seu código original
#define MAX_NUM 50000
#define MAX_SIZE 50000
#define QUANT_ARQUIVO 500

int main(int argc, char *argv[]) {
    bool modo_adaptativo = false;
    char algoritmo[20] = "";
    int tamanho = 0; 
    char input_file[256] = "";
    char tipo[30] = "aleatorio";
    int seed = 42; 
    char output_file[256] = "";
    bool verbose = false;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--modo") == 0 && i + 1 < argc) {
            if (strcmp(argv[i+1], "adaptativo") == 0) modo_adaptativo = true;
            i++;
        } else if (strcmp(argv[i], "--algoritmo") == 0 && i + 1 < argc) {
            strcpy(algoritmo, argv[i+1]);
            i++;
        } else if (strcmp(argv[i], "--tamanho") == 0 && i + 1 < argc) {
            tamanho = atoi(argv[i+1]);
            i++;
        } else if (strcmp(argv[i], "--input") == 0 && i + 1 < argc) {
            strcpy(input_file, argv[i+1]);
            i++;
        } else if (strcmp(argv[i], "--tipo") == 0 && i + 1 < argc) {
            strcpy(tipo, argv[i+1]);
            i++;
        } else if (strcmp(argv[i], "--seed") == 0 && i + 1 < argc) {
            seed = atoi(argv[i+1]);
            i++;
        } else if (strcmp(argv[i], "--output") == 0 && i + 1 < argc) {
            strcpy(output_file, argv[i+1]);
            i++;
        } else if (strcmp(argv[i], "--verbose") == 0) {
            verbose = true;
        }
    }

    srand(seed);

    if (verbose) {
        printf("=== Configurações da Execução ===\n");
        printf("Modo Adaptativo: %s\n", modo_adaptativo ? "ON" : "OFF");
        if (!modo_adaptativo) printf("Algoritmo Fixo: %s\n", algoritmo);
        if (tamanho > 0) printf("Tamanho gerado: %d (Tipo: %s)\n", tamanho, tipo);
        if (strlen(input_file) > 0) printf("Arquivo de Input: %s\n", input_file);
        printf("Seed: %d\n=================================\n\n", seed);
    }

    metrics m = {0}; // Inicializa a struct de métricas

    if (strlen(input_file) > 0) {
        if (verbose) printf("Lendo dados do arquivo %s...\n", input_file);
        
        char **lines = read_data_input(input_file, QUANT_ARQUIVO, MAX_NUM, MAX_SIZE);
        int contagens[5] = {0}; // c, h, i, m, s

        if (lines == NULL) {
            printf("ERRO: Falha ao carregar os dados de %s. Encerrando execução.\n", input_file);
        return 1;
        }

        for (int i = 1; i < QUANT_ARQUIVO; i++) {
            if (lines[i] != NULL) {
                entry_analysis ea = analyse_entry(lines[i]);

                if (modo_adaptativo) {
                    m = decision_tree(ea, MAX_SIZE);
                } else {
                    if (strcmp(algoritmo, "merge") == 0) m = mergeSort(ea.vector, ea.size);
                    else if (strcmp(algoritmo, "heap") == 0) m = heapSort(ea.vector, ea.size);
                    else if (strcmp(algoritmo, "selection") == 0) m = selectionSort(ea.vector, ea.size);
                    else if (strcmp(algoritmo, "insertion") == 0) m = insertionSort(ea.vector, ea.size);
                    else if (strcmp(algoritmo, "counting") == 0) m = countingSort(ea.vector, ea.size);
                }

                if (verbose) {
                    printf("Linha %d | Tamanho: %d | Tempo: %f | Algoritmo usado: %c\n", i, ea.size, m.tempo, m.metodo);
                }

                // Estatísticas do adaptativo
                switch (m.metodo) {
                    case 'c': contagens[0]++; break;
                    case 'h': contagens[1]++; break;
                    case 'i': contagens[2]++; break;
                    case 'm': contagens[3]++; break;
                    case 's': contagens[4]++; break;
                }

                if (ea.vector != NULL) free(ea.vector);
            }
        }
        
        if (modo_adaptativo) {
            printf("\n--- ESTATÍSTICAS DA ÁRVORE ---\n");
            printf("Counting: %d | Heap: %d | Insertion: %d | Merge: %d | Selection: %d\n", 
                   contagens[0], contagens[1], contagens[2], contagens[3], contagens[4]);
        }

        // Liberação de memória das linhas
        for (int i = 0; i < QUANT_ARQUIVO; i++) {
            if (lines[i] != NULL) free(lines[i]);
        }
        free(lines);

    } else if (tamanho > 0) {
        // FLUXO 2: Gerando um array único dinamicamente
        int *dados = NULL;
        
        if (strcmp(tipo, "aleatorio") == 0) dados = random_arr(MAX_NUM, tamanho);
        else if (strcmp(tipo, "quase_ordenado") == 0) dados = random_adversarial_arr(MAX_NUM, tamanho);
        else if (strcmp(tipo, "reverso") == 0) dados = random_reverse_arr(MAX_NUM, tamanho);
        else if (strcmp(tipo, "repetidos") == 0) dados = random_equal_arr(MAX_NUM, tamanho);

        if (dados != NULL) {
            if (verbose) printf("Iniciando ordenação do array de tamanho %d...\n", tamanho);

            if (modo_adaptativo) {
                entry_analysis ea;
                ea.vector = dados;
                ea.size = tamanho;
                ea.index = 1;
                m = decision_tree(ea, tamanho);
            } else {
                if (strcmp(algoritmo, "insertion") == 0) m = insertionSort(dados, tamanho);
                else if (strcmp(algoritmo, "selection") == 0) m = selectionSort(dados, tamanho);
                else if (strcmp(algoritmo, "merge") == 0) m = mergeSort(dados, tamanho);
                else if (strcmp(algoritmo, "counting") == 0) m = countingSort(dados, tamanho);
                else if (strcmp(algoritmo, "heap") == 0) m = heapSort(dados, tamanho);
            }

            printf("\n--- RESULTADO ---\n");
            printf("Algoritmo executado: %c\n", m.metodo);
            printf("Tempo de execução: %f segundos\n", m.tempo);
            
            free(dados);
        }

    } else {
        printf("ERRO: É obrigatório informar um arquivo (--input) ou um tamanho para gerar (--tamanho).\n");
        printf("Exemplo: ./programa --modo adaptativo --input entrada.csv\n");
        return 1;
    }

    if (strlen(output_file) > 0) {
        FILE *f = fopen(output_file, "a");
        if (f) {
            fprintf(f, "%c,%d,%f\n", m.metodo, tamanho, m.tempo);
            fclose(f);
            if (verbose) printf("Métricas salvas em %s\n", output_file);
        } else {
            printf("Erro ao criar o arquivo de output %s\n", output_file);
        }
    }

    if (verbose) printf("\nExecução finalizada com sucesso.\n");
    return 0;
}