#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include "arena.h"

typedef struct {
    int data;
    long next_offset;
} Node;

size_t array_create(Arena* arena, int length); // Membuat list dengan panjang tertentu
size_t list_append(Arena* arena, size_t head_offset, int value);
void display_list(Arena* arena, size_t head_offset);

#endif