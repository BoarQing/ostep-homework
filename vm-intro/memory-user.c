#include "stdio.h"
#include "stdlib.h"
int global = 0;
int main(int argc, char* argv[])
{
    int size = atoi(argv[1]);
    printf("alloc size %d\n", size);
    void* array = malloc(size);
    printf("address of alloc %p\n", array);
    printf("address of stack %p\n", &size);
    printf("address of global variable %p\n", &global);
    printf("address of function %p\n", main);
    
redo:
    for (int i = 0; i < size; i++) {
        ((char*)array)[i] += 1;
    }
    goto redo;
    return 0;
}