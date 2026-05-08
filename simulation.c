#include "queue.h"
#include "simulation.h"
#include <stdio.h>

void run_simulation(Arena* a) {
    ArenaQueue q;
    queue_init(&q);

    printf("\n--- STARTING SIMULATION --- [cite: 49]\n");
    
    // Simulasi 3 job masuk
    enqueue(a, &q, 101);
    enqueue(a, &q, 102);
    enqueue(a, &q, 103);
    
    printf("Job 101, 102, 103 masuk antrean...\n");
    arena_dump(a); // Lihat kondisi memori setelah enqueue [cite: 15]

    // Simulasi job diproses
    int processed = dequeue(a, &q);
    printf("Processing Job ID: %d\n", processed);
    
    arena_dump(a); // Lihat kondisi setelah dequeue
}