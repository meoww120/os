#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    int arr[5] = {45, 12, 67, 23, 9};
    int n = 5;

    pid = fork();

    if (pid == 0)
    {
        // Child process
        printf("\nThis is Child Process\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
        // Sort in ascending order
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (arr[j] > arr[j + 1])
                {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }

        printf("Ascending order: ");
        for (int i = 0; i < n; i++)
            printf("%d ", arr[i]);

        printf("\n");
        exit(0);
    }
    else if (pid > 0)
    {
        // Parent process
        wait(NULL);

        printf("\nThis is Parent Process\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);

        // Sort in descending order
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (arr[j] < arr[j + 1])
                {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }

        printf("Descending order: ");
        for (int i = 0; i < n; i++)
            printf("%d ", arr[i]);

        printf("\n");
    }
    else
    {
        printf("Fork failed!\n");
        return 1;
    }

    return 0;
}
