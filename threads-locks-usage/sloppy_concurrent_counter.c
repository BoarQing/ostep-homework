#include "stdio.h"
#include "stdlib.h"
#include "sys/time.h"
#include "pthread.h"

typedef struct __counter_t {
    int value;
    pthread_mutex_t lock;
} counter_t;

void init(counter_t *c) {
    c->value = 0;
    pthread_mutex_init(&c->lock, NULL);
}

void increment(counter_t *c) {
    c->value++;
}
int lock_and_get(counter_t *c) {
    pthread_mutex_lock(&c->lock);
    int rc = c->value;
    return rc;
}

int goal = 0;
counter_t c;
void* worker(void* arg) {
    while (lock_and_get(&c) != goal) {
        increment(&c);
        pthread_mutex_unlock(&c.lock);
    }
    pthread_mutex_unlock(&c.lock);
    return NULL;
}

int main(int argc, char* argv[])
{
    int threadCount = atoi(argv[1]);
    goal = atoi(argv[2]);
    init(&c);
    pthread_t p[threadCount];

    pthread_mutex_lock(&c.lock);
    for (int i = 0; i < threadCount; i++) {
        pthread_create(&(p[i]), NULL, worker, NULL);
    }
    struct timeval beg;
    gettimeofday(&beg, NULL);
    pthread_mutex_unlock(&c.lock);
    for (int i = 0; i < threadCount; i++) {
        pthread_join(p[i], NULL);
    }
    struct timeval end;
    gettimeofday(&end, NULL);

    long seconds = end.tv_sec - beg.tv_sec;
    long microseconds = end.tv_usec - beg.tv_usec;
    double elapsed = (seconds * 1000000.0 + microseconds);
    printf("thread count = %d goal = %d\n", threadCount, goal);
    printf("Total takes time: %f microsecond\n", elapsed);
    return 0;
}