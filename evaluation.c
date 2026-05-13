#include "evaluation.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void run_performance_test() {
    const int iterations = 10000;
    clock_t start, end;
    
    printf("\n>>> PHASE 3: PERFORMANCE BENCHMARKING (%d iterations) <<<\n", iterations);

    // Arena Test
    unsigned char test_mem[100000];
    Arena testArena;
    arena_init_static(&testArena, test_mem, sizeof(test_mem));
    
    start = clock();
    for (int i = 0; i < iterations; i++) {
        arena_alloc(&testArena, 8);
        if (testArena.offset > 90000) arena_reset(&testArena);
    }
    end = clock();
    printf("Arena Time  : %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Malloc Test
    start = clock();
    for (int i = 0; i < iterations; i++) {
        void* p = malloc(8);
        free(p);
    }
    end = clock();
    printf("Malloc Time : %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}