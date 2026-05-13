#include "queue.h"
#include "simulation.h"
#include <stdio.h>

void run_simulation(Arena* a) {
    ArenaQueue q;
    queue_init(&q);

    printf("\n>>> PHASE 2: CUSTOMER SERVICE SIMULATION <<<\n");
    enqueue(a, &q, 101);
    enqueue(a, &q, 102);
    
    printf("customer ticket 101 & 102 masuk antrean...\n");
    arena_dump(a);

    int p = dequeue(a, &q);
    printf("Memproses Peserta ID: %d\n", p);

    printf("State after one customer is served:\n");
    arena_dump(a);
}
