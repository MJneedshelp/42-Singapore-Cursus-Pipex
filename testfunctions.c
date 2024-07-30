#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

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
    char    buf[6];

    pipe_ret = pipe(arr);
    if (pipe_ret < 0)
        exit (-1);

    //write into the write end of the pipe
    write(arr[1], str, 5);
    write(arr[1], str2, 5);

    //read from the read end of the pipe
    read(arr[0], buf, 5);
    printf("First line read from pipe: %s\n", buf);
    read(arr[0], buf, 5);
    printf("Second line read from pipe: %s\n", buf);   



    return (0);
}