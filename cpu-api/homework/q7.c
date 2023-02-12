#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>



int main(int argc, char *argv[]) {
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child (new process)
        // no child
        fclose(STDOUT_FILENO);
        printf("hello, I am child (pid:%d)\n", (int) getpid()); // disappear
    } else { // parent goes down this path (main)
        // rc_wait is the pid of child processs
        // if argu is not null, return value is used to check ste return status of the child process
        int waitStatus = 0;
        int rc_wait = wait(&waitStatus);
        printf("if child exit normally %d\n", WIFEXITED(waitStatus));
        printf("hello, I am parent of %d (rc_wait:%d) (pid:%d)\n",
        rc, rc_wait, (int) getpid());
    }
    return 0;
}