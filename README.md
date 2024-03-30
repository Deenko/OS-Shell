Welcome to LOTR-Shell.

A project by Denis Mahmutovic & Claudio Merlonghi.

The functionality of this project is to showcase the application of system calls as well as to demonstrate how piping several commands together can change the output of the code for the Operating Systems course.

To compile:

gcc -o main main.c

The shell comes with the following commands:
1. wc 
2. grep 
3. df
4. clear 
5. help
6. forkbomb
7. cmatrix
8. sl
9. fortune
10. cowsay
11. wait
12. fork
13. clone
14. execl
15. delete_operating_system
16. exec
17. exit

Answers to task 1.5:

Q: If we have a single-core, uniprocessor system that supports multiprogramming,
how many processes can be in a running state in such a system, at any given time? 

A: In a single-core, uniprocessor system that supports multiprogramming, only one process can be in the running state at any given time.
Since the system has one physical CPU core, it can only run one set of instructions at a moment, but due to the speed of the CPU itself, it creates an illusion of multiple processes running simultaneously by switching between processes. 

Q: Explain why system calls are needed for a shared memory method of
inter-process communication (IPC). If there are multiple threads in one process, are the system
calls needed for sharing memory between those threads?

A: System calls are needed for shared memory IPC because they break the memory isolation between processes in a safe way.
The operating system uses system calls to allocate and manage the shared memory as a resource. Additionally, these system calls help implement synchronization tools to prevent data corruption when multiple processes access the shared space. In contrast, threads within a single process already share memory, so they don't need system calls for basic sharing. However, threads still require synchronization mechanisms 
(often provided by libraries) to coordinate their access to shared data structures. System calls remain crucial for the controlled and synchronized use of shared memory between separate processes.

Q:  Consider the following sample code from a simple shell program. Now,
suppose the shell wishes to redirect the output of the command not to STDOUT but to a file
“foo.txt”. Show how you would modify the above code to achieve this output redirection.


command = read_from_user();
int rc = fork();
if (rc == 0) { // child
    exec(command);
} else{ //parent
wait();
}


A: The modifications to the code would be as such:





int main() {
    char* command = read_from_user(); // Assume read_from_user() is a function that reads a command from the user
    int rc = fork();
        if (rc < 0) { // fork failed
    fprintf(stderr, "Fork failed\n");
    exit(1);
        } else if (rc == 0) { // child process

        int fd = open("foo.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
        if (fd < 0) {
        fprintf(stderr, "Failed to open file\n");
        exit(1);
        }

        // Redirect STDOUT to the file
        if (dup2(fd, STDOUT_FILENO) < 0) {
            fprintf(stderr, "Failed to redirect STDOUT\n");
            exit(1);
        }

        fprintf(stderr, "Exec failed\n");
        exit(1);
        } else { // parent process
        wait(NULL); // Wait for the child process to finish
        }

    return 0;
