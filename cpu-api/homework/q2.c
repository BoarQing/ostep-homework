#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// writing to same file is a disaster
int main(int argc, char *argv[]) {
    printf("hello world (pid:%d)\n", (int) getpid());
    FILE *f = fopen("input.txt", "wb");
    int rc = fork();
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process) 
        for (int i = 0; i < 1000; i++) {
            fputs("hello, I am child\n", f);
        }
        printf("hello, I am child (pid:%d)\n", (int) getpid());
    } else {
        // parent goes down this path (main)
        for (int i = 0; i < 1000; i++) {
            fputs("hello, I am parent\n", f);
        }
        printf("hello, I am parent of %d (pid:%d)\n", rc, (int) getpid());
    }
    return 0;
}