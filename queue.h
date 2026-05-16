#ifndef QUEUE_H
#define QUEUE_H
#include "arena.h"

typedef struct {
    int data;
    long next_offset;
} QueueNode;

typedef struct {
    long head_offset;
    long tail_offset;
} ArenaQueue;

void queue_init(ArenaQueue* q);
void enqueue(Arena* a, ArenaQueue* q, int value);
int dequeue(Arena* a, ArenaQueue* q); // Mengembalikan nilai yang keluar

int queue_delete_id(Arena* a, ArenaQueue* q, int value);

#endif