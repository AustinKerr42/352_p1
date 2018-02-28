HEADERS = shell.h

default: program

shell.o: shell.c $(HEADERS)
	gcc -c shell.c -o shell.o

program: shell.o
	gcc shell.o -o shell

clean:
	-rm -f shell.o
	-rm -f shell
