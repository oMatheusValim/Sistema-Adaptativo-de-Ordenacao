# Definir config.txt padrão
cat << EOF > ./experiments/config.txt
# Quais algoritmos de sorting devem ser utilizados/comparados
A=1
C=1
H=1
I=1
M=1
S=1

# Detalhes da entrada
CSV_FILE=
QUANT=1500
MAX_SIZE=4000
MAX_NUM=5000

NEGATIVE=10

ADV=35
SRT=8
R_SRT=8
EQUAL=4

SEED=

# Detalhes da saída
VERBOSE=1
OUT_TXT=1
EOF

make
make run