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

int queue_delete_id(Arena* a, ArenaQueue* q, int value) {
    if (q->head_offset == -1) return 0; // Antrean kosong, gagal hapus

    size_t current_offset = q->head_offset;
    size_t prev_offset = -1;
    int found = 0;

    while (current_offset != -1) {
        QueueNode* current_node = (QueueNode*)arena_get(a, current_offset);

        if (current_node->data == value) {
            found = 1;
            
            if (prev_offset == -1) {
                // Kasus 1: Node yang dihapus adalah HEAD
                q->head_offset = current_node->next_offset;
                if (q->head_offset == -1) {
                    q->tail_offset = -1; // Jika antrean jadi kosong
                }
            } else {
                // Kasus 2: Node yang dihapus ada di tengah atau di TAIL
                QueueNode* prev_node = (QueueNode*)arena_get(a, prev_offset);
                prev_node->next_offset = current_node->next_offset;
                
                // Jika node yang dihapus adalah TAIL, update tail_offset ke node sebelumnya
                if (current_offset == q->tail_offset) {
                    q->tail_offset = prev_offset;
                }
            }
            break;
        }
        prev_offset = current_offset;
        current_offset = current_node->next_offset;
    }

    return found; // Mengembalikan 1 jika sukses dihapus, 0 jika ID tidak ditemukan
}