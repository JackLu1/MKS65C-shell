// parse into execvp format
char ** parse();
// checks and handles shell commands
void shell_exe( char ** cmd );
// executes non-shell commands
void exe( char ** cmd );
