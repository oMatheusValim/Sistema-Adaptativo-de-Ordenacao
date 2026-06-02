APPS = ./apps
BIN = ./bin
INCLUDE = ./include
OBJ = ./obj
SRC = ./src


all:
	gcc -c $(SRC)/io.c  -I $(INCLUDE)/ -o $(OBJ)/io.o
	gcc -c $(SRC)/entry_analysis.c  -I $(INCLUDE)/ -o $(OBJ)/entry_analysis.o
	gcc -c $(SRC)/algoritmos.c -I $(INCLUDE)/ -o $(OBJ)/algoritmos.o
	gcc -c $(SRC)/input_generator.c  -I $(INCLUDE)/ -o $(OBJ)/input_generator.o
	gcc -c $(APPS)/main.c $(OBJ)/io.o $(OBJ)/entry_analysis.o $(OBJ)/algoritmos.o $(OBJ)/input_generator.o -I $(INCLUDE) -o $(BIN)/run.exe -lm
	
run:
	$(BIN)/run.exe

val:
	gcc -c $(SRC)/io.c  -I $(INCLUDE)/ -o $(OBJ)/io.o
	gcc -c $(SRC)/entry_analysis.c  -I $(INCLUDE)/ -o $(OBJ)/entry_analysis.o
	gcc -c $(SRC)/algoritmos.c -I $(INCLUDE)/ -o $(OBJ)/algoritmos.o
	gcc -c $(SRC)/input_generator.c  -I $(INCLUDE)/ -o $(OBJ)/input_generator.o
	gcc -g -O0 $(APPS)/main.c $(OBJ)/io.o $(OBJ)/entry_analysis.o $(OBJ)/algoritmos.o $(OBJ)/input_generator.o -I $(INCLUDE) -o $(BIN)/run.exe -lm
	
run_val:
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes bin/run.exe

clean:
	rm $(OBJ)/*.o
	rm $(BIN)/*.exe
