all : cshell.c shell.h
	gcc -o exec cshell.c parse.c default.c

run : all
	./exec

clean : shell
	rm exec
