CC= gcc
V= valgrind
GDB= gdb
CFLAGS= -std=c99 -g -O0
GFLAGS= -tui
ARCHIVOS= materias.csv
WFLAGS= -Wall -Wconversion -Werror
VFLAGS= --leak-check=full --track-origins=yes --show-reachable=yes

carrera: main.c materias.c
	$(CC) main.c materias.c $(CFLAGS) $(WFLAGS) -o carrera
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