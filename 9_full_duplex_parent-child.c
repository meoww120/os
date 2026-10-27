#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int p1[2], p2[2];
    pid_t pid;
    char filename[100];
    char buffer[1000];

    // Create two pipes
    pipe(p1);
    pipe(p2);

    pid = fork();

    if (pid == 0)
    {
        // Child process
        close(p1[1]);
        close(p2[0]);

        // Read filename from parent
        read(p1[0], filename, sizeof(filename));
        filename[sizeof(filename) - 1] = '\0';

        // Open the file
        FILE *fp = fopen(filename, "r");

        if (fp == NULL)
        {
            strcpy(buffer, "Error: File not found!\n");
        }
        else
        {
            int n = fread(buffer, 1, sizeof(buffer) - 1, fp);
            buffer[n] = '\0';
            fclose(fp);
        }

        // Send file contents to parent
        write(p2[1], buffer, strlen(buffer) + 1);

        close(p1[0]);
        close(p2[1]);
    }
    else if (pid > 0)
    {
        // Parent process
        close(p1[0]);
        close(p2[1]);

        // Enter filename
        printf("Enter file pathname: ");
        scanf("%99s", filename);

        // Send filename to child
        write(p1[1], filename, strlen(filename) + 1);
        close(p1[1]);

        // Read file contents from child
        int n = read(p2[0], buffer, sizeof(buffer));

        if (n > 0)
        {
            buffer[n - 1] = '\0';
            printf("\nFile contents:\n%s\n", buffer);
        }

        close(p2[0]);
        wait(NULL);
    }
    else
    {
        perror("fork");
        return 1;
    }

    return 0;
}