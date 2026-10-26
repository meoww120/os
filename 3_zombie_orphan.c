
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child process exiting.\n");
        exit(0);
    }
    else if (pid > 0) {
        printf("Parent PID: %d, Child PID: %d\n",
               getpid(), pid);

        printf("Parent sleeping; child becomes zombie.\n");
        sleep(5);

        wait(NULL);
        printf("Zombie process removed.\n");
    }
    else {
        printf("Fork failed!\n");
        return 1;
    }

    printf("\nCreating orphan process...\n");
    fflush(stdout);

    pid = fork();

    if (pid == 0) {
        sleep(2);
        printf("Orphan child PID: %d\n", getpid());
        printf("New Parent PID: %d\n", getppid());
    }
    else if (pid > 0) {
        printf("Parent exiting. Child will become orphan.\n");
        fflush(stdout);
        return 0;
    }
    else {
        printf("Fork failed!\n");
        return 1;
    }

    return 0;
}
