/*
 * Responsible for receiving user input and parsing into an execvp array.
 * Returns array of strings of command line arguments.
 */
char ** parse(char * buffer, char * delim);
/*
 * Parses input for commands separated by ;
 */
char ** parse_cmd(char * buffer);
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
void redir( char ** cmd );
