#include <stdio.h>
#include <stdlib.h>

int **create_arrs(int quant, int max_size, int max_num);
int random_int(int min, int max);
float chance(int lower_odds, int upper_odds);
int *random_arr(int max_num, int max_size);
int *random_adversarial_arr(int max_num, int max_size);