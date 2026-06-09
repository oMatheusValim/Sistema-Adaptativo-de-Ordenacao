APPS = ./apps
BIN = ./bin
INCLUDE = ./include
OBJ = ./obj
SRC = ./src

UTL = /utils
IO = /io
EA = /entry_analysis
ALG = /algoritmos
IG = /input_generator
ADP = /adaptive
MA = /method_analysis
CFG = /config

all:
	gcc -c $(SRC)$(UTL).c  -I $(INCLUDE)/ -o $(OBJ)$(UTL).o
	gcc -c $(SRC)$(IO).c  -I $(INCLUDE)/ -o $(OBJ)$(IO).o
	gcc -c $(SRC)$(EA).c  -I $(INCLUDE)/ -o $(OBJ)$(EA).o
	gcc -c $(SRC)$(ALG).c  -I $(INCLUDE)/ -o $(OBJ)$(ALG).o
	gcc -c $(SRC)$(IG).c  -I $(INCLUDE)/ -o $(OBJ)$(IG).o
	gcc -c $(SRC)$(ADP).c  -I $(INCLUDE)/ -o $(OBJ)$(ADP).o
	gcc -c $(SRC)$(MA).c  -I $(INCLUDE)/ -o $(OBJ)$(MA).o
	gcc -c $(SRC)$(CFG).c  -I $(INCLUDE)/ -o $(OBJ)$(CFG).o
	gcc $(APPS)/main.c $(OBJ)$(UTL).o $(OBJ)$(IO).o $(OBJ)$(EA).o $(OBJ)$(ALG).o $(OBJ)$(IG).o $(OBJ)$(ADP).o $(OBJ)$(MA).o $(OBJ)$(CFG).o -I $(INCLUDE) -o $(BIN)/run.exe -lm


run:
	$(BIN)/run.exe


val:
	gcc -c $(SRC)$(UTL).c  -I $(INCLUDE)/ -o $(OBJ)$(UTL).o
	gcc -c $(SRC)$(IO).c  -I $(INCLUDE)/ -o $(OBJ)$(IO).o
	gcc -c $(SRC)$(EA).c  -I $(INCLUDE)/ -o $(OBJ)$(EA).o
	gcc -c $(SRC)$(ALG).c  -I $(INCLUDE)/ -o $(OBJ)$(ALG).o
	gcc -c $(SRC)$(IG).c  -I $(INCLUDE)/ -o $(OBJ)$(IG).o
	gcc -c $(SRC)$(ADP).c  -I $(INCLUDE)/ -o $(OBJ)$(ADP).o
	gcc -c $(SRC)$(MA).c  -I $(INCLUDE)/ -o $(OBJ)$(MA).o
	gcc -c $(SRC)$(CFG).c  -I $(INCLUDE)/ -o $(OBJ)$(CFG).o
	gcc -g -O0 $(APPS)/main.c $(OBJ)$(UTL).o $(OBJ)$(IO).o $(OBJ)$(EA).o $(OBJ)$(ALG).o $(OBJ)$(IG).o $(OBJ)$(ADP).o $(OBJ)$(MA).o $(OBJ)$(CFG).o -I $(INCLUDE) -o $(BIN)/run.exe -lm

run_val:
	valgrind -s --log-file="val_report.txt" --leak-check=full --show-leak-kinds=all --track-origins=yes bin/run.exe

clean:
	rm $(OBJ)/*.o
	rm $(BIN)/*.exe
