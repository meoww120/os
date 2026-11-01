
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>

int main()
{
    int dept1[2], dept2[2], fd;
    char filename[10] = {'\0'};
    char buffer[200] = {'\0'};

    pid_t pid;

    pipe(dept1);
    pipe(dept2);

    pid = fork();

    if(pid != 0) // parent
    {
        close(dept1[0]); // close the read end of dept1
        close(dept2[1]); // close the write end of dept2

        write(dept1[1], "abc.txt", 7);
        close(dept1[1]);

        while(read(dept2[0], buffer, sizeof(buffer)))
        {
            printf("%s", buffer);
        }

        close(dept2[0]);
    }
    else
    {
        close(dept1[1]); // close the write end of dept1
        close(dept2[0]); // close the read end of dept2

        read(dept1[0], filename, sizeof(filename));
        close(dept1[0]);

        fd = open(filename, O_RDONLY);

        if(fd < 0)
        {
            write(dept2[1], "file not found", 14);
        }
        else
        {
            while(read(fd, buffer, sizeof(buffer)))
            {
                write(dept2[1], buffer, sizeof(buffer));
            }

            close(fd);
        }

        close(dept2[1]);
    }
    return 0;
}
