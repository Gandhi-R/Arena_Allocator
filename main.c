#include "arena.h"
#include <stdio.h>

int main()
{
    Arena myArena;
    arena_init(&myArena, 64); // Inisialisasi 64 bytes

    printf("--- Kondisi Awal ---\n");
    arena_dump(&myArena);

    size_t node1 = arena_alloc(&myArena, 8);
    size_t node2 = arena_alloc(&myArena, 8);

    printf("--- Setelah Alokasi (node1 offset: %zu, node2 offset: %zu) ---\n", node1, node2);
    arena_dump(&myArena);

    printf("--- Setelah Reset ---\n");
    arena_reset(&myArena);
    arena_dump(&myArena);

    return 0;
}