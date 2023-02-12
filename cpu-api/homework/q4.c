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
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        // run ls on ls executable with option -l

        // char *myargs[] = {"/usr/bin/ls", "/usr/bin/ls", "-l", (char*)NULL};
        // execv(myargs[0], myargs); // variable length array

        // char *myargs[] = {"ls", "/usr/bin/ls", "-l", (char*)NULL};
        // execvp(myargs[0], myargs); // with path

        //    binary         binary         ls arg1        ls arg2     end mark
        //execl("/usr/bin/ls", "/usr/bin/ls", "/usr/bin/ls", "-l", (char*)NULL);
        
        // env setup only happens after call
        // char *env[] = {"PATH=IS_CHANGED", NULL};
        // execle("/usr/bin/env", "/usr/bin/env", (char*)NULL, env);

        // execlp("ls", "ls", "/usr/bin/ls", "-l", (char*)NULL);

        // char *myargs[] = {"env", (char*)NULL};
        // char *env[] = {"PATH=IS_CHANGED", NULL};
        // execvpe(myargs[0], myargs, env);

    } else { // parent goes down this path (main)
        int rc_wait = wait(NULL);
        printf("hello, I am parent of %d (rc_wait:%d) (pid:%d)\n",
        rc, rc_wait, (int) getpid());
    }
    return 0;
}