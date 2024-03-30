#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h> // For errno
#include <fcntl.h> // For open
#include <time.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 128





void set_color_red() {
    printf("\033[1;31m");
}

void set_color_orange() {
    printf("\033[1;33m");
}
void set_color_yellow() {
    printf("\033[1;33m");
}
void set_color_green() {
    printf("\033[1;32m");
}
void set_color_blue() {
    printf("\033[0;34m");
}

void set_color_brown() {
    printf("\033[1;33m");
}

void set_color_black() {
    printf("\033[1;30m");
}

void set_color_white() {
    printf("\033[1;37m");
}

void set_color_magenta(){
    printf("\033[1;35m");
}
void reset_color() {
    printf("\033[0m");
}


void bye(){

    system("clear");
    system("cowsay -f stegosaurus GOODBYE!");
    sleep(3);
    system("clear");
}



void randomColor(void) {
#define LOWER_LIMIT 0
#define UPPER_LIMIT 8

    int num = (rand() % (UPPER_LIMIT - LOWER_LIMIT + 1)) + LOWER_LIMIT;
    switch(num) {
        case 0:
            set_color_red();
            break;

        case 1:
            set_color_green();
            break;

        case 2:
            set_color_magenta();
            break;

        case 3:
            set_color_yellow();
            break;

        case 4:
            set_color_orange();
            break;

        case 5:
            set_color_blue();
            break;

        case 6:
            set_color_brown();
            break;

        case 7:
            set_color_black();
            break;

        case 8:
            set_color_white();

        default:
            reset_color();
            break;
    }
}


void thing(){
    system("mpv --no-config --vo=tct rr2.mp4");
}

void forkbomb(){
    char input[3];
    set_color_red();
    printf("Do you really want to do this? (Y/N)\n");
    printf("\nY");
    set_color_green();
    printf("\nN");

    printf("CHOOSE WISELY: ");

    reset_color();
    char input2[3];

    while(1){
        scanf("%s", input);


        if(strcmp(input, "Y") == 0 || strcmp(input, "y") == 0){
            set_color_red();
            printf("\nPLEASE DO NOT DO THIS.");
            printf("\nDo you wish to continue?");

            scanf("%s", input2);


            if(strcmp(input2, "Y") == 0 || strcmp(input2, "y") == 0){

                while (1) {
                    randomColor();
                    printf("FORK");
                    randomColor();
                    printf("BOMB");
                    fork();
                }
            } else if(strcmp(input, "N") == 0 || strcmp(input, "n" )== 0){
                set_color_green();
                printf("\nWise choice.");
                reset_color();
                break;
            } else{
                printf("For your safety, we will exit!");
                break;
            }

        } else if(strcmp(input, "N") == 0 || strcmp(input, "n" )== 0){
            set_color_green();
            printf("Wise choice.\n");
            reset_color();
            break;
        } else {
            printf("\nINVALID INPUT!");
            printf("\nFor your safety, we will exit.\n");
            break;
        }


    }






}


void help(){
    printf("\nList of available commands: \n");
    printf("1. wc \n");
    printf("2. grep \n");
    printf("3. df \n");
    printf("4. clear \n");
    printf("5. help \n");
    set_color_red();
    printf("6. forkbomb - USE AT YOUR OWN RISK\n");
    reset_color();
    printf("7. cmatrix\n");
    printf("8. exit\n");
}


void lotrIntro(){

    system("clear");
    set_color_orange();
    printf("                                             _______________________\n"
           "   _______________________-------------------                       `\\\n"
           " /:--__                                                              |\n"
           "||< > |                                   ___________________________/\n"
           "| \\__/_________________-------------------                         |\n"
           "|                                                                  |\n"
           " |                       THE LORD OF THE RINGS                      |\n"
           " |                                                                  |\n"
           " |      \"Three Rings for the Elven-kings under the sky,             |\n"
           "  |        Seven for the Dwarf-lords in their halls of stone,        |\n"
           "  |      Nine for Mortal Men doomed to die,                          |\n"
           "  |        One for the Dark Lord on his dark throne                  |\n"
           "  |      In the Land of Mordor where the Shadows lie.                 |\n"
           "   |       One Ring to rule them all, One Ring to find them,          |\n"
           "   |       One Ring to bring them all and in the darkness bind them   |\n"
           "   |     In the Land of Mordor where the Shadows lie.                |\n"
           "  |                                              ____________________|_\n"
           "  |  ___________________-------------------------                      `\\\n"
           "  |/`--_                                                                 |\n"
           "  ||[ ]||                                            ___________________/\n"
           "   \\===/___________________--------------------------\n");

    reset_color();
    sleep(3);
    system("clear");
}

char *get_prompt() {
    char machine_name[MAX_INPUT_SIZE];
    char *username = getlogin();
    gethostname(machine_name, sizeof(machine_name));
    char *prompt = malloc(MAX_INPUT_SIZE * sizeof(char));

    set_color_red();
    printf("%s", machine_name);

    set_color_green();
    printf( "@");
    set_color_blue();
    printf("%s", username);

    reset_color();
    sprintf(prompt,":~$ ");


    return prompt;
}

void execute_command(char *args[]) {
    int pipe_fds[2]; // File descriptors for the pipe
    int pipe_index = -1; // Index of the pipe in args, if present
    int status;
    pid_t pid1, pid2;

    // Check for a pipe in the command
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "|") == 0) {
            pipe_index = i;
            break;
        }
    }

    if (pipe_index != -1) { // Pipe exists in the command
        args[pipe_index] = NULL; // Split the args array into two at the pipe

        // Create a pipe
        if (pipe(pipe_fds) == -1) {
            perror("pipe");
            return;
        }

        // First command (before the pipe)
        pid1 = fork();
        if (pid1 < 0) {
            perror("Fork failed");
            return;
        } else if (pid1 == 0) { // Child process for the first command
            close(pipe_fds[0]); // Close unused read end
            dup2(pipe_fds[1], STDOUT_FILENO); // Replace stdout with pipe write end
            close(pipe_fds[1]); // Close original write end of the pipe

            if (execvp(args[0], args) == -1) {
                perror("Execution failed");
                exit(EXIT_FAILURE);
            }
        }

        // Second command (after the pipe)
        pid2 = fork();
        if (pid2 < 0) {
            perror("Fork failed");
            return;
        } else if (pid2 == 0) { // Child process for the second command
            close(pipe_fds[1]); // Close unused write end
            dup2(pipe_fds[0], STDIN_FILENO); // Replace stdin with pipe read end
            close(pipe_fds[0]); // Close original read end of the pipe

            if (execvp(args[pipe_index + 1], &args[pipe_index + 1]) == -1) {
                perror("Execution failed");
                exit(EXIT_FAILURE);
            }
        }

        // Parent process
        close(pipe_fds[0]); // Close the read end of the pipe
        close(pipe_fds[1]); // Close the write end of the pipe
        waitpid(pid1, &status, 0); // Wait for the first child
        waitpid(pid2, &status, 0); // Wait for the second child
    } else {
        // Original code for executing a single command without piping
        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) { // Child process
            if (execvp(args[0], args) == -1) {
                if (errno == ENOENT) {
                    printf("%s: command not found\n", args[0]);
                } else {
                    perror("Execution failed");
                }
                exit(EXIT_FAILURE);
            }
        } else {
            wait(NULL); // Parent process waits for the child to finish
        }
    }
}











void runShell() {
    set_color_magenta();
    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARGS];
    char *prompt;


    while (1) {
        set_color_magenta();

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
                set_color_magenta();
                bye();
                break;
            }
            else if (strcmp(args[0], "wc") == 0 ||strcmp(args[0], "grep") == 0 || strcmp(args[0], "df") == 0 ||strcmp(args[0], "sl" )== 0 ||strcmp(args[0], "cmatrix") == 0 || strcmp(args[0], "clear") == 0 || strcmp(args[0], "fortune") == 0 ||strcmp(args[0], "cowsay") == 0 ||strcmp(args[0], "dig") == 0) {

                execute_command(args);
            }

            else if(strcmp(args[0], "help") == 0){
                help();
            } else if (strcmp(args[0], "forkbomb") == 0){
                forkbomb();
            } else if(strcmp(args[0], "easteregg") == 0) {
               thing();
            }






            else {
                set_color_red();
                printf("%s: command not found\n", args[0]);

            }
        }
    }
}






int main() {
    lotrIntro();
    runShell();
    return 0;
}


