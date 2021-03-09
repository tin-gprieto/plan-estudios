V= valgrind
GDB= gdb
CFLAGS= -std=c99 -g -O0
GFLAGS= -tui
WFLAGS= -Wall -Wconversion -Werror
VFLAGS= --leak-check=full --track-origins=yes --show-reachable=yes

CFILE=code/main.c
LIB_FILE= toolbox/tools.c code/materias.c
EXE= carrera.exe

TEST_FILE=test/pruebas_unitarias.c
TEST_EXTRA_FILE=test/extra.c

TEST_LIB= toolbox/tools.c code/materias.c
TEST_EXE= test/prueba.exe
TEST_EXTRA_EXE= test/extra.exe

ARCHIVOS= txt/ing_informatica_1886.csv

$(EXE): $(CFILE) $(LIB_FILE)
	clear
	$(CC) $(CFILE) $(LIB_FILE) $(CFLAGS) $(WFLAGS) -o $(EXE)
$(TEST_EXE): $(TEST_FILE) $(TEST_LIB) 
	clear
	$(CC) $(TEST_FILE) $(TEST_LIB) $(CFLAGS) $(WFLAGS) -o $(TEST_EXE)
test: $(TEST_EXE)
	clear
	$(V) $(VFLAGS) ./$(TEST_EXE)
test_extra:
	$(CC) $(TEST_EXTRA_FILE) $(TEST_LIB) $(CFLAGS) $(WFLAGS) -o $(TEST_EXTRA_EXE)
	clear
	$(V) $(VFLAGS) ./$(TEST_EXE)
exe: $(EXE)
	clear
	./$(EXE) $(ARCHIVOS) 
help:$(EXE)
	clear
	./$(EXE) --help
csv: $(EXE)
	clear
	./$(EXE) --csv
gdb: $(TEST_EXE)
	clear
	$(GDB) $(TEST_EXE) $(GFLAGS)
gdbgui: $(TEST_EXE)
	clear
	gdbgui $(TEST_EXE) 
