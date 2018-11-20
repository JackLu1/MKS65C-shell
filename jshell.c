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
    char *buffer = calloc(1,1000);
    while(1){
        printf("Enter command: ");
        //fgets(buffer, 1000, stdin);
        scanf("%s", buffer);
        
        printf("buffer = %s\n", buffer);
        cmd = execute(buffer);

        //for (char ** a = cmd; *a; a++){
        //    printf("a = %s\n", *a); 
        //}
        execvp(cmd[0], cmd);
        //printf("\ncmd: %s\n", buffer);
        //cmd = wait(&status);
    }
    return 0;
}

char ** execute( char * line ){
    char ** args = malloc(1000);
    int i = 0;
    while (args[i++] = strsep(&line, " "));
    return args;
}

//int main(){
//    char line[100] = "ls -l -a --color";
//    char ** args = parse_args(line);
//
//    // for (char ** a = args; *a; a++){
//    //     printf("%s\n", *a); 
//    // }
//    execvp(args[0], args);
//
//    return 0;
//}
