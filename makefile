all : sea_shell.c shell.h
	gcc -o shell sea_shell.c 

run : all
	./shell

clean : shell
	rm shell
