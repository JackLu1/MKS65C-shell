#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include "shell.h"

int main(){

    int status;
    char ** cmd;
    while(1){
        printf("$ ");
        cmd = parse();
        shell_exe(cmd);
        exe( cmd );
    }
    return 0;
}

char ** parse(){

    char * buffer = calloc(1,10000);
    char ** args = calloc(1, 10000);
    fgets(buffer, 10000, stdin);

    //remove terminating newline
    buffer[strcspn(buffer, "\n")] = 0;

    int i = 0;
    while (args[i++] = strsep(&buffer, " "));
    free(buffer);
    return args;
}

void shell_exe( char ** cmd ){
    if (!strcmp(cmd[0], "exit")) {
        int status;
        exit(status);
    } else if (!strcmp(cmd[0], "cd")) {
        chdir(cmd[1]);
    }
}

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































