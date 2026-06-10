#include "utils.h"

//função date_time_stamp: retorna a data e horário da execução do código para nomeação do arquivo csv de entrada.
char *datetime_stamp(){
    time_t raw_time = time(NULL);
    struct tm *time_info = localtime(&raw_time);
    
    char *buffer = (char *)malloc(80*sizeof(char));
    strftime(buffer, 80, "%Y_%m_%d_%H_%M_%S", time_info);

    return buffer;
}

//função char_to_int: converte o caractere de escolha de método de ordenação para um número inteiro.
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

//função int_to_chat: converte o inteiro de escolha do método de ordenação para um caractere.
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

//função random_int: retorna um inteiro randômico em um intervalo escolhido.
int random_int(int min, int max){
    if (min==max){
        return min;
    }

    return ((rand() % (max - min)) + min);
}

//função random_float: retorna um número tipo float randômico entre probabilidades máximas e mínimas.
float random_float(int lower_odds, int upper_odds){
    float odds = (float)(random_int(lower_odds, upper_odds+1)/100.0);
    return odds;
}
