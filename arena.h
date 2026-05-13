#ifndef ARENA_H
#define ARENA_H
#include <stddef.h>

typedef struct {
    void* buffer;
    size_t capacity;
    size_t offset;
} Arena;

void arena_init_static(Arena* arena, void* static_buffer, size_t size);
size_t arena_alloc(Arena* arena, size_t size);
void* arena_get(Arena* arena, size_t offset);
void arena_reset(Arena* arena);
void arena_dump(Arena* arena);
#endif