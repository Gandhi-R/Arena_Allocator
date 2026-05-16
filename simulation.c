#include "queue.h"
#include "simulation.h"
#include <stdio.h>


void run_simulation(Arena *a, ArenaQueue* q)
{

    printf("\n>>> PHASE 2: CUSTOMER SERVICE SIMULATION <<<\n");
    printf("Mencoba memasukkan ticket 101 & 102 ke shared antrean...\n");

    size_t offset_sebelum = a->offset;
    enqueue(a, q, 101);
    enqueue(a, q, 102);

    if (a->capacity == offset_sebelum)
    {
        printf(">> GAGAL SIMULASI: Arena sudah penuh semenjak stress test/alokasi sebelumnya!\n");
        return;
    }

    printf("Pelanggan 101 & 102 berhasil masuk antrean.\n");
    arena_dump(a);

    int p = dequeue(a, q);
    if (p != -1)
    {
        printf("Memproses Peserta ID dari simulasi: %d\n", p);
    }

    printf("State after one customer is served in simulation:\n");
    arena_dump(a);
}
