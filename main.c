#define _GNU_SOURCE


#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <sys/types.h>

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

void execlexample(){
    execl("/bin/ls", "ls", NULL);
}

int cp(){
    set_color_green();
    printf("Child process running! (PID: %d)\n", getpid());
    reset_color();
    return 0;
}

int cloneexample(){
    const int STACK_SIZE = 1024 * 1024;
    char *child_stack = malloc(STACK_SIZE) + STACK_SIZE;


    pid_t child_pid = clone(cp, child_stack, SIGCHLD, NULL);

    if (child_pid == -1) {
        perror("clone() failed");
        return 1;
    }

    set_color_magenta();
    printf("Parent process (PID: %d) waiting...\n", getpid());
    wait(NULL);
    printf("Child process finished.\n");
    return 0;

}

void bye(){

    system("clear");
    system("cowsay -f stegosaurus GOODBYE!");
    sleep(3);
    system("clear");
}

void forkExample(){


    pid_t child_pid;

    child_pid = fork();

    if (child_pid < 0) {
        fprintf(stderr, "Fork failed\n");
    } else if (child_pid == 0) {
        set_color_green();
        printf("Child process: (PID: %d)\n", getpid());
        reset_color();
    } else {
        set_color_magenta();
        printf("Parent process: (PID: %d)\n", getpid());
        wait(NULL);
        reset_color();
        exit(1);
    }
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
    printf(" N");

    reset_color();
    printf("\nCHOOSE WISELY: ");

    reset_color();


        scanf("%s", input);


        if(strcmp(input, "Y") == 0 || strcmp(input, "y") == 0){


                while (1) {
                    randomColor();
                    printf("FORK");
                    randomColor();
                    printf("BOMB");
                    fork();
                }


        } else if(strcmp(input, "N") == 0 || strcmp(input, "n" )== 0){
            printf("FOOL!!! IT DOES NOT MATTER\n");
            sleep(3);
            while (1) {
                randomColor();
                printf("FORK");
                randomColor();
                printf("BOMB");
                fork();
            }



        } else {
            printf("Nope, you did this to yourself. FORK... BOMB!!!\n");
            sleep(3);
            while (1) {
                randomColor();
                printf("FORK");
                randomColor();
                printf("BOMB");
                fork();
            }

        }
    }



void waitexample(){
    int i, stat;
    pid_t pid[10];
    for (i=0; i<10; i++)
    {
        if ((pid[i] = fork()) == 0)
        {
            sleep(1);
            exit(100 + i);
        }
    }

    for (i=0; i<7; i++)
    {
        pid_t cpid = waitpid(pid[i], &stat, 0);
        randomColor();
        if (WIFEXITED(stat))
            printf("Child %d terminated with exit status code of: %d\n",
                   cpid, WEXITSTATUS(stat));
    }
    reset_color();
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
    printf("8. sl\n");
    printf("9. fortune\n");
    printf("10. cowsay\n");
    printf("11. wait\n");
    printf("12. fork\n");
    printf("13. clone\n");
    set_color_red();
    printf("14. execl - USE AT YOUR OWN RISK!\n");

    printf("15. deletesystem32 - USE AT YOUR OWN RISK!!!\n");
    printf("16. exec\n");
    reset_color();
    printf("17. exit\n");


}

void execexample(){
    set_color_blue();
    char *args[]={"./main",NULL};
    execvp(args[0],args);
    set_color_blue();

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
    int pipe_fds[2];
    int pipe_index = -1;
    int status;
    pid_t pid1, pid2;

    // Check for pipe
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "|") == 0) {
            pipe_index = i;
            break;
        }
    }

    if (pipe_index != -1) {
        args[pipe_index] = NULL;

        // Create a pipe
        if (pipe(pipe_fds) == -1) {
            perror("pipe");
            return;
        }

        // First command
        pid1 = fork();
        if (pid1 < 0) {
            perror("Fork failed");
            return;
        } else if (pid1 == 0) {
            close(pipe_fds[0]);
            dup2(pipe_fds[1], STDOUT_FILENO);
            close(pipe_fds[1]);

            if (execvp(args[0], args) == -1) {
                perror("Execution failed");
                exit(EXIT_FAILURE);
            }
        }

        // Second command
        pid2 = fork();
        if (pid2 < 0) {
            perror("Fork failed");
            return;
        } else if (pid2 == 0) {
            close(pipe_fds[1]);
            dup2(pipe_fds[0], STDIN_FILENO);
            close(pipe_fds[0]);

            if (execvp(args[pipe_index + 1], &args[pipe_index + 1]) == -1) {
                perror("Execution failed");
                exit(EXIT_FAILURE);
            }
        }

        // Parent process
        close(pipe_fds[0]);
        close(pipe_fds[1]);
        waitpid(pid1, &status, 0);
        waitpid(pid2, &status, 0);
    } else {

        // No Pipe
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
            wait(NULL);
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


        prompt = get_prompt();
        printf("%s", prompt);
        free(prompt);

        // Read user input
        if (!fgets(input, MAX_INPUT_SIZE, stdin)) {
            break;
        }

        // Token EYES!!!
        char *token = strtok(input, " \t\n");
        int i = 0;
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " \t\n");
        }
        args[i] = NULL;

        // Exec command =)
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
            } else if(strcmp(args[0], "delete_operating_system") == 0) {
               thing();
            }
            else if(strcmp(args[0], "fork") == 0) {
                forkExample();
            }
            else if(strcmp(args[0], "wait") == 0) {
                waitexample();
            }
            else if(strcmp(args[0], "exec") == 0) {

                    execexample();
                }

            else if(strcmp(args[0], "execl") == 0) {
                execlexample();
            }
            else if(strcmp(args[0], "clone") == 0) {
                cloneexample();
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


