V = valgrind
CFLAGS = -std=c99 -g -O0
GFLAGS = -tui
WFLAGS = -Wall -Wconversion -Werror
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

TOOLS = code/tools.c

test/interfaz.exe: code/interfaz.c $(TOOLS)
	$(CC) test/test_interfaz.c code/interfaz.c $(TOOLS) $(CFLAGS) $(WFLAGS) -o test/interfaz.exe

exe interfaz: test/interfaz.exe test/test_interfaz.c
	$(V) $(VFLAGS) ./test/interfaz.exe