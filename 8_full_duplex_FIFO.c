#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
    char str[100], filename[20], result[500];
    int fd1, fd2, fd, n;

    mkfifo("fifo1", 0666);
    mkfifo("fifo2", 0666);

    fd1 = open("fifo1", O_WRONLY);

    printf("Enter a sentence: ");
    fgets(str, 100, stdin);

    write(fd1, str, sizeof(str));
    close(fd1);

    fd2 = open("fifo2", O_RDONLY);

    read(fd2, filename, sizeof(filename));
    close(fd2);

    fd = open(filename, O_RDONLY);

    n = read(fd, result, sizeof(result) - 1);
    result[n] = '\0';

    printf("\n%s", result);

    close(fd);

    return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    char str[100];
    int fd1, fd2;
    int i, ch = 0, words = 0, lines = 0;

    fd1 = open("fifo1", O_RDONLY);

    read(fd1, str, sizeof(str));
    close(fd1);

    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != '\n')
            ch++;

        if (str[i] == '\n')
            lines++;

        if ((str[i] == ' ' || str[i] == '\n') &&
            i > 0 && str[i - 1] != ' ' && str[i - 1] != '\n')
            words++;
    }

    if (i > 0 && str[i - 1] != ' ' && str[i - 1] != '\n')
        words++;

    if (i > 0 && str[i - 1] != '\n')
        lines++;

    FILE *fp = fopen("result.txt", "w");

    fprintf(fp, "Characters: %d\n", ch);
    fprintf(fp, "Words: %d\n", words);
    fprintf(fp, "Lines: %d\n", lines);

    fclose(fp);

    fd2 = open("fifo2", O_WRONLY);

    write(fd2, "result.txt", 11);

    close(fd2);

    return 0;
}
