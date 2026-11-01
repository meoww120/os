
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>

int main()
{
    int p1[2], p2[2], fd;
    char filename[10] = {'\0'};
    char buffer[200] = {'\0'};

    pid_t pid;

    pipe(p1);
    pipe(p2);

    pid = fork();

    if(pid != 0) // parent
    {
        close(p1[0]); // close the read end of p1
        close(p2[1]); // close the write end of p2

        write(p1[1], "abc.txt", 7);
        close(p1[1]);

        while(read(p2[0], buffer, sizeof(buffer)))
        {
            printf("%s", buffer);
        }

        close(p2[0]);
    }
    else
    {
        close(p1[1]); // close the write end of p1
        close(p2[0]); // close the read end of p2

        read(p1[0], filename, sizeof(filename));
        close(p1[0]);

        fd = open(filename, O_RDONLY);

        if(fd < 0)
        {
            write(p2[1], "file not found", 14);
        }
        else
        {
            while(read(fd, buffer, sizeof(buffer)))
            {
                write(p2[1], buffer, sizeof(buffer));
            }

            close(fd);
        }

        close(p2[1]);
    }
    return 0;
}
