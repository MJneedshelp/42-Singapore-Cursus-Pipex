#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {

    // int fd;
    // int dupfd;
    // int newfd;

    // fd = open("newfile", O_RDWR | O_APPEND);
    // dupfd = dup(fd);
    // newfd = 1;
    // printf("Original fd: %d | dup fd: %d | dup2 fd: %d\n", fd, dupfd, dup2(fd, newfd));

    // write(fd, "Using old fd\n", 13);
    // write(dupfd, "Using dup fd\n", 13);
    // //write(newfd, "Using dup2 fd\n", 14);
    // printf("This will now go in the file as well\n");



    char    *str = "msg 1";
    char    *str2 = "msg 2";
    int     arr[2];
    int     pipe_ret;
    char    buf[100];
    pid_t   pid;
    int     unlink_ret;
    
    // unlink_ret = unlink("unlinkfile");

    // if (unlink_ret == 0)
    // {
    //     printf("Unlink success\n");
    // }

    pipe_ret = pipe(arr);
    if (pipe_ret < 0)
        exit (-1);

    pid = fork();
    if (pid == -1)
    {   
        perror("Fork failed");
        exit (EXIT_FAILURE);
    }

    if (pid == 0)
    {
        printf("Inside child process\n");
        close(arr[0]);
        write(arr[1], "child to parent", 15);
        close(arr[1]);
        sleep(10);
        printf("Inside child process. Check message origin: %s\n", buf);
        exit (EXIT_SUCCESS);
    }
    else
    {
        printf("Inside parent process\n");
        close(arr[1]);
        read(arr[0], buf, 15);
        close(arr[0]);
        printf("Inside parent process. Check message origin: %s\n", buf);
        wait(NULL);
        printf("Waited for child to finish\n");
    }
    return (0);

    // //write into the write end of the pipe
    // write(arr[1], str, 5);
    // write(arr[1], str2, 5);

    // //read from the read end of the pipe
    // read(arr[0], buf, 5);
    // printf("First line read from pipe: %s\n", buf);
    // read(arr[0], buf, 5);
    // printf("Second line read from pipe: %s\n", buf);


    // char    *args[3];

    // args[0] = "ls";
    // args[1] = "-l";
    // args[2] = NULL;

    // execve("/bin/ls", args, NULL);
    // printf("Will this be printed?\n");
    // return (0);




}