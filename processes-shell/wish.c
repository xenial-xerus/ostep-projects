#include "wish.h"

void show_prompt()
{
    char message[7] = "wish> ";
    write(STDOUT_FILENO, message, strlen(message));
}

char* accept_input()
{
    char *string;
    int bytes_read;
    size_t line_width = 32;   // Keeping a small value for now, getline function will automatically increase the size as needed

    string = (char *) malloc(line_width * sizeof(char));
    bytes_read = getline(&string, &line_width, stdin);
    if (bytes_read == -1) {
        show_error_and_exit();
    }

    return string;
}

void show_error_and_exit()
{
    char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message));
    exit(1);
}

void print_cmd_before_run(char *string)
{
    write(STDOUT_FILENO, string, strlen(string));
}

void run_batch_mode(char const *filename)
{
    print_cmd_before_run("Batch Mode Support not added yet!!\n");
    show_error_and_exit();
}

int main(int argc, char const *argv[])
{
    if (argc > 2) {
        show_error_and_exit();
    }

    if (argc == 2) {
        //Shell is suppose to run in batch mode
        run_batch_mode(argv[1]);
    }

    // Running in interactive mode
    while (1)
    {
        char *cmd;
        show_prompt();
        cmd = accept_input();
        print_cmd_before_run(cmd);
    }
    
    return 0;
}
