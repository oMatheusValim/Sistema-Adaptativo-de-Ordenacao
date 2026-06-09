#include "utils.h"
#include "io.h"

void write_csv(int **arrs, char* filename, int quant, int max_size, int max_num){
    FILE *fptr;

    fptr = fopen(filename, "w");

    if (fptr == NULL) {
        printf("Erro ao abrir o arquivo de entrada\n");
        return;
    }

    fprintf(fptr, "index,nums...\n");
    fprintf(fptr, "%d, %d, %d\n", quant, max_size, max_num);
    for (int i = 0; i < quant; i++){
        fprintf(fptr, "%d,", i);

        int j = 0;

        while(arrs[i][j] <= max_num){
            if (arrs[i][j+1] <= max_num)
                fprintf(fptr, "%d,", arrs[i][j]);

            else{
                fprintf(fptr, "%d\n", arrs[i][j]);
                break;
            }

            j++;
        }
    }

    fclose(fptr);
}


csv_extraction read_csv(char* file_name){

    csv_extraction csv_results = {0};

    csv_results.quant = -1; //Código de erro para a main

    FILE *fptr;

    fptr = fopen(file_name, "r");

    if (fptr == NULL) {
        printf("Erro! Não foi possível abrir o arquivo %s para leitura!\n", file_name);
        return csv_results;
    }

    char temp_buffer[40];

    fgets(temp_buffer, 35, fptr); // Linha de header
    fgets(temp_buffer, 35, fptr); // Linha com constantes importantes

    int quant;
    int max_size;
    int max_num;

    char *token = strtok(temp_buffer, ",");  
 
    if (token != NULL) quant = atoi(token);    
    else{
        printf("Erro! Não foi possível identificar o valor de QUANT no arquivo %s!\n", file_name);
        return csv_results;
    }

    token = strtok(NULL, ",");  

    if (token != NULL) max_size = atoi(token);
    else{
        printf("Erro! Não foi possível identificar o valor de MAX_SIZE no arquivo %s!\n", file_name);
        return csv_results;
    }

    token = strtok(NULL, "\n");  

    if (token != NULL) max_num = atoi(token);
    else{
        printf("Erro! Não foi possível identificar o valor de MAX_NUM no arquivo %s!\n", file_name);
        return csv_results;
    }

    int buffers_size = max_size*(((int)log10(max_num)) + 2);
    char buffer[buffers_size];
    char **lines = (char **)malloc((quant) * sizeof(char *));

    if (lines == NULL){
        printf("Erro! Não foi possível alocar memoria para o texto do csv!\n");
        return csv_results;
    }

    int i = 0;
    while (fgets(buffer, buffers_size-2, fptr) != NULL && i < quant) {

        int length = strlen(buffer);
        lines[i] = malloc((length + 1) * sizeof(char));

        if (lines[i] != NULL){
            strcpy(lines[i], buffer);
        }

        else{
            printf("Erro ao alocar a linha [%d]!\n", i);
        }
        i++;
    }

    fclose(fptr);

    csv_results.lines = lines;
    csv_results.quant = quant;
    csv_results.max_size = max_size;
    csv_results.max_num = max_num;

    return csv_results;
}


void decision_tree_statistics(entry_analysis *ea, metrics *m, int *method_count, int quant){

    tree_statistics ts[5] = {0, 0, 0, 0, 0};

    int method;

    for (int i = 0; i < quant; i++){
        method = char_to_int(m[i].metodo);

        ts[method].avg_t += m[i].tempo;
        ts[method].avg_n += ea[i].size;
        ts[method].avg_amp += ea[i].amp;
        ts[method].avg_distr += ea[i].distr.disorder;
        ts[method].avg_cmp += m[i].compare;
        ts[method].avg_mov += m[i].movements;
        ts[method].avg_mem += m[i].memory;
        ts[method].avg_rec += m[i].chamadas_recursivas;
        ts[method].avg_max_depth += m[i].max_depth;
    }

    // Abre o arquivo .txt para salvar a tabela
    FILE *fptr = fopen("tabela_resultados.txt", "a");
    if (fptr == NULL) {
        printf("Erro ao criar o arquivo tabela_resultados.txt!\n");
        return;
    }

    printf("\n\n==================================== DISTRIBUIÇÃO DE ALGOTIMOS PELA ÁRVORE DE DECISÃO ===================================================\n\n");
    printf("            count - %%      avg(t)    avg(n)    avg(amp)   avg(distr)   avg(cmp)    avg(mov)   avg(mem)   avg(rec)   avg(max_depth)\n");

    //o que vai pro txt é o fprintf
    fprintf(fptr, "\n\n==================================== DISTRIBUIÇÃO DE ALGOTIMOS PELA ÁRVORE DE DECISÃO =============================================\n\n");
    fprintf(fptr, "            count - %%      avg(t)    avg(n)    avg(amp)   avg(distr)   avg(cmp)    avg(mov)   avg(mem)   avg(rec)   avg(max_depth)\n");


    for (int i = 0; i < 5; i++){

        switch (i){
            case 0:
                printf("%-12s", "COUNT");
                fprintf(fptr, "%-12s", "COUNT");
                break;
            
            case 1:
                printf("%-12s", "HEAP");
                fprintf(fptr, "%-12s", "HEAP");
                break;

            case 2:
                printf("%-12s", "INSERTION");
                fprintf(fptr, "%-12s", "INSERTION");
                break;

            case 3:
                printf("%-12s", "MERGE");
                fprintf(fptr, "%-12s", "MERGE");
                break;

            case 4:
                printf("%-12s", "SELECTION");
                fprintf(fptr, "%-12s", "SELECTION");
                break;
            }

        if (method_count[i] == 0){
            printf("    0 - 0.00   -         -         -          -            -           -          -          -          -\n");
            fprintf(fptr, "    0 - 0.00   -         -         -          -            -           -          -          -          -\n");
            continue;
        }

        printf("%5d - %-7.2f", method_count[i], (float)method_count[i]/quant);                                                                                                                                                                                                                                                             
        printf("%-10.5f", ts[i].avg_t/method_count[i]);
        printf("%-10d", ts[i].avg_n/method_count[i]);
        printf("%-11d", ts[i].avg_amp/method_count[i]);
        printf("%-13.3f", ts[i].avg_distr/method_count[i]);
        printf("%-12lld", ts[i].avg_cmp/method_count[i]);
        printf("%-11lld", ts[i].avg_mov/method_count[i]);
        printf("%-11lld", ts[i].avg_mem/method_count[i]);
        printf("%-11lld", ts[i].avg_rec/method_count[i]);
        printf("%-13d\n", ts[i].avg_max_depth/method_count[i]);

        fprintf(fptr, "%5d - %-7.2f", method_count[i], (float)method_count[i]/quant);                                                                                                                                                                                                                                                             
        fprintf(fptr, "%-10.5f", ts[i].avg_t/method_count[i]);
        fprintf(fptr, "%-10d", ts[i].avg_n/method_count[i]);
        fprintf(fptr, "%-11d", ts[i].avg_amp/method_count[i]);
        fprintf(fptr, "%-13.3f", ts[i].avg_distr/method_count[i]);
        fprintf(fptr, "%-12lld", ts[i].avg_cmp/method_count[i]);
        fprintf(fptr, "%-11lld", ts[i].avg_mov/method_count[i]);
        fprintf(fptr, "%-11lld", ts[i].avg_mem/method_count[i]);
        fprintf(fptr, "%-11lld", ts[i].avg_rec/method_count[i]);
        fprintf(fptr, "%-13d\n", ts[i].avg_max_depth/method_count[i]);
    }


    //Fechamento do arquivo
    fclose(fptr);
}


void adaptive_comparison(metrics **m, int quant, int algs_count){

    adaptive_statistics as[algs_count];

    for (int i = 0; i < algs_count; i++){
        as[i].method = m[i][0].metodo;
        as[i].avg_cmp = 0;
        as[i].avg_max_depth = 0;
        as[i].avg_mem = 0;
        as[i].avg_mov = 0;
        as[i].avg_rec = 0;
        as[i].avg_t = 0;
    
        for (int j = 0; j < quant; j++){

            if (m[i][j].metodo != as[i].method){
                as[i].method = 'a';
            }

            as[i].avg_t += m[i][j].tempo;
            as[i].avg_cmp += m[i][j].compare;
            as[i].avg_mov += m[i][j].movements;
            as[i].avg_mem += m[i][j].memory;
            as[i].avg_rec += m[i][j].chamadas_recursivas;
            as[i].avg_max_depth += m[i][j].max_depth;
        }
    }


    // Abre o arquivo .txt para salvar a tabela
    FILE *fptr = fopen("tabela_resultados.txt", "w");
    if (fptr == NULL) {
        printf("Erro ao criar o arquivo tabela_resultados.txt!\n");
        return;
    }

    printf("============= COMPARAÇÃO DA ÁRVORE DE DECISÃO COM UM ALGORITMO ESTÁTICO ============\n\n");
    printf("            avg(t)     avg(cmp)    avg(mov)   avg(mem)   avg(rec)   avg(max_depth)\n");

    //o que vai pro txt é o fprintf
    fprintf(fptr, "============= COMPARAÇÃO DA ÁRVORE DE DECISÃO COM UM ALGORITMO ESTÁTICO ============\n\n");
    fprintf(fptr, "            avg(t)     avg(cmp)    avg(mov)   avg(mem)   avg(rec)   avg(max_depth)\n");

    for (int i = 0; i < algs_count; i++){

        switch (as[i].method){
            case 'a':
                printf("%-12s", "ADAPTATIVO");
                fprintf(fptr, "%-12s", "ADAPTATIVO");
                break;

            case 'c':
                printf("%-12s", "COUNT");
                fprintf(fptr, "%-12s", "COUNT");
                break;
            
            case 'h':
                printf("%-12s", "HEAP");
                fprintf(fptr, "%-12s", "HEAP");
                break;

            case 'i':
                printf("%-12s", "INSERTION");
                fprintf(fptr, "%-12s", "INSERTION");
                break;

            case 'm':
                printf("%-12s", "MERGE");
                fprintf(fptr, "%-12s", "MERGE");
                break;

            case 's':
                printf("%-12s", "SELECTION");
                fprintf(fptr, "%-12s", "SELECTION");
                break;
            }

                                                                                                                                                                                                                                                           
        printf("%-11.5f", as[i].avg_t/quant);
        printf("%-12lld", as[i].avg_cmp/quant);
        printf("%-11lld", as[i].avg_mov/quant);
        printf("%-11lld", as[i].avg_mem/quant);
        printf("%-11lld", as[i].avg_rec/quant);
        printf("%-13d\n", as[i].avg_max_depth/quant);
                                                                                                                                                                                                                                                          
        fprintf(fptr, "%-11.5f", as[i].avg_t/quant);
        fprintf(fptr, "%-12lld", as[i].avg_cmp/quant);
        fprintf(fptr, "%-11lld", as[i].avg_mov/quant);
        fprintf(fptr, "%-11lld", as[i].avg_mem/quant);
        fprintf(fptr, "%-11lld", as[i].avg_rec/quant);
        fprintf(fptr, "%-13d\n", as[i].avg_max_depth/quant);
    }


    //Fechamento do arquivo
    fclose(fptr);
}
