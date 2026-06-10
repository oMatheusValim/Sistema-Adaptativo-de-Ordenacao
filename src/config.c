#include "utils.h"
#include "config.h"

#define CONFIG_FILE "config.txt"
#define MAX_LINE_LEN 100
 
// função trim: Remove whitespace da string
static char *trim(char *s) {
    while (*s == ' ' || *s == '\t') s++;
    char *end = s + strlen(s) - 1;
    while (end > s && (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n'))
        *end-- = '\0';
    return s;
}
 

//função config_load_file: Carrega as constantes do ".env"
void config_load_file() {
    FILE *fptr = fopen(CONFIG_FILE, "r");

    if (fptr == NULL) {
        printf("Erro! Não foi possível abrir o arquivo de configuração!");
        return;
    }
 
    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), fptr)) {
        char *p = trim(line);

        // Linha vazia ou comentário
        if (*p == '\0' || *p == '#')
            continue;
 
        char *eq = strchr(p, '=');

        // Linha não contém =
        if (eq == NULL) continue;
 
        *eq = '\0';
        char *key = trim(p);
        char *val = trim(eq + 1);
 
        setenv(key, val, 0);
    }
    fclose(fptr);
}
 

//função config_load_ars: Carrega as constantes das linhas de comando
void config_load_args(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "--", 2) != 0) continue;
 
        char buf[MAX_LINE_LEN];
        strncpy(buf, argv[i] + 2, sizeof(buf) - 1);
        char *eq = strchr(buf, '=');
 
        char *key = NULL, *val = NULL;
 
        if (eq) {
            *eq = '\0';
            key = trim(buf);
            val = trim(eq + 1);
        } 
        
        else if (i + 1 < argc && strncmp(argv[i + 1], "--", 2) != 0) {
            key = trim(buf);
            val = trim(argv[i + 1]);
            i++;
        } 
        
        else {
            continue;
        } 
    
        setenv(key, val, 1);


    }
}
 
 
// função load_envs: obtém os parametros definidos no ".env"
int load_envs(int argc, char *argv[]){

    config_load_file();
    config_load_args(argc, argv);

    int algs_count = 0;

    algs_count += atoi(getenv("A") ? getenv("A") : "0");
    algs_count += atoi(getenv("C") ? getenv("C") : "0");
    algs_count += atoi(getenv("H") ? getenv("H") : "0");
    algs_count += atoi(getenv("I") ? getenv("I") : "0");
    algs_count += atoi(getenv("M") ? getenv("M") : "0");
    algs_count += atoi(getenv("S") ? getenv("S") : "0");

    if (algs_count == 0){
        printf("Erro! É necessário incluir pelo menos um algoritmo de sorting ou o método adaptativo!\n ");
        return -1;
    }

    return algs_count;
}


// função convert_env: verifica se as contantes estão definidas corretamente e as modifica para inteiros
int convert_env(char* key, int lower, int upper){

    char *key_c = (getenv(key));

    if (key_c == NULL){
        printf("Erro! A variável %s não está definida! Inclua-a em uma linha de comando ou no arquivo de configuração!\n", key_c);
        return -1;
    }
        
    int key_i = atoi(key_c);

    if (key_i < lower || key_i > upper){
        printf("Erro! A variável %s deve estar entre %d e %d!\n", key_c, lower, upper);
        return -1;
    }

    return key_i;
}