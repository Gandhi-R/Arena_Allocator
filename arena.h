#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>

typedef struct {
    void* buffer;      // Blok memori utama 
    size_t capacity;   // Total ukuran arena
    size_t offset;     // Posisi alokasi saat ini [cite: 25]
} Arena;

// API Arena sesuai ketentuan [cite: 20, 49]
void arena_init(Arena* arena, size_t size);
size_t arena_alloc(Arena* arena, size_t size);
void* arena_get(Arena* arena, size_t offset);
void arena_reset(Arena* arena);
void arena_dump(Arena* arena); // Visualisasi ASCII sederhana [cite: 15, 27]

#endif