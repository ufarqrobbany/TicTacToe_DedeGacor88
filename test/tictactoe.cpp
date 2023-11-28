#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include <cstdlib>

int papan[7][7];
int giliran, giliranP1, giliranP2;

void menu_utama();
void mulai_main();
void pilih_mode();
void input_nama(int mode);
void pilih_level(int mode, char namaPlayer1[11], char namaPlayer2[11]);
void pilih_ukuran(int mode, char namaPlayer1[11], char namaPlayer2[11], int level);
void pilih_simbol(int mode, char namaPlayer1[11], char namaPlayer2[11], int level, int ukuran);
void inisialisasi_papan(int dimensi, int (*papan)[7][7]);
void print_papan(int dimensi, int papan[7][7]);
void menu_permainan(int mode, char namaPlayer1[11], char namaPlayer2[11], int level, int ukuran, int simbolP1);
void letakkan_simbol(int petak, int giliran, int dimensi, int (*papan)[7][7]);
void cek_papan();
void riwayat_skor();
void bantuan();
void kredit();

void print_header() {
}

void menu_utama() {
    int opsi = 0;
    bool valid;

    do {
        system("cls");
        printf("+------------------------------------------+ \n");
        printf("| %-14s%-12s %-13s | \n", "", "TIC TAC TOE", "");
        printf("| %-40s | \n", "DedeGacor88");
        printf("+------------------------------------------+ \n");
        printf("| %-14s %-10s %-14s | \n", "", "Menu Utama", "");
        printf("+------------------------------------------+ \n");
        printf("| %-40s | \n", "1. Mulai Permainan");
        printf("| %-40s | \n", "2. Riwayat Skor");
        printf("| %-40s | \n", "3. Bantuan");
        printf("| %-40s | \n", "4. Kredit");
        printf("| %-40s | \n", "5. Keluar");
        printf("+------------------------------------------+ \n");
        printf("Pilih: ");
        scanf("%d", &opsi);

        switch (opsi) {
            case 1:
                valid = true;
                mulai_main();
                break;
            case 2:
                valid = true;
                riwayat_skor();
                break;
            case 3:
                valid = true;
                bantuan();
                break;
            case 4:
                valid = true;
                kredit();
                break;
            case 5:
                valid = true;
                break;
            default:
                valid = false;
        }
    } while (!valid);
}

void pilih_mode() {
    int opsi;
    bool valid;

    do {
        system("cls");
        printf("+------------------------------------------+ \n");
        printf("| %-14s%-12s %-13s | \n", "", "TIC TAC TOE", "");
        printf("| %-40s | \n", "DedeGacor88");
        printf("+------------------------------------------+ \n");
        printf("| %-10s %-18s %-10s | \n", "", "Pilih Mode Bermain", "");
        printf("+------------------------------------------+ \n");
        printf("| %-40s | \n", "1. Player vs Player");
        printf("| %-40s | \n", "2. Player vs Computer");
        printf("| %-40s | \n", "3. Kembali");
        printf("+------------------------------------------+ \n");
        printf("Pilih: ");

        scanf("%d", &opsi);
        printf("");

        if (opsi == 1 || opsi == 2) {
            valid = true;
            input_nama(opsi);
        } else if (opsi == 3) {
            valid = true;
            menu_utama();
        } else {
            valid = false;
        }
    } while (!valid);
}

void input_nama(int mode) {
    char namaP1[11], namaP2[11], namaPlayer1[11], namaPlayer2[11];
    int i;

    do {
        system("cls");
        printf("+------------------------------------------+ \n");
        printf("| %-14s%-12s %-13s |\n", "", "TIC TAC TOE", "");
        printf("| %-40s | \n", "DedeGacor88");
        printf("+------------------------------------------+ \n");
        printf("| %-13s%-13s %-13s | \n", "", "Masukkan Nama", "");
        printf("+------------------------------------------+ \n");
        printf("| %-40s | \n", "Player 1: ____________________");
        printf("+------------------------------------------+ \n");
        printf("Input: ");
        scanf(" %[^\n]s", &namaP1);
        printf("");

        if (strlen(namaP1) > 10) {
            printf("Nama player 1 melebihi batas maksimal (10 karakter), Silakan ulangi...");
            _getch();
        }
    } while (strlen(namaP1) > 10);

    i = 0;
    while (i <= strlen(namaP1)) {
        namaPlayer1[i] = namaP1[i];
        i++;
    }

    if (mode == 1) {
        do {
            system("cls");
            printf("+------------------------------------------+ \n");
            printf("| %-14s%-12s %-13s |\n", "", "TIC TAC TOE", "");
            printf("| %-40s | \n", "DedeGacor88");
            printf("+------------------------------------------+ \n");
            printf("| %-13s%-13s %-13s | \n", "", "Masukkan Nama", "");
            printf("+------------------------------------------+ \n");
            printf("| %-9s %-30s | \n", "Player 1:", namaPlayer1);
            printf("| %-40s | \n", "Player 2: ____________________");
            printf("+------------------------------------------+ \n");
            printf("Input: ");
            scanf(" %[^\n]s", &namaP2);
            printf("");

            if (strlen(namaP2) > 10) {
                printf("Nama player 2 melebihi batas maksimal (10 karakter), Silakan ulangi...");
                _getch();
            }
        } while (strlen(namaP2) > 10);

        i = 0;
        while (i <= strlen(namaP2)) {
            namaPlayer2[i] = namaP2[i];
            i++;
        }

        pilih_ukuran(mode, namaPlayer1, namaPlayer2, 0);
    } else {
        pilih_level(mode, namaPlayer1, '\0');
    }
}

void pilih_level(int mode, char namaPlayer1[11], char namaPlayer2[11]) {
    int opsi = 0;
    bool valid;

    do {
        system("cls");
        printf("+------------------------------------------+ \n");
        printf("| %-14s%-12s %-13s | \n", "", "TIC TAC TOE", "");
        printf("| %-40s | \n", "DedeGacor88");
        printf("+------------------------------------------+ \n");
        printf("| %-8s%-23s %-8s | \n", "", "Pilih Tingkat Kesulitan", "");
        printf("+------------------------------------------+ \n");
        printf("| %-40s | \n", "1. Easy");
        printf("| %-40s | \n", "2. Normal");
        printf("| %-40s | \n", "3. Hard");
        printf("| %-40s | \n", "4. Kembali");
        printf("+------------------------------------------+ \n");
        printf("Pilih: ");
        scanf("%d", &opsi);
        printf("");

        if (opsi == 1 || opsi == 2 || opsi == 3) {
            valid = true;
            pilih_ukuran(mode, namaPlayer1, namaPlayer2, opsi);
        } else if (opsi == 4) {
            valid = false;
            input_nama(mode);
            break;
        } else {
            valid = false;
        }
    } while (!valid);
}

void pilih_ukuran(int mode, char namaPlayer1[11], char namaPlayer2[11], int level) {
    int opsi = 0;
    bool valid;

    do {
        system("cls");
        printf("+------------------------------------------+ \n");
        printf("| %-14s%-12s %-13s | \n", "", "TIC TAC TOE", "");
        printf("| %-40s | \n", "DedeGacor88");
        printf("+------------------------------------------+ \n");
        printf("| %-10s %-18s %-10s | \n", "", "Pilih Ukuran Papan", "");
        printf("+------------------------------------------+ \n");
        printf("| %-40s | \n", "1. 3x3");
        printf("| %-40s | \n", "2. 5x5");
        printf("| %-40s | \n", "3. 7x7");
        printf("| %-40s | \n", "4. Kembali");
        printf("+------------------------------------------+ \n");
        printf("Pilih: ");
        scanf("%d", &opsi);
        printf("");

        if (opsi == 1 || opsi == 2 || opsi == 3) {
            valid = true;
            pilih_simbol(mode, namaPlayer1, namaPlayer2, level, opsi);
        } else if (opsi == 4) {
            valid = false;
            if (mode == 1) {
                input_nama(mode);
            } else {
                pilih_level(mode, namaPlayer1, namaPlayer2);
            }
            break;
        } else {
            valid = false;
        }
    } while (!valid);
}

void pilih_simbol(int mode, char namaPlayer1[11], char namaPlayer2[11], int level, int ukuran) {
    int opsi;
    bool valid;

    do {
        system("cls");
        printf("+------------------------------------------+ \n");
        printf("| %-14s%-12s %-13s | \n", "", "TIC TAC TOE", "");
        printf("| %-40s | \n", "DedeGacor88");
        printf("+------------------------------------------+ \n");
        printf("| %-10s %-18s %-10s | \n", "", "Pilih Simbol Bidak", "");
        printf("+------------------------------------------+ \n");
        printf("| %-9s %-30s | \n", "Player 1:", namaPlayer1);
        printf("| %-40s | \n", "1. X");
        printf("| %-40s | \n", "2. O");
        printf("| %-40s | \n", "3. Kembali");
        printf("+------------------------------------------+ \n");
        printf("Pilih: ");
        scanf("%d", &opsi);
        printf("");

        if (opsi == 1 || opsi == 2) {
            valid = true;
            menu_permainan(mode, namaPlayer1, namaPlayer2, level, ukuran, opsi);
        } else if (opsi == 3) {
            valid = false;
            pilih_ukuran(mode, namaPlayer1, namaPlayer2, level);
        } else {
            valid = false;
        }
    } while (!valid);
}

void inisialisasi_papan(int dimensi, int (*papan)[7][7]) {
    int baris, kolom;
    baris = 0;

    while (baris < dimensi) {
        kolom = 0;
        while (kolom < dimensi) {
            (*papan)[baris][kolom] = 0;
            kolom++;
        }
        baris++;
    }
}

void print_papan(int dimensi, int papan[7][7]) {
    int baris, kolom, nomor;

    nomor = 1;
    baris = 0;

    const char *dimensiKosong;
    const char *dimensiKosongAkhir;

    if (dimensi == 3) {
        dimensiKosong = "                   ";
        dimensiKosongAkhir = "                  ";
    } else if (dimensi == 5) {
        dimensiKosong = "           ";
        dimensiKosongAkhir = "          ";
    } else {
        dimensiKosong = "   ";
        dimensiKosongAkhir = "  ";
    }

    while (baris < dimensi) {
        // Tampilkan garis horizontal pemisah antar baris
        printf("|%s", dimensiKosong);
        for (int i = 0; i < dimensi * 8 + 1; i++) {
            if (i == 0 || i == dimensi * 8 || i % 8 == 0) {
                printf("+");
            } else {
                printf("-");
            }
        }
        printf("%s|", dimensiKosong);
        printf("\n");

        kolom = 0;
        printf("|%s", dimensiKosong);
        printf("|");
        while (kolom < dimensi) {
            printf(" %-5s |", "");
            kolom++;
        }
        printf("%s|", dimensiKosong);
        printf("\n");

        kolom = 0;
        printf("|%s", dimensiKosong);
        printf("| ");
        while (kolom < dimensi) {
            if (papan[baris][kolom] == 0) {
                printf("  %-2d  | ", nomor);
            } else if (papan[baris][kolom] == 1) {
                printf("  \033[0;31m%c\033[0m   | ", 'X');
            } else {
                printf("  \033[0;32m%c\033[0m   | ", 'O');
            }
            nomor++;
            kolom++;
        }
        printf("%s|", dimensiKosongAkhir);
        printf("\n");

        kolom = 0;
        printf("|%s", dimensiKosong);
        printf("|");
        while (kolom < dimensi) {
            printf(" %-5s |", "");
            kolom++;
        }
        printf("%s|", dimensiKosong);
        printf("\n");

        baris++;
    }

    // Tampilkan garis horizontal pemisah terakhir
    printf("|%s", dimensiKosong);
    for (int i = 0; i < dimensi * 8 + 1; i++) {
        if (i == 0 || i == dimensi * 8 || i % 8 == 0) {
            printf("+");
        } else {
            printf("-");
        }
    }
    printf("%s|\n", dimensiKosong);
}

void menu_permainan(int mode, char namaPlayer1[11], char namaPlayer2[11], int level, int ukuran, int simbolP1) {
    int dimensi, pilih;
    char simbolPlayer1, simbolPlayer2;

    if (ukuran == 1) {
        dimensi = 3;
    } else if (ukuran == 2) {
        dimensi = 5;
    } else {
        dimensi = 7;
    }

    if (simbolP1 == 1) {
        giliranP1 = 1;
        giliranP2 = 2;
        giliran = giliranP1;
        simbolPlayer1 = 'X';
        simbolPlayer2 = 'O';
    } else {
        giliranP1 = 2;
        giliranP2 = 1;
        giliran = giliranP2;
        simbolPlayer1 = 'O';
        simbolPlayer2 = 'X';
    }

    inisialisasi_papan(dimensi, &papan);

    do {
        system("cls");
        printf("+---------------------------------------------------------------+ \n");
        printf("| %-24s%-12s %-24s | \n", "", "TIC TAC TOE", "");
        printf("| %-11s %-49s | \n", "DedeGacor88", "");
        printf("+---------------------------------------------------------------+ \n");
        printf("| %-20s %-19s %-20s | \n", "", "Game On, Good Luck!", "");
        printf("+---------------------------------------------------------------+ \n");
        if (giliran == giliranP1) {
            printf("| Giliran: %-10s (%c) %-16s Sisa Waktu: %-2d Detik |\n", namaPlayer1, simbolPlayer1, "", 10);
        } else if ((giliran == giliranP2) && (mode == 2)) {
            printf("| Giliran: Computer (%c) %-16s Sisa Waktu: %-2d Detik |\n", simbolPlayer2, "", 10);
        } else {
            printf("| Giliran: %-10s (%c) %-16s Sisa Waktu: %-2d Detik |\n", namaPlayer2, simbolPlayer2, "", 10);
        }
        printf("| %-61s | \n", "");
        print_papan(dimensi, papan);
        printf("| %-61s | \n", "");
        printf("+---------------------------------------------------------------+ \n");
        if ((giliran == giliranP1) || ((giliran == giliranP2) && (mode == 1))) {
            printf("Pilih: ");
            scanf("%d", &pilih);
            printf("");
        } else {
            printf("Tunggu...");
            system("pause");
        }

        letakkan_simbol(pilih, giliran, dimensi, &papan);

        if (giliran == 1) {
            giliran = 2;
        } else {
            giliran = 1;
        }
    } while (true);
}

void letakkan_simbol(int petak, int giliran, int dimensi, int (*papan)[7][7]) {
    int baris, kolom, i;
    i = 1;
    baris = 0;
    while (baris < dimensi) {
        kolom = 0;
        while (kolom < dimensi) {
            if ((i == petak) && ((*papan)[baris][kolom] == 0)) {
                (*papan)[baris][kolom] = giliran;
            }
            i++;
            kolom++;
        }
        baris++;
    }
}

void mulai_main() {
    system("cls");
    pilih_mode();
}

void riwayat_skor() {
    system("cls");
    printf("______________________ \n \n");
    printf("Riwayat Skor \n");
    printf("______________________ \n \n");
    system("pause");
    menu_utama();
}

void bantuan() {
    system("cls");
    printf("______________________ \n \n");
    printf("Bantuan \n");
    printf("______________________ \n \n");
    system("pause");
    menu_utama();
}

void kredit() {
    system("cls");
    printf("+------------------------------------------+ \n");
    printf("| %-14s%-12s %-13s | \n", "", "TIC TAC TOE", "");
    printf("| %-40s | \n", "DedeGacor88");
    printf("+------------------------------------------+ \n");
    printf("| %-16s %-6s %-16s | \n", "", "Kredit", "");
    printf("+------------------------------------------+ \n");
    printf("| %-40s | \n", "Author:");
    printf("| %-40s | \n", "Jizdan Mulkan Nailan (2315240)");
    printf("| %-40s | \n", "Muhammad Aslim Salman (2315240)");
    printf("| %-40s | \n", "Umar Faruq Robbany (2315240)");
    printf("| %-40s | \n", "");
    printf("| %-40s | \n", "Jurusan Teknik Komputer dan Informatika");
    printf("| %-40s | \n", "Program Studi D-IV Teknik Informatika");
    printf("| %-40s | \n", "Politeknik Negeri Bandung");
    printf("| %-40s | \n", "2023");
    printf("+------------------------------------------+ \n");
    system("pause");
    menu_utama();
}

int main() {
    menu_utama();
    return 0;
}
