#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMANDS 10         // The shell will only support max 10 parallel commands
#define MAX_PATHS    10

/* This is function is used to show the shell command prompt */
void show_prompt();

/* Initializes the PATH */
void init_path();

/* Accepts the input given by user and returns back the input string(char *) */
char* accept_input();

/* Parse input  */
int parse_input(char *line, char *cmd[], char *args[]);

/* Only used incase of error while executing a command */
void show_error_and_exit();

/* Only for testing: Used to print the final parsed commandline */
void print_cmd_before_run(char *cmd, char *args);

/* Runs batch mode */
void run_batch_mode(char const *filename);

/* Runs the given command */
void run_command(char* cmd, char *args);

/*MAIN*/
int main(int argc, char const *argv[]);