#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
    int fd1, fd2;
    char text[1000], result[1000];
    int chars, words, lines, i;

    mkfifo("fifo1", 0666);
    mkfifo("fifo2", 0666);

    if (fork() == 0)
    {
        // Child process: receives text and counts
        fd1 = open("fifo1", O_RDONLY);
        read(fd1, text, sizeof(text) - 1);
        close(fd1);

        chars = strlen(text);
        words = 0;
        lines = 0;

        for (i = 0; text[i] != '\0'; i++)
        {
            if (text[i] == ' ' || text[i] == '\n')
                words++;

            if (text[i] == '\n')
                lines++;
        }

        if (chars > 0 && text[chars - 1] != '\n')
            lines++;

        if (chars > 0 && text[chars - 1] != ' ' &&
            text[chars - 1] != '\n')
            words++;

        // Store results in a file
        FILE *fp = fopen("result.txt", "w");
        fprintf(fp, "Text: %s\n", text);
        fprintf(fp, "Characters: %d\n", chars);
        fprintf(fp, "Words: %d\n", words);
        fprintf(fp, "Lines: %d\n", lines);
        fclose(fp);

        // Send file contents back through second FIFO
        fp = fopen("result.txt", "r");
        fd2 = open("fifo2", O_WRONLY);

        while (fgets(result, sizeof(result), fp) != NULL)
            write(fd2, result, strlen(result));

        close(fd2);
        fclose(fp);
    }
    else
    {
        // Parent process: sends text
        printf("Enter sentences (press Ctrl+D when finished):\n");

        text[0] = '\0';

        while (fgets(result, sizeof(result), stdin) != NULL)
        {
            if (strlen(text) + strlen(result) < sizeof(text))
                strcat(text, result);
            else
            {
                printf("Input too long!\n");
                break;
            }
        }

        fd1 = open("fifo1", O_WRONLY);
        write(fd1, text, strlen(text) + 1);
        close(fd1);

        // Receive results from child
        fd2 = open("fifo2", O_RDONLY);
        printf("\nResults received from child:\n");

        while ((i = read(fd2, result, sizeof(result) - 1)) > 0)
        {
            result[i] = '\0';
            printf("%s", result);
        }

        close(fd2);
        wait(NULL);

        unlink("fifo1");
        unlink("fifo2");
    }

    return 0;
}