#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#define total 5
int forkOne() {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    if (rc == 0) {
        printf("hello, I am child (pid:%d)\n", getpid());
        exit(0);
    }
    return rc;
}
int main(int argc, char *argv[]) {
    int pid[total] = {};
    for (int i = 0; i < total; ++i) {
        pid[i] = forkOne();
    }
    for (int i = 0; i < total; ++i) {
        int waitStatus = 0;
        int rc_wait = waitpid(pid[i], &waitStatus, 0);
    }
    for (int i = 0; i < total; ++i) {
        printf("hello, I am parent of %d (pid:%d)\n", pid[i], getpid());
    }
    return 0;
}