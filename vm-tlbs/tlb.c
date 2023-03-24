#include "stdio.h"
#include "stdlib.h"
#include "sys/time.h"
int main(int argc, char* argv[])
{
    int pageCount = atoi(argv[1]);
    if (pageCount > 0x7FFFFFFF / 4096) {
        printf("page count is too large\n");
    }
    int iteration = atoi(argv[2]);
    int size = pageCount * 4096;
    char* page = malloc(size);
    char* pageEnd = page + size;
    struct timeval beg;
    gettimeofday(&beg, NULL);
    for (int i = 0; i < iteration; i++) {
        for (char* cur = page; cur != pageEnd; cur += 4096) {
            *cur += 1;
        }
    }
    struct timeval end;
    gettimeofday(&end, NULL);
    long seconds = end.tv_sec - beg.tv_sec;
    long microseconds = end.tv_usec - beg.tv_usec;
    double elapsed = (seconds * 1000000.0 + microseconds) / (iteration * pageCount);
    printf("page count = %d iteration = %d\n", pageCount, iteration);
    printf("Each touch takes time: %f microsecond\n", elapsed);
    return 0;
}