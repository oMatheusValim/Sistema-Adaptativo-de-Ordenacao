#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **read_data_input(char* file_name, int quant, int max_num, int max_size);
void write_csv(int **arrs, int quant, char* filename, int max_num);