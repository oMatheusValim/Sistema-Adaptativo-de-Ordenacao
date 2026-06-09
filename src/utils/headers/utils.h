#ifndef UTL_H
#define UTL_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>


int random_int(int min, int max);
float random_float(int lower_odds, int upper_odds);

int load_envs(int argc, char *argv[]);
char *datetime_stamp();

int char_to_int(char method);
char int_to_char(int method);


#endif