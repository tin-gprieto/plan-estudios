CC= gcc
V= valgrind
GDB= gdb
CFLAGS= -std=c99 -g -O0
GFLAGS= -tui
ARCHIVOS= txt/materias.csv
WFLAGS= -Wall -Wconversion -Werror
VFLAGS= --leak-check=full --track-origins=yes --show-reachable=yes

carrera: code/main.c code/materias.c
	$(CC) code/main.c code/materias.c $(CFLAGS) $(WFLAGS) -o carrera
test: test/pruebas_unitarias.c code/materias.c
	$(CC) test/pruebas_unitarias.c code/materias.c $(CFLAGS) $(WFLAGS) -o test/prueba
	./test/prueba
val_test: test
	$(V) $(VFLAGS) ./test/prueba $(ARCHIVOS)
exe: carrera
	./carrera $(ARCHIVOS) 
help: carrera
	./carrera --help
csv: carrera
	./carrera --csv
val: carrera
	$(V) $(VFLAGS) ./carrera $(ARCHIVOS) 
gdb: carrera
	$(GDB) carrera $(ARCHIVOS) $(GFLAGS)
materias.o: 
	$(CC) materias.c $(CFLAGS) $(WFLAGS) -o materias.o
