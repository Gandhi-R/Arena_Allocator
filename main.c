#include "arena.h"
#include <stdio.h>

/*void demo_minggu1(Arena *a)
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
*/

void demo_minggu2(Arena *a)
{
    // Demo Array
    size_t arr_off = create_array(&myArena, 5);
    int *arr = (int *)arena_get(&myArena, arr_off);
    arr[0] = 10;
    arr[1] = 20; // Mengisi array

    // Demo Linked List
    size_t head = -1;
    head = list_append(&myArena, head, 100);
    head = list_append(&myArena, head, 200);

    // Menampilkan Output yang diminta asisten
    printf("--- LINKED LIST TRAVERSAL ---\n");
    size_t curr = head;
    while (curr != -1)
    {
        Node *n = (Node *)arena_get(&myArena, curr);
        printf("[Offset: %zu] Data: %d | Next Offset: %ld\n", curr, n->data, n->next_offset);
        curr = n->next_offset;
    }

    printf("\n--- VISUALISASI ARENA (GRID) ---\n");
    arena_dump(&myArena); // Menampilkan kondisi memori
}

int main()
{
    Arena myArena;
    arena_init(&myArena, 1024); // Inisialisasi arena dengan 1024 bytes

    demo_minggu2(&myArena); // Jalankan demo minggu 2

    return 0;
}