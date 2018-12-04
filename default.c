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
void pipe_function( char * cmd ){
    char * cmd0_temp = strsep(&cmd, "|");
    char * cmd1_temp = strsep(&cmd, "|");
    //printf("cmd0_temp: %s\n", cmd0_temp);
    //printf("cmd1_temp: %s\n", cmd1_temp);

    char ** cmd0 = rm_space(parse(cmd0_temp, " "));
    char ** cmd1 = rm_space(parse(cmd1_temp, " "));
    int i = 0;
    //while (cmd0[i]){
    //    printf("|%s|\n", cmd0[i++]);
    //}
    //i = 0;
    //while (cmd1[i]){
    //    printf("|%s|\n", cmd1[i++]);
    //}

    int pipefd[2];

    int fd0;
    int fd1;
    int stdout_backup = dup(STDOUT_FILENO);
    int stdin_backup = dup(STDIN_FILENO);

    pipe(pipefd);
    if ( !(fd0 = fork()) ){
        //WRITE
        printf("WRITE\n");

        dup2(pipefd[1], STDOUT_FILENO);
        //close unused read end
        close(pipefd[0]);

        execvp(cmd0[0], cmd0);
    } else if ( !(fd1 = fork()) ){
        //READ
        printf("READ\n");

        dup2(pipefd[0], STDIN_FILENO);
        //close unused write end
        close(pipefd[1]);

        execvp(cmd1[0], cmd1);
    } 

    int status;
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid( fd0, &status, 0 );
    perror("status");
    waitpid( fd1, &status, 0 );
    perror("status");
    dup2(stdout_backup, 1);
    dup2(stdin_backup, 0);
    close(stdout_backup);
    close(stdin_backup);
}
