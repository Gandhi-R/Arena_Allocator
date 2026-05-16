#include "arena.h"
#include "queue.h"
#include "simulation.h"
#include "evaluation.h"
#include <stdio.h>
#include <stdlib.h>

void fase1_technical_stress(Arena *a)
{
    printf("\n>>> PHASE 1: TECHNICAL STRESS TEST (Overflow Check) <<<\n");
    printf("Mencoba alokasi besar di arena kecil...\n");

    int i = 1;
    while (1)
    {
        // Melakukan alokasi chunks kecil berukuran 32 bytes sampai arena benar-benar penuh
        size_t off = arena_alloc(a, 32);
        if (off != (size_t)-1)
        {
            printf("Alokasi blok %d sukses di offset %zu (Sisa: %zu/%zu bytes)\n", i, off, a->offset, a->capacity);
            i++;
        }
        else
        {
            printf("\n>> [OVERFLOW NOTICE]: Alokasi blok ke-%d GAGAL! Arena sekarang benar-benar PENUH!\n", i);
            break;
        }
    }
    arena_dump(a);
    printf("Peringatan: Memori telah dikuras habis oleh Stress Test! Jalankan Menu 5 jika ingin mengosongkan kembali.\n");
}

void tampilkan_menu()
{
    printf("\n==================================================\n");
    printf("    FINAL PROJECT: ARENA ALLOCATOR INTERAKTIF 2026 \n");
    printf("==================================================\n");
    printf("    [ PENGUJIAN MANUAL ]\n");
    printf("1. Alokasi Memori Bebas (Custom Bytes)\n");
    printf("2. Masukkan Data ke Antrean (Enqueue)\n");
    printf("3. Proses Data Antrean (Dequeue)\n");
    printf("4. Hapus ID Tertentu dari Antrean (Delete ID)\n"); // MENU BARU
    printf("5. Lihat Visualisasi Memori (Arena Dump)\n");
    printf("6. Kosongkan Memori & Antrean (Reset O(1))\n");
    printf("\n    [ PENGUJIAN OTOMATIS (FASE) ]\n");
    printf("7. Jalankan Fase 1: Stress Test (Exhaust Memori)\n");
    printf("8. Jalankan Fase 2: Simulasi Antrean Otomatis\n");
    printf("9. Jalankan Fase 3: Benchmark Performa vs Malloc\n");
    printf("\n10. Keluar Program\n");
    printf("--------------------------------------------------\n");
    printf("Pilih aksi (1-10): ");
}

int main()
{
    // 1. Siapkan memori di STACK sebesar 1024 bytes (0% Malloc)
    unsigned char memori_utama[1024];

    // 2. Inisialisasi Arena
    Arena myArena;
    arena_init_static(&myArena, memori_utama, sizeof(memori_utama));

    // 3. Inisialisasi Antrean (Queue) untuk pengujian manual
    ArenaQueue myQueue;
    queue_init(&myQueue);

    int pilihan;

    while (1)
    {
        tampilkan_menu();

        if (scanf("%d", &pilihan) != 1)
        {
            while (getchar() != '\n')
                ; // Bersihkan input sampah
            printf(">> ERROR: Mohon masukkan angka yang valid!\n");
            continue;
        }

        printf("\n");

        switch (pilihan)
        {
        case 1:
        {
            size_t ukuran;
            printf("Berapa bytes yang ingin dialokasikan? : ");
            scanf("%zu", &ukuran);
            size_t off = arena_alloc(&myArena, ukuran);
            if (off != (size_t)-1)
            {
                printf(">> BERHASIL: %zu bytes dipesan pada offset %zu.\n", ukuran, off);
            }
            else
            {
                printf(">> GAGAL: Memori Arena penuh!\n");
            }
            break;
        }
        case 2:
        {
            if (myArena.offset + sizeof(QueueNode) > myArena.capacity)
            {
                printf(">> GAGAL: Arena sudah PENUH (%zu/%zu bytes digunakan)!\n", myArena.offset, myArena.capacity);
                printf(">> Anda tidak bisa menambahkan antrean. Silakan jalankan Menu 6 (Reset) terlebih dahulu.\n");
                break;
            }

            int nilai;
            printf("Masukkan nomor tiket pelanggan (Angka) : ");
            scanf("%d", &nilai);

            enqueue(&myArena, &myQueue, nilai);
            printf(">> BERHASIL: Pelanggan [%d] masuk antrean.\n", nilai);
            break;
        }

        case 3:
        {
            int diproses = dequeue(&myArena, &myQueue);
            if (diproses != -1)
            {
                printf(">> BERHASIL: Pelanggan [%d] selesai dilayani.\n", diproses);
            }
            else
            {
                printf(">> GAGAL: Antrean saat ini sedang kosong!\n");
            }
            break;
        }

        case 4:
        {
            if (myQueue.head_offset == -1)
            {
                printf(">> GAGAL: Antrean kosong, tidak ada ID yang bisa dihapus.\n");
                break;
            }
            int target_id;
            printf("Masukkan ID pelanggan yang ingin dihapus: ");
            scanf("%d", &target_id);

            if (queue_delete_id(&myArena, &myQueue, target_id))
            {
                printf(">> BERHASIL: Pelanggan dengan ID [%d] telah dihapus dari antrean.\n", target_id);
            }
            else
            {
                printf(">> GAGAL: ID [%d] tidak ditemukan dalam antrean!\n", target_id);
            }
            break;
        }

        case 5:
        {
            printf("--- VISUALISASI MEMORI SAAT INI ---\n");
            arena_dump(&myArena);
            break;
        }
        case 6:
        {
            arena_reset(&myArena);
            queue_init(&myQueue);
            printf(">> BERHASIL: Memori kembali kosong secara instan (O(1)).\n");
            break;
        }
        case 7:
        {
            fase1_technical_stress(&myArena);
            // Reset queue karena memori baru saja diacak-acak oleh stress test
            queue_init(&myQueue);
            break;
        }
        case 8:
        {
            run_simulation(&myArena, &myQueue);
            break;
        }
        case 9:
        {
            // Memanggil file evaluation.c untuk membandingkan kecepatan
            run_performance_test();
            break;
        }
        case 10:
        {
            printf("Terima kasih telah menggunakan Arena Allocator!\n");
            return 0; // Keluar dari program
        }
        default:
        {
            printf(">> Pilihan tidak dikenali. Silakan pilih 1 sampai 9.\n");
        }
        }
    }
    return 0;
}
