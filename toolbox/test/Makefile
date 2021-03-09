V= valgrind
CFLAGS= -std=c99 -g -O0
GFLAGS= -tui
WFLAGS= -Wall -Wconversion -Werror
VFLAGS= --leak-check=full --track-origins=yes --show-reachable=yes


interfaz: ../code/interfaz.c
	$(CC) test_interfaz.c ../code/interfaz.c $(CFLAGS) $(WFLAGS) -o interfaz
interfaz_exe: inetrfaz test_interfaz.c
	$(V) $(VFLAGS) ./inetrfaz