#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <ctype.h>
#include "shell.h"
#include <fcntl.h>

/*
 * Arguments: array of commandline argument strings
 * Checks if command is special shell commands, and executes it if true.
 */
void shell_exe( char ** cmd ){
    if (!strcmp(cmd[0], "exit")) {
        int status;
        exit(status);
    } else if (!strcmp(cmd[0], "cd")) {
        if (cmd[1] == NULL || !strcmp(cmd[1], "~")){
            chdir(getenv("HOME"));
        } else{
            chdir(cmd[1]);
        }
    }
}

/*
 * Arguments: command line array
 * Handles Redirection
 */
void redir( char ** cmd ){
    int stdout_f = dup(STDOUT_FILENO);
    int stdin_f = dup(STDIN_FILENO);
    int stdout_backup = stdout_f;
    int stdin_backup = stdin_f;
    int mode = O_WRONLY | O_CREAT; 

    int i = 0;
    while (cmd[i]){
        if (!strcmp(cmd[i], ">")){
            mode |= O_TRUNC;
            new_fd = open()
            dup2()
        } 
    }
}
