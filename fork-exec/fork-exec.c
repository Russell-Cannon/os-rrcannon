#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void child() {
    printf("Hello from Child Process (pid %d)!\n", getpid());
    execl("./hi", "hi", (char *) NULL);
}

void parent(pid_t child_pid) {
    printf("Hello from Parent Process (parent pid %d, child pid %d)!\n", getpid(), child_pid);

    waitpid(child_pid, NULL, 0); //wait for child to finish.
    printf("Parent process (pid %d) exiting.\n", getpid());
}

int main(int argc, char* argv[]) {
    (void) argc; //supress warnings
    (void) argv;

    int status = fork();
    if (status < 0) {
        //Fork failed
        return 1;
    } if (status == 0) {
        //Child process
        child();
    } else {
        //Parent process
        parent(status);
    }

    return 0;
}
