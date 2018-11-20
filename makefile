all : jshell.c shell.h
	gcc -o shell jshell.c 

run : all
	./shell

clean : shell
	rm shell
