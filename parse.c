#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <ctype.h>
#include "shell.h"

/*
 * Responsible for receiving user input and parsing into an execvp array.
 * Returns array of strings of command line arguments delimited by the delim parameter.
 */
char ** parse( char * buffer, char * delim ){

    char ** args = calloc(1, 1000);

    //remove terminating newline
    buffer[strcspn(buffer, "\n")] = 0;

    int i = 0;
    char * token;
    while (token = strsep(&buffer, delim)){
        // Deals with multiple space separation
        if ( strcmp(token, "") ){
            args[i++] = token;
        }
    }

    free(buffer);
    return args;
}

char ** rm_space( char ** cmd ){
    int i = 0;
    while ( cmd[i] ){

        char * c = cmd[i];
        while( isspace(*c) ){
            c++;
        }
        cmd[i] = c;
        c = cmd[i] + strlen(cmd[i]) -1;
        while( isspace(*c) && c > cmd[i] ){
            c--;
        }
        c++;
        int size = c - cmd[i];
        char * temp = malloc(size * 4);
        strncpy(temp, cmd[i], size);
        cmd[i] = temp;
        i++;
    }

    return cmd;
}
