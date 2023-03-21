#include "stdlib.h"
int main(int argc, char* argv[])
{
    void* array = malloc(100);
    ((char*)array)[100] = 1;
    return 0;
}