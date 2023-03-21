#include "stdlib.h"
#include "stdio.h"
typedef struct {
    int capacity;
    int size;
    int* ptr;
} vector;


void init(vector* v) 
{
    v->capacity = 8;
    v->size = 0;
    v->ptr = malloc(sizeof(int) * v->capacity);
}

void destruct(vector* v)
{
    free(v->ptr);
}

void push(vector* v, int val)
{
    v->ptr[v->size] = val;
    ++v->size;
    if (v->size >= v->capacity * 3 / 4) {
        v->capacity *= 2;
        v->ptr = realloc(v->ptr, sizeof(int) * v->capacity);
    }
}
void pop(vector* v)
{
    --v->size;
    if (v->size <= v->capacity * 1 / 4 && v->capacity >= 16) {
        v->capacity /= 2;
        v->ptr = realloc(v->ptr, sizeof(int) * v->capacity);
    }
}

void set(vector* v, int pos, int val)
{
    v->ptr[pos] = val;
}

int get(vector* v, int pos)
{
    return v->ptr[pos];
}

int main(int argc, char* argv[])
{
    vector v;
    init(&v);
    int size = 128;
    for (int i = 0; i < size; i++) {
        push(&v, i);
    }
    int delSize = 100;
    printf("capacity %d\n", v.capacity);
    for (int i = 0; i < delSize; i++) {
        pop(&v);
    }
    printf("capacity %d\n", v.capacity);
    for (int i = 0; i < size - delSize; i++) {
        set(&v, i, get(&v, i) * 2);
    }
    for (int i = 0; i < size - delSize; i++) {
        printf("%d %d\n", i, get(&v, i));
    }
    for (int i = 0; i < size - delSize; i++) {
        pop(&v);
    }
    printf("capacity %d\n", v.capacity);
    destruct(&v);
}