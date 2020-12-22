CC= gcc
V= valgrind
GDB= gdb
CFLAGS= -std=c99 -g -O0
GFLAGS= -tui
WFLAGS= -Wall -Wconversion -Werror
VFLAGS= --leak-check=full --track-origins=yes --show-reachable=yes

CFILE=code/main.c
LIB_FILE=code/materias.c
EXE= carrera

TOOLS = code/tools.c

TEST_FILE=test/pruebas_unitarias.c
TEST_LIB= test/test.c code/materias.c
TEST_EXE= test/prueba

ARCHIVOS= txt/materias.csv

$(EXE): $(CFILE) $(LIB_FILE)
	$(CC) $(CFILE) $(LIB_FILE) $(TOOLS) $(CFLAGS) $(WFLAGS) -o $(EXE)
$(TEST_EXE): $(TEST_FILE) $(TEST_LIB) 
	$(CC) $(TEST_FILE) $(TEST_LIB) $(CFLAGS) $(WFLAGS) -o $(TEST_EXE)
val_test: $(TEST_EXE)
	$(V) $(VFLAGS) ./$(TEST_EXE) $(ARCHIVOS)
exe: $(EXE)
	./$(EXE) $(ARCHIVOS) 
help:$(EXE)
	./$(EXE) --help
csv: $(EXE)
	./$(EXE) --csv
gdb: $(EXE)
	$(GDB) $(EXE) $(ARCHIVOS) $(GFLAGS)
materias.o: 
	$(CC) materias.c $(CFLAGS) $(WFLAGS) -o materias.o
