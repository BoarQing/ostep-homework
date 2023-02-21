#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
// do know how not to use wait
int main(int argc, char *argv[]) {
    int rc = fork();
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child (new process)
        printf("hello\n");
    } else { // parent goes down this path (main)
        int rc_wait = wait(NULL);
        printf("goodbyte\n");
    }
    return 0;
 }