#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include "shell.h"

/*
 * Runs infinite while loop until terminated
 */
int main(){

    char ** cmd_list;
    char ** cmd;
    char * cwd = malloc(100);
    char * usr = getlogin();
    char * delim = malloc(2);
    while(1){
        cwd = getcwd(cwd, 100);
        printf("[%s] [%s] $ ", usr, cwd);
        char * buffer = calloc(1,1000);
        fgets(buffer, 1000, stdin);
    
        strcpy(delim, ";");
        cmd_list = parse(buffer, delim);
        strcpy(delim, " ");
        int i = 0;
        while( cmd_list[i] ) {
            cmd = parse(cmd_list[i++], " ");
            shell_exe(cmd);
            exe( cmd );
        }
    }
    return 0;
}

/*
 * Responsible for receiving user input and parsing into an execvp array.
 * Returns array of strings of command line arguments.
 */
char ** parse( char * buffer, char * delim ){

    char ** args = calloc(1, 1000);

    //remove terminating newline
    buffer[strcspn(buffer, "\n")] = 0;

    int i = 0;
    while (args[i++] = strsep(&buffer, delim));
    free(buffer);
    return args;
}

/*
 * Arguments: array of commandline argument strings
 * Checks if command is special shell commands, and executes it if true.
 */
void shell_exe( char ** cmd ){
    if (!strcmp(cmd[0], "exit")) {
        int status;
        exit(status);
    } else if (!strcmp(cmd[0], "cd")) {
        chdir(cmd[1]);
    }
}

/*
 * Arguments: array of commandline argument strings
 * Forks a child which executes command
 */
void exe( char ** cmd ){
    int f = fork();
    int status;
    if (f){
        // parent
        wait(&status);
        perror("status");
    } else {
        //child
        execvp(cmd[0], cmd);
        exit(status);
    }
}


