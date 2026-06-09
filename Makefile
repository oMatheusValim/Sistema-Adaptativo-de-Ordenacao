HEADERS = ./headers
SRC = ./src
UTILS = ./src/utils
OBJ = ./obj

UTL = /utils
IO = /io
EA = /entry_analysis
ALG = /algoritmos
IG = /input_generator
ADP = /adaptive
MC = /method_compare
CFG = /config

all:
	gcc -c $(UTILS)$(UTL).c  -I $(HEADERS)/  -o $(OBJ)$(UTL).o
	gcc -c $(UTILS)$(CFG).c  -I $(HEADERS)/  -o $(OBJ)$(CFG).o
	gcc -c $(UTILS)$(IO).c   -I $(HEADERS)/  -o $(OBJ)$(IO).o
	gcc -c $(UTILS)$(IG).c   -I $(HEADERS)/  -o $(OBJ)$(IG).o
	gcc -c $(SRC)$(EA).c     -I $(HEADERS)/  -o $(OBJ)$(EA).o
	gcc -c $(SRC)$(ALG).c    -I $(HEADERS)/  -o $(OBJ)$(ALG).o
	gcc -c $(SRC)$(ADP).c    -I $(HEADERS)/  -o $(OBJ)$(ADP).o
	gcc -c $(SRC)$(MC).c     -I $(HEADERS)/  -o $(OBJ)$(MC).o
	gcc $(SRC)/main.c $(OBJ)$(UTL).o $(OBJ)$(CFG).o $(OBJ)$(IO).o $(OBJ)$(IG).o $(OBJ)$(EA).o $(OBJ)$(ALG).o $(OBJ)$(ADP).o $(OBJ)$(MC).o -I $(HEADERS) -o $(OBJ)/run.exe -lm


run:
	$(OBJ)/run.exe


val:
	gcc -c $(UTILS)$(UTL).c  -I $(HEADERS)/  -o $(OBJ)$(UTL).o
	gcc -c $(UTILS)$(CFG).c  -I $(HEADERS)/  -o $(OBJ)$(CFG).o
	gcc -c $(UTILS)$(IO).c   -I $(HEADERS)/  -o $(OBJ)$(IO).o
	gcc -c $(UTILS)$(IG).c   -I $(HEADERS)/  -o $(OBJ)$(IG).o
	gcc -c $(SRC)$(EA).c     -I $(HEADERS)/  -o $(OBJ)$(EA).o
	gcc -c $(SRC)$(ALG).c    -I $(HEADERS)/  -o $(OBJ)$(ALG).o
	gcc -c $(SRC)$(ADP).c    -I $(HEADERS)/  -o $(OBJ)$(ADP).o
	gcc -c $(SRC)$(MC).c     -I $(HEADERS)/  -o $(OBJ)$(MC).o
	gcc -g -O0 $(SRC)/main.c $(OBJ)$(UTL).o $(OBJ)$(CFG).o $(OBJ)$(IO).o $(OBJ)$(IG).o $(OBJ)$(EA).o $(OBJ)$(ALG).o $(OBJ)$(ADP).o $(OBJ)$(MC).o -I $(HEADERS) -o $(OBJ)/run.exe -lm

run_val:
	valgrind -s --log-file="results/val_report.txt" --leak-check=full --show-leak-kinds=all --track-origins=yes $(OBJ)//run.exe

clean:
	rm $(OBJ)/*.o
	rm $(BIN)/*.exe
