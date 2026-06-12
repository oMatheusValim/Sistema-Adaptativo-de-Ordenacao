CC = gcc

CFLAGS = -Wall -I./headers
LDFLAGS = -lm

HEADERS = ./headers
SRC = ./src
UTILS = ./src/utils
OBJ = ./obj

TARGET = $(OBJ)/run.exe

UTILS_OBJS = \
	$(OBJ)/utils.o \
	$(OBJ)/config.o \
	$(OBJ)/io.o \
	$(OBJ)/input_generator.o

SRC_OBJS = \
	$(OBJ)/entry_analysis.o \
	$(OBJ)/algoritmos.o \
	$(OBJ)/adaptive.o \
	$(OBJ)/method_compare.o

MAIN_OBJ = $(OBJ)/main.o

OBJS = $(UTILS_OBJS) $(SRC_OBJS)

.PHONY: all run clean val run_val

all: $(TARGET)

$(TARGET): $(MAIN_OBJ) $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

# main.c

$(OBJ)/main.o: $(SRC)/main.c
	$(CC) $(CFLAGS) -c $< -o $@

# Arquivos em src/

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Arquivos em src/utils/

$(OBJ)/%.o: $(UTILS)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

val: CFLAGS += -g -O0
val: clean all

run_val: $(TARGET)
	valgrind \
		-s \
		--log-file="results/valgrind_report.txt" \
		--leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		./$(TARGET)

clean:
	rm -f $(OBJ)/*.o $(OBJ)/*.d $(TARGET)

-include $(OBJS:.o=.d) $(MAIN_OBJ:.o=.d)