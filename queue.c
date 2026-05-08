#include "queue.h"
#include <stdio.h>

void queue_init(ArenaQueue* q) {
    q->head_offset = -1;
    q->tail_offset = -1;
}

void enqueue(Arena* a, ArenaQueue* q, int value) {
    size_t off = arena_alloc(a, sizeof(QueueNode));
    if (off == (size_t)-1) return;

    QueueNode* newNode = (QueueNode*)arena_get(a, off);
    newNode->data = value;
    newNode->next_offset = -1;

    if (q->tail_offset == -1) {
        q->head_offset = q->tail_offset = off;
    } else {
        QueueNode* lastNode = (QueueNode*)arena_get(a, q->tail_offset);
        lastNode->next_offset = off;
        q->tail_offset = off;
    }
}

int dequeue(Arena* a, ArenaQueue* q) {
    if (q->head_offset == -1) return -1; // Kosong

    QueueNode* headNode = (QueueNode*)arena_get(a, q->head_offset);
    int value = headNode->data;
    
    // Geser head ke depan (Node lama tetap di memori, tidak di-free!)
    q->head_offset = headNode->next_offset;
    
    if (q->head_offset == -1) q->tail_offset = -1;
    
    return value;
}