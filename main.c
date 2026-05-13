#include "arena.h"
#include "simulation.h"
#include "evaluation.h"
#include <stdio.h>

void fase1_technical_stress(Arena *a) {
    printf("\n>>> PHASE 1: TECHNICAL STRESS TEST (Overflow Check) <<<\n");
    printf("Mencoba alokasi besar di arena kecil...\n");
    for (int i = 0; i < 3; i++) {
        size_t off = arena_alloc(a, 25);
        if (off != (size_t)-1) printf("Alokasi %d sukses di offset %zu\n", i+1, off);
        else printf("Alokasi %d GAGAL (Memori Penuh!)\n", i+1);
    }
    arena_dump(a);
}

int main() {
    printf("=== FINAL PROJECT: ARENA ALLOCATOR 2026 ===\n");

    // 1. Siapkan memori di STACK (0% Malloc)
    unsigned char memori_utama[1024]; 
    Arena myArena;
    arena_init_static(&myArena, memori_utama, 64); // Set kecil dulu buat Phase 1

    // FASE 1: Stress Test 
    fase1_technical_stress(&myArena);

    // FASE 2: Simulasi
    arena_reset(&myArena);
    myArena.capacity = 1024; // Perbesar kapasitas buat simulasi
    run_simulation(&myArena);

    // FASE 3: Benchmark (Minggu 4)
    run_performance_test();

    return 0;
}