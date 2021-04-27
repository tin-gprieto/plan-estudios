V= valgrind
GDB= gdb
CFLAGS= -std=c99 -g -O0
GFLAGS= -tui
WFLAGS= -Wall -Wconversion -Werror
VFLAGS= --leak-check=full --track-origins=yes --show-reachable=yes

LIB=code/materias.c toolbox/interfaz/interfaz.h toolbox/tools/tools.h 
TDA=toolbox/TDAs/lista/lista.h toolbox/TDAs/hash/hash.h
TEST_LIB=toolbox/tools/tools.c code/materias.c

EXE= carrera.exe
TEST_EXE= test/prueba.exe

$(EXE): code/main.c $(LIB) $(TDA) 
	clear
	$(CC) code/main.c $(LIB) $(TDA) $(CFLAGS) $(WFLAGS) -o $(EXE)
exe: $(EXE)
	clear
	./$(EXE)
help:$(EXE)
	clear
	./$(EXE) --help
$(TEST_EXE): test/pruebas_unitarias.c $(LIB) $(TDA)
	clear
	$(CC) test/pruebas_unitarias.c $(LIB) $(TDA) $(CFLAGS) $(WFLAGS) -o $(TEST_EXE)
test: $(TEST_EXE)
	clear
	$(V) $(VFLAGS) ./$(TEST_EXE)
gdb: $(TEST_EXE)
	clear
	$(GDB) $(TEST_EXE) $(GFLAGS)
