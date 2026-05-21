APPS = ./apps
BIN = ./bin
INCLUDE = ./include
OBJ = ./obj
SRC = ./src


all:
	gcc -c $(SRC)/io.c  -I $(INCLUDE)/ -o $(OBJ)/io.o
	gcc -c $(SRC)/entry_analysis.c  -I $(INCLUDE)/ -o $(OBJ)/entry_analysis.o
	gcc $(APPS)/main.c $(OBJ)/io.o $(OBJ)/entry_analysis.o -I $(INCLUDE) -o $(BIN)/progall.exe -lm

run:
	$(BIN)/progall.exe

clean:
	rm $(OBJ)/*.o
	rm $(BIN)/*.exe
