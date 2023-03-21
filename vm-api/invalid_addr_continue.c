#include "stdlib.h"
#include "stdio.h"
int main(int argc, char* argv[])
{
    void* array = malloc(100);
    for (int i = 0; i < 100; i++)
        ((char*)array)[i] = i;
    free(array);
    for (int i = 0; i < 100; i++)
        printf("at %d %d\n", i, ((char*)array)[i]);
    return 0;
}