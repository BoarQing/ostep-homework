#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define BUF_LEN 1024
int main(int argc, char *argv[])
{
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        fprintf(stderr, "create pipe failed\n");
        exit(1);
    }
    int pid1 = fork();
    if (pid1 == -1) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if (pid1 == 0) { // children
        char buf[BUF_LEN] = {};
        sprintf(buf, "this is pid(%d) speaking", getpid());
        printf("send msg: %s\n", buf);
        write(pipefd[1], buf, strlen(buf));
        exit(0);
    }
    waitpid(pid1, NULL, 0);
    int pid2 = fork();
    if (pid2 == 0) {
        char buf[BUF_LEN] = {};
        read(pipefd[0], buf, BUF_LEN);
        printf("receive msg at pid(%d): %s\n", getpid(), buf);
        exit(0);
    }
    waitpid(pid2, NULL, 0);
    return 0;
}