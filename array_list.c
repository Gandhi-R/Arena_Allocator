#include "array_list.h"
#include <stdio.h>

size_t array_create(Arena* arena, int length) {
    return arena_alloc(arena, sizeof(int) * length); // Alokasi untuk node pertama
}

size_t list_append(Arena* arena, size_t head_offset, int value) {
    size_t new_node_offset = arena_alloc(arena, sizeof(Node)); // Alokasi untuk node baru
    Node* new_node = (Node*)arena_get(arena, new_node_offset);
    
    new_node->data = value; // Set nilai data
    new_node->next_offset = -1; // Set next ke NULL
    if (head_offset == (size_t)-1) return new_node_offset; // Jika list kosong, node baru jadi head

    size_t current_offset = head_offset;
    while (1) {
        Node* current_node = (Node*)arena_get(arena, current_offset);
        if (current_node->next_offset == -1) {
            current_node->next_offset = new_node_offset; // Update next node terakhir
            break;
        }
        current_offset = current_node->next_offset; // Lanjut ke node berikutnya
    }

    return head_offset; // Kembalikan offset head yang tetap
}
