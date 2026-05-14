#include "arena.h"
#include "queue.h"
#include "simulation.h"
#include "evaluation.h"
#include <stdio.h>
#include <stdlib.h>

void fase1_technical_stress(Arena *a) {
    printf("\n>>> PHASE 1: TECHNICAL STRESS TEST (Overflow Check) <<<\n");
    printf("Mencoba alokasi besar di arena kecil...\n");
    
    // Simpan kapasitas asli, lalu kecilkan sementara untuk test
    size_t kapasitas_asli = a->capacity;
    a->capacity = 1024; 
    arena_reset(a); // Kosongkan sebelum test

    for (int i = 0; i < 50; i++) {
        size_t off = arena_alloc(a, 25);
        if (off != (size_t)-1) printf("Alokasi %d sukses di offset %zu\n", i+1, off);
        else printf("Alokasi %d GAGAL (Memori Penuh!)\n", i+1);
    }
    arena_dump(a);

    // Kembalikan ke kapasitas semula setelah test selesai
    a->capacity = kapasitas_asli;
    arena_reset(a);
}

void tampilkan_menu() {
    printf("\n==================================================\n");
    printf("   FINAL PROJECT: ARENA ALLOCATOR INTERAKTIF 2026 \n");
    printf("==================================================\n");
    printf("   [ PENGUJIAN MANUAL ]\n");
    printf("1. Alokasi Memori Bebas (Custom Bytes)\n");
    printf("2. Masukkan Data ke Antrean (Enqueue)\n");
    printf("3. Proses Data Antrean (Dequeue)\n");
    printf("4. Lihat Visualisasi Memori (Arena Dump)\n");
    printf("5. Kosongkan Memori & Antrean (Reset O(1))\n");
    printf("\n   [ PENGUJIAN OTOMATIS (FASE) ]\n");
    printf("6. Jalankan Fase 1: Stress Test (Overflow Check)\n");
    printf("7. Jalankan Fase 2: Simulasi Antrean Otomatis\n");
    printf("8. Jalankan Fase 3: Benchmark Performa vs Malloc\n");
    printf("\n9. Keluar Program\n");
    printf("--------------------------------------------------\n");
    printf("Pilih aksi (1-9): ");
}

int main() {
    // 1. Siapkan memori di STACK sebesar 1024 bytes (0% Malloc)
    unsigned char memori_utama[1024]; 
    
    // 2. Inisialisasi Arena
    Arena myArena;
    arena_init_static(&myArena, memori_utama, sizeof(memori_utama)); 

    // 3. Inisialisasi Antrean (Queue) untuk pengujian manual
    ArenaQueue myQueue;
    queue_init(&myQueue);

    int pilihan;

    while (1) {
        tampilkan_menu();
        
        if (scanf("%d", &pilihan) != 1) {
            while(getchar() != '\n'); // Bersihkan input sampah
            printf(">> ERROR: Mohon masukkan angka yang valid!\n");
            continue;
        }

        printf("\n");

        switch (pilihan) {
            case 1: {
                size_t ukuran;
                printf("Berapa bytes yang ingin dialokasikan? : ");
                scanf("%zu", &ukuran);
                size_t off = arena_alloc(&myArena, ukuran);
                if (off != (size_t)-1) {
                    printf(">> BERHASIL: %zu bytes dipesan pada offset %zu.\n", ukuran, off);
                } else {
                    printf(">> GAGAL: Memori Arena penuh!\n");
                }
                break;
            }
            case 2: {
                int nilai;
                printf("Masukkan nomor tiket pelanggan (Angka) : ");
                scanf("%d", &nilai);
                size_t offset_sebelum = myArena.offset;
                enqueue(&myArena, &myQueue, nilai);
                if (myArena.offset > offset_sebelum) {
                    printf(">> BERHASIL: Pelanggan [%d] masuk antrean.\n", nilai);
                } else {
                    printf(">> GAGAL: Memori penuh, tidak bisa menambah antrean.\n");
                }
                break;
            }
            case 3: {
                int diproses = dequeue(&myArena, &myQueue);
                if (diproses != -1) {
                    printf(">> BERHASIL: Pelanggan [%d] selesai dilayani.\n", diproses);
                } else {
                    printf(">> GAGAL: Antrean saat ini sedang kosong!\n");
                }
                break;
            }
            case 4: {
                printf("--- VISUALISASI MEMORI SAAT INI ---\n");
                arena_dump(&myArena);
                break;
            }
            case 5: {
                arena_reset(&myArena);
                queue_init(&myQueue); 
                printf(">> BERHASIL: Memori kembali kosong secara instan (O(1)).\n");
                break;
            }
            case 6: {
                fase1_technical_stress(&myArena);
                // Reset queue karena memori baru saja diacak-acak oleh stress test
                queue_init(&myQueue); 
                break;
            }
            case 7: {
                run_simulation(&myArena);
                break;
            }
            case 8: {
                // Memanggil file evaluation.c untuk membandingkan kecepatan
                run_performance_test();
                break;
            }
            case 9: {
                printf("Terima kasih telah menggunakan Arena Allocator!\n");
                return 0; // Keluar dari program
            }
            default: {
                printf(">> Pilihan tidak dikenali. Silakan pilih 1 sampai 9.\n");
            }
        }
    }
    return 0;
}