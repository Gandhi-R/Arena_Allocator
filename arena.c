#include "arena.h"
#include <stdio.h>
#include <stdlib.h>

void arena_init(Arena* arena, size_t size) {
    arena->buffer = malloc(size); // Satu-satunya malloc [cite: 6]
    arena->capacity = size;
    arena->offset = 0;
}

size_t arena_alloc(Arena* arena, size_t size) {
    if (arena->offset + size <= arena->capacity) {
        size_t current_offset = arena->offset;
        arena->offset += size; // Geser penanda memori 
        return current_offset; // Kembalikan offset (integer), bukan pointer 
    }
    return -1; // Memori penuh
}

void* arena_get(Arena* arena, size_t offset) {
    if (offset >= arena->capacity) return NULL;
    return (char*)arena->buffer + offset; // Konversi offset ke alamat memori 
}

void arena_reset(Arena* arena) {
    arena->offset = 0; // Hapus semua data secara instan dalam O(1) 
}

void arena_dump(Arena* arena) {
    printf("Arena Status: [%zu/%zu] bytes used\n", arena->offset, arena->capacity);
    for (size_t i = 0; i < arena->capacity; i++) {
        if (i < arena->offset) printf("[#]"); // Memori terisi
        else printf("[.]");                   // Memori kosong
        if ((i + 1) % 16 == 0) printf("\n");
    }
    printf("\n");
}