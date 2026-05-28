APPS = ./apps
BIN = ./bin
INCLUDE = ./include
OBJ = ./obj
SRC = ./src


all:
	gcc -c $(SRC)/io.c  -I $(INCLUDE)/ -o $(OBJ)/io.o
	gcc -c $(SRC)/entry_analysis.c  -I $(INCLUDE)/ -o $(OBJ)/entry_analysis.o
	gcc -c $(SRC)/input_generator.c  -I $(INCLUDE)/ -o $(OBJ)/input_generator.o
	gcc -g -O0 $(APPS)/main.c $(OBJ)/io.o $(OBJ)/entry_analysis.o $(OBJ)/input_generator.o -I $(INCLUDE) -o $(BIN)/run.exe -lm

run:
	$(BIN)/progall.exe

clean:
	rm $(OBJ)/*.o
	rm $(BIN)/*.exe
