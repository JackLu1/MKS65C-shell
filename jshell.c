#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include "shell.h"

int main(){

    int status;
    char *buffer = calloc(1,1000);
    char ** cmd;
    //while(1){
        printf("Enter command: ");
        fgets(buffer, 1000, stdin);
        //scanf("%s", buffer);
        
        printf("buffer = %s\n", buffer);
        cmd = parse(buffer);

        for (char ** a = cmd; *a; a++){
            printf("a = %s\n", *a); 
        }
        execvp(cmd[0], cmd);
        //printf("\ncmd: %s\n", buffer);
        //cmd = wait(&status);
    //}
    return 0;
}

char ** parse( char * line ){
    //points to pointers
    char ** args = calloc(50, 100);
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
