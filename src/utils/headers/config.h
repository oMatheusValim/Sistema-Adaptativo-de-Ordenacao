#ifndef CFG_H
#define CFG_H

int load_envs(int argc, char *argv[]);
int convert_env(char* key, int def, int lower, int upper);

#endif