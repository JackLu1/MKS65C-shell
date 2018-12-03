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
            cmd = rm_space(parse(cmd_list[i++], " "));
            shell_exe(cmd);
            exe( cmd );
        }
    }
    return 0;
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
        cmd = redir(cmd);
        int i = 0;
        //while(cmd[i]){
        //    if (strchr(cmd[i], '|')){
        //        pipe_function( cmd );
        //    }
        //    i++;
        //}
        execvp(cmd[0], cmd);
        exit(status);
    }
}

