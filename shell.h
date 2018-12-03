/*
 * Responsible for receiving user input and parsing into an execvp array.
 * Returns array of strings of command line arguments.
 */
char ** parse(char * buffer, char * delim);
/*
 * Arguments: array of commandline argument strings
 * Checks if command is special shell commands, and executes it if true.
 */
void shell_exe( char ** cmd );
/*
 * Arguments: array of commandline argument strings
 * Forks a child which executes command
 */
void exe( char ** cmd );
/*
 * Removes extra whitespace from each string in the command line array
 */
char ** rm_space( char ** cmd );
/*
 * Arguments: command line array
 * Handles Redirection
 */
char ** redir( char ** cmd );
/*
 * Arguments: command line array
 * Handles piping
 */
void pipe_function( char ** cmd );
