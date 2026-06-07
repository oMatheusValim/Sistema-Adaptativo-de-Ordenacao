#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "execution_analysis.h"

// A função recebe o array com os dados dos 5 métodos
void statistics(output_analysis oa[]) {

    // Abre o arquivo .txt para salvar a tabela
    FILE *arquivo = fopen("tabela_resultados.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo tabela_resultados.txt!\n");
        return;
    }

    printf("======================================== DADOS DE EXECUÇÃO ========================================\n\n");
    printf("            count   avg(t)   avg(n)   avg(t/n)   avg(amp)   avg(t/amp)   avg(distr)   avg(t/distr)\n");

    //o que vai pro txt é o fprintf
    fprintf(arquivo, "======================================== DADOS DE EXECUÇÃO ========================================\n\n");
    fprintf(arquivo, "            count   avg(t)   avg(n)   avg(t/n)   avg(amp)   avg(t/amp)   avg(distr)   avg(t/distr)\n");


    // ================= COUNT =================
    printf("%-12s", "COUNT");
    printf("%-8d", oa[0].count);                                                                                                                                                                                                                                                                                         
    printf("%-9.2f", oa[0].t_sum/oa[0].count);
    printf("%-9d", oa[0].n_sum/oa[0].count);
    printf("%-11.3f", oa[0].t_per_n_sum/oa[0].count);
    printf("%-11d", oa[0].amp_sum/oa[0].count);
    printf("%-16.3f", oa[0].t_per_amp_sum/oa[0].count);
    printf("%-13.3f", oa[0].distr_sum/oa[0].count);
    printf("%-13.3f\n", oa[0].t_per_distr_sum/oa[0].count);

    fprintf(arquivo, "%-12s", "COUNT");
    fprintf(arquivo, "%-8d", oa[0].count);
    fprintf(arquivo, "%-9.2f", oa[0].t_sum/oa[0].count);
    fprintf(arquivo, "%-9d", oa[0].n_sum/oa[0].count);
    fprintf(arquivo, "%-11.3f", oa[0].t_per_n_sum/oa[0].count);
    fprintf(arquivo, "%-11d", oa[0].amp_sum/oa[0].count);
    fprintf(arquivo, "%-16.3f", oa[0].t_per_amp_sum/oa[0].count);
    fprintf(arquivo, "%-13.3f", oa[0].distr_sum/oa[0].count);
    fprintf(arquivo, "%-13.3f\n", oa[0].t_per_distr_sum/oa[0].count);


    // ================= HEAP =================
    printf("%-12s", "HEAP");
    printf("%-8d", oa[1].count);                                                                                                                                                                                                                                                                                         
    printf("%-9.2f", oa[1].t_sum/oa[1].count);
    printf("%-9d", oa[1].n_sum/oa[1].count);
    printf("%-11.3f", oa[1].t_per_n_sum/oa[1].count);
    printf("%-11d", oa[1].amp_sum/oa[1].count);
    printf("%-16.3f", oa[1].t_per_amp_sum/oa[1].count);
    printf("%-13.3f", oa[1].distr_sum/oa[1].count);
    printf("%-13.3f\n", oa[1].t_per_distr_sum/oa[1].count);

    fprintf(arquivo, "%-12s", "HEAP");
    fprintf(arquivo, "%-8d", oa[1].count);
    fprintf(arquivo, "%-9.2f", oa[1].t_sum/oa[1].count);
    fprintf(arquivo, "%-9d", oa[1].n_sum/oa[1].count);
    fprintf(arquivo, "%-11.3f", oa[1].t_per_n_sum/oa[1].count);
    fprintf(arquivo, "%-11d", oa[1].amp_sum/oa[1].count);
    fprintf(arquivo, "%-16.3f", oa[1].t_per_amp_sum/oa[1].count);
    fprintf(arquivo, "%-13.3f", oa[1].distr_sum/oa[1].count);
    fprintf(arquivo, "%-13.3f\n", oa[1].t_per_distr_sum/oa[1].count);


    // ================= INSERTION =================
    printf("%-12s", "INSERTION");
    printf("%-8d", oa[2].count);                                                                                                                                                                                                                                                                                         
    printf("%-9.2f", oa[2].t_sum/oa[2].count);
    printf("%-9d", oa[2].n_sum/oa[2].count);
    printf("%-11.3f", oa[2].t_per_n_sum/oa[2].count);
    printf("%-11d", oa[2].amp_sum/oa[2].count);
    printf("%-16.3f", oa[2].t_per_amp_sum/oa[2].count);
    printf("%-13.3f", oa[2].distr_sum/oa[2].count);
    printf("%-13.3f\n", oa[2].t_per_distr_sum/oa[2].count);

    fprintf(arquivo, "%-12s", "INSERTION");
    fprintf(arquivo, "%-8d", oa[2].count);
    fprintf(arquivo, "%-9.2f", oa[2].t_sum/oa[2].count);
    fprintf(arquivo, "%-9d", oa[2].n_sum/oa[2].count);
    fprintf(arquivo, "%-11.3f", oa[2].t_per_n_sum/oa[2].count);
    fprintf(arquivo, "%-11d", oa[2].amp_sum/oa[2].count);
    fprintf(arquivo, "%-16.3f", oa[2].t_per_amp_sum/oa[2].count);
    fprintf(arquivo, "%-13.3f", oa[2].distr_sum/oa[2].count);
    fprintf(arquivo, "%-13.3f\n", oa[2].t_per_distr_sum/oa[2].count);


    // ================= MERGE =================
    printf("%-12s", "MERGE");
    printf("%-8d", oa[3].count);                                                                                                                                                                                                                                                                                         
    printf("%-9.2f", oa[3].t_sum/oa[3].count);
    printf("%-9d", oa[3].n_sum/oa[3].count);
    printf("%-11.3f", oa[3].t_per_n_sum/oa[3].count);
    printf("%-11d", oa[3].amp_sum/oa[3].count);
    printf("%-16.3f", oa[3].t_per_amp_sum/oa[3].count);
    printf("%-13.3f", oa[3].distr_sum/oa[3].count);
    printf("%-13.3f\n", oa[3].t_per_distr_sum/oa[3].count);

    fprintf(arquivo, "%-12s", "MERGE");
    fprintf(arquivo, "%-8d", oa[3].count);
    fprintf(arquivo, "%-9.2f", oa[3].t_sum/oa[3].count);
    fprintf(arquivo, "%-9d", oa[3].n_sum/oa[3].count);
    fprintf(arquivo, "%-11.3f", oa[3].t_per_n_sum/oa[3].count);
    fprintf(arquivo, "%-11d", oa[3].amp_sum/oa[3].count);
    fprintf(arquivo, "%-16.3f", oa[3].t_per_amp_sum/oa[3].count);
    fprintf(arquivo, "%-13.3f", oa[3].distr_sum/oa[3].count);
    fprintf(arquivo, "%-13.3f\n", oa[3].t_per_distr_sum/oa[3].count);


    // ================= SELECTION =================
    printf("%-12s", "SELECTION");
    printf("%-8d", oa[4].count);                                                                                                                                                                                                                                                                                         
    printf("%-9.2f", oa[4].t_sum/oa[4].count);
    printf("%-9d", oa[4].n_sum/oa[4].count);
    printf("%-11.3f", oa[4].t_per_n_sum/oa[4].count);
    printf("%-11d", oa[4].amp_sum/oa[4].count);
    printf("%-16.3f", oa[4].t_per_amp_sum/oa[4].count);
    printf("%-13.3f", oa[4].distr_sum/oa[4].count);
    printf("%-13.3f\n", oa[4].t_per_distr_sum/oa[4].count);

    fprintf(arquivo, "%-12s", "SELECTION");
    fprintf(arquivo, "%-8d", oa[4].count);
    fprintf(arquivo, "%-9.2f", oa[4].t_sum/oa[4].count);
    fprintf(arquivo, "%-9d", oa[4].n_sum/oa[4].count);
    fprintf(arquivo, "%-11.3f", oa[4].t_per_n_sum/oa[4].count);
    fprintf(arquivo, "%-11d", oa[4].amp_sum/oa[4].count);
    fprintf(arquivo, "%-16.3f", oa[4].t_per_amp_sum/oa[4].count);
    fprintf(arquivo, "%-13.3f", oa[4].distr_sum/oa[4].count);
    fprintf(arquivo, "%-13.3f\n", oa[4].t_per_distr_sum/oa[4].count);


    //fechamento do arquivo
    fclose(arquivo);
    printf("\n[Sucesso] Tabela exportada para 'tabela_resultados.txt'!\n");
}