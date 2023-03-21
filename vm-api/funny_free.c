#include "stdlib.h"
int main(int argc, char* argv[])
{
    void* array = malloc(1024);
    free(array + 512);
    return 0;
}