## cshell
### by Jack Lu   

## Features:
    - Executes commands.  
    - Shell commands are 'cd' and 'exit'  
        - You can cd into home directory by using 'cd' or 'cd ~'
    - Redirections using < and >  
    - Piping using |

## Attempted
    - Multiple redirects and pipes don't work


get home dir, but cannot append another path to it~~
for example
$ cd ~/systems
will not work


only handles single redirect < >

pipes should be separated by spaces on both sides, or else they won't work

## Files & Function Headers  
### parse.c  - Handles line parsing
```c
/*
 * Responsible for receiving user input and parsing into an execvp array.
 * Accepts string of commands and string delimiter
 * Returns array of strings of command line arguments.
 */
char ** parse(char * buffer, char * delim);
/*
 * Removes extra whitespace from each string in the command line array
 * Takes in string arr of commands, returns modified array
 */
char ** rm_space( char ** cmd );
```

### default.c - shell functionality
```c
/*
 * Arguments: array of commandline argument strings
 * Checks if command is special shell commands, and executes it if true.
 */
void shell_exe( char ** cmd );
/*
 * Arguments: command line array
 * Handles Redirection
 * Returns string array of shell commands
 */
char ** redir( char ** cmd );
/*
 * Arguments: command line array
 * Handles piping
 */
void pipe_function( char ** cmd );

```
### cshell.c - runs and executes command line prompts
```c
/*
 * Arguments: array of commandline argument strings
 * Forks a child which executes command
 */
void exe( char ** cmd );
```
