#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* This is function is used to show the shell command prompt */
void show_prompt();

/* Accepts the input given by user and returns back the input string(char *) */
char* accept_input();

/* Only used incase of error while executing a command */
void show_error_and_exit();

/* Only for testing: Used to print the final parsed commandline */
void print_cmd_before_run(char *string);

/* Runs batch mode */
void run_batch_mode(char const *filename);

/*MAIN*/
int main(int argc, char const *argv[]);