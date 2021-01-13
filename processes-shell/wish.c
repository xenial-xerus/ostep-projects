#include "wish.h"

char *path[MAX_PATHS];

void show_prompt()
{
    char message[7] = "wish> ";
    write(STDOUT_FILENO, message, strlen(message));
}

void init_path()
{
    // Initially the path will only contain '/bin/' folder
    char *str = "/bin";
    path[0] = (char *) malloc(strlen(str));
    strcpy(path[0], str);
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

int parse_input(char *line, char *cmd[], char *args[])
{
    char *found;
    int tot_cmd = 0;

    // Remove the newline character from the end of line
    if (line[strlen(line) - 1] == '\n')
        line[strlen(line) - 1] = 0;

    while ((found = strsep(&line, " ")) != NULL) {
        if (!(found[0] == '\0' || isspace(found[0]))) {      //Ignores extra spaces
            cmd[tot_cmd] = (char *) malloc(strlen(found) * sizeof(char));
            strcpy(cmd[tot_cmd], found);
            // Assuming only one command with zero args for now
            *args = NULL;
            tot_cmd++;
        }
    }
    return tot_cmd;
}

void show_error_and_exit()
{
    char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message));
    exit(1);
}

void print_cmd_before_run(char *cmd, char *args)
{
    if (cmd) {
        strcat(cmd, "\n");
        write(STDOUT_FILENO, cmd, strlen(cmd));
    }
    if (args) {
        strcat(args, "\n");
        write(STDOUT_FILENO, args, strlen(args));
    }
}

void run_batch_mode(char const *filename)
{
    print_cmd_before_run("Batch Mode Support not added yet!!\n", NULL);
    show_error_and_exit();
}

char *get_path(char *cmd)
{
    char *root_path;

    //Iterate path
    for (int i = 0; path[i]; i++) {
        root_path = (char *) malloc(strlen(path[i]) + strlen(cmd) + 1);
        strcpy(root_path, path[i]);
        strcat(root_path, "/");
        strcat(root_path, cmd);

        //Check if exe is present here
        if (access(root_path, X_OK) != 0) {
            free(root_path);
            continue;
        }
        return root_path;
    }

    //Any of the given paths do not have an exe, return error
    show_error_and_exit();

    return NULL;
}

void run_command(char* cmd, char *args)
{
    int rc;
    char *exe_path;

    // Search if given executable command is present in one of the defined paths
    exe_path = get_path(cmd);

    rc = fork();
    if (rc < 0) {
        show_error_and_exit();
    }
    if (rc == 0) {     //Child Process
        char *argv[2];
        argv[0] = exe_path;
        argv[1] = NULL;
        execv(argv[0], argv);
    }
    else {
        wait(NULL);
    }
}



int main(int argc, char const *argv[])
{
    if (argc > 2) {
        show_error_and_exit();
    }

    init_path();

    if (argc == 2) {
        //Shell is suppose to run in batch mode
        run_batch_mode(argv[1]);
    }

    // Running in interactive mode
    while (1)
    {
        char *line, *cmd[MAX_COMMANDS], *args[MAX_COMMANDS];
        int total_cmds = 0;
        show_prompt();
        line = accept_input();
        total_cmds = parse_input(line, cmd, args);
        for (int i = 0; i < total_cmds; i++) {
            run_command(cmd[i], args[i]);
        }
    }
    
    return 0;
}
