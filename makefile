all : cshell.c shell.h
	gcc -o exec cshell.c 

run : all
	./exec

clean : shell
	rm exec
