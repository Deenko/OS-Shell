
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h> // For errno
#include <fcntl.h> // For open

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64

char *get_prompt() {
    char machine_name[MAX_INPUT_SIZE];
    char *username = getlogin();
    gethostname(machine_name, sizeof(machine_name));
    char *prompt = malloc(MAX_INPUT_SIZE * sizeof(char));
    sprintf(prompt, "%s@%s:~$ ", machine_name, username);
    return prompt;
}

void execute_command(char *args[]) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            if (errno == ENOENT) {
                printf("%s: command not found\n", args[0]);
            } else {
                perror("Execution failed");
            }
            exit(EXIT_FAILURE);
        }
    } else {
        wait(NULL);
    }
}



void runShell() {
    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARGS];
    char *prompt;
    int status;

    while (1) {
        // Print the prompt
        prompt = get_prompt();
        printf("%s", prompt);
        free(prompt);

        // Read user input
        if (!fgets(input, MAX_INPUT_SIZE, stdin)) {
            break;
        }

        // Tokenize input
        char *token = strtok(input, " \t\n");
        int i = 0;
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " \t\n");
        }
        args[i] = NULL;

        // Execute command
        if (args[0] != NULL) {
            if (strcmp(args[0], "exit") == 0) {
                break;
            } else if (strcmp(args[0], "cd") == 0) {
                if (args[1] == NULL) {
                    fprintf(stderr, "cd: missing operand\n");
                } else {
                    status = chdir(args[1]);
                    if (status != 0) {
                        perror("cd");
                    }
                }
            } else if (strcmp(args[0], "cmatrix") == 0) {
                pid_t pid = fork();
                if (pid < 0) {
                    perror("Fork failed");
                    exit(EXIT_FAILURE);
                } else if (pid == 0) {
                    execlp("cmatrix", "cmatrix", NULL);
                    perror("Execution failed");
                    exit(EXIT_FAILURE);
                } else {
                    wait(NULL);
                }
            } else if (strcmp(args[0], "wc") == 0 ||
                       strcmp(args[0], "grep") == 0 ||
                       strcmp(args[0], "df") == 0) {
                execute_command(args);
            } else {
                printf("%s: command not found\n", args[0]);
            }
        }
    }
}






int main() {
    shell();
    return 0;
}


