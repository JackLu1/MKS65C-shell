#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <ctype.h>
#include "shell.h"
#include <fcntl.h>
#define READ 0
#define WRITE 1

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
char ** redir( char ** cmd ){
    char ** input = calloc(1, 10000);
    int mode = O_RDWR | O_CREAT; 

    int i = 0;
    while (cmd[i]){
        if (!strcmp(cmd[i], ">")){

            mode |= O_TRUNC;
            int new_fd = open(cmd[i+1], mode, 0644);
            dup2(new_fd, WRITE);
            cmd[i] = NULL;
            break;
        } 
        if (!strcmp(cmd[i], "<")){

            int new_fd = open(cmd[i+1], mode, 0644);
            dup2(new_fd, READ);
            cmd[i] = NULL;
            break;
        } 
        i++;
    }

    return cmd;
}

/*
 * Arguments: command line array
 * Handles piping
 */
void pipe_function( char ** cmd ){
    //for (int i = 0; cmd[i]; i++){
    //    printf("%s\n", cmd[i]);
    //}
    int i = 0;
    char * cmd0 = strsep(cmd, "|");
    char * cmd1 = strsep(cmd, "|");
    printf("cmd0 = %s\n", cmd0);
    printf("cmd1 = %s\n", cmd1);
    //while (cmd[i]){
    //    if ( !strcmp(cmd[i], "|") ){
    //        int a = 0;
    //        for (; a < i; a++){
    //            printf("READ: %s\n", cmd[a]);
    //            cmd0[a] = cmd[a];
    //        }
    //        i++;
    //        for (; cmd[i]; i++){
    //            printf("WRITE: %s\n", cmd[i]);
    //            cmd1[i] = cmd[i];
    //        }
    //        break;
    //    }
    //    i++;
    //}
    int pipefd[2];
    int fd0;
    int fd1;
    int stdout_backup = dup(WRITE);
    int stdin_backup = dup(READ);
    pipe(pipefd);
    if ( !(fd0 = fork()) ){
        //WRITE
        dup2(pipefd[1], 1);
        printf("WRITE END %s", cmd0);
        char ** cmd0arr = parse(cmd0, " ");
        execvp(cmd0arr[0], cmd0arr);
    } else if ( !(fd1 = fork()) ){
        //READ
        dup2(pipefd[0], 0);
        printf("READ END %s", cmd1);
        char ** cmd1arr = parse(cmd1, " ");
        execvp(cmd1arr[0], cmd1arr);
    }

    close(pipefd[0]);
    close(pipefd[1]);
    dup2(stdout_backup, 1);
    dup2(stdin_backup, 0);
    close(stdout_backup);
    close(stdin_backup);
}
