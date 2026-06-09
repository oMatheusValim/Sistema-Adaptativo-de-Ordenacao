#include "headers/utils.h"

char *datetime_stamp(){
    time_t raw_time = time(NULL);
    struct tm *time_info = localtime(&raw_time);
    
    char *buffer = (char *)malloc(80*sizeof(char));
    strftime(buffer, 80, "%Y_%m_%d_%H_%M_%S", time_info);

    return buffer;
}

int char_to_int(char method){
    switch (method){
        case 'c':
            return 0;
        
        case 'h':
            return 1;

        case 'i':
            return 2;

        case 'm':
            return 3;

        case 's':
            return 4;

        default:
            printf("ERRO! Método %c é inválido!\n", method);
            return -1;
    }
}

char int_to_char(int method){
    switch (method){
        case 0:
            return 'c';
        
        case 1:
            return 'h';

        case 2:
            return 'i';

        case 3:
            return 'm';

        case 4:
            return 's';

        default:
            printf("ERRO! Método %d é inválido!\n", method);
            return 'z';
    }
}

int random_int(int min, int max){
    if (min==max){
        return min;
    }

    return ((rand() % (max - min)) + min);
}

float random_float(int lower_odds, int upper_odds){
    float odds = (float)(random_int(lower_odds, upper_odds+1)/100.0);
    return odds;
}
