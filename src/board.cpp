#include "board.h"

#include <stdbool.h>
#include <stdio.h>

#include "common.h"

void init_papan(int ukuran, int (*papan)[7][7]) {
    int baris, kolom;
    baris = 0;

    while (baris < ukuran) {
        kolom = 0;
        while (kolom < ukuran) {
            (*papan)[baris][kolom] = 0;
            kolom++;
        }
        baris++;
    }
}

void display_papan(int ukuran, int papan[7][7], int selection) {
    int i, j, nomor;
    int baris = 14;
    int nBaris = 1;
    int nKolom = 1;
    nomor = 1;

    const char *dimensiKosong;

    if (ukuran == 3) {
        dimensiKosong = "                                   ";
    } else if (ukuran == 5) {
        dimensiKosong = "                           ";
    } else {
        dimensiKosong = "           ";
    }

    // Tampilkan atas
    gotoxy(2, baris++);
    printf("%s%c", dimensiKosong, 201);
    for (j = 1; j < ukuran * 8; j++) {
        if (j % 8 == 0) {
            printf("%c", 203);
        } else {
            printf("%c", 205);
        }
    }
    printf("%c", 187);

    for (i = 0; i < ukuran; i++) {
        if (i != 0) {
            gotoxy(2, baris++);
            printf("%s%c", dimensiKosong, 204);
            for (j = 1; j < ukuran * 8; j++) {
                if (j % 8 == 0) {
                    printf("%c", 206);
                } else {
                    printf("%c", 205);
                }
            }
            printf("%c", 185);
        }

        gotoxy(2, baris++);
        printf("%s%c", dimensiKosong, 186);
        for (j = 1; j <= ukuran; j++) {
            printf("       %c", 186);
        }

        gotoxy(2, baris++);
        printf("%s%c", dimensiKosong, 186);
        for (j = 0; j < ukuran; j++) {
            if (selection == nomor) printf("\033[48;5;33m");
            if (papan[i][j] == 0) {
                printf("       ");
            } else if (papan[i][j] == 1) {
                if (selection == nomor) {
                    printf("   %c   ", 'X');
                } else {
                    printf("   \033[0;31m%c\033[0m   ", 'X');
                }
            } else {
                if (selection == nomor) {
                    printf("   %c   ", 'O');
                } else {
                    printf("   \033[0;32m%c\033[0m   ", 'O');
                }
            }
            if (selection == nomor) printf("\033[0m");
            printf("%c", 186);
            nomor++;
        }

        gotoxy(2, baris++);
        printf("%s%c", dimensiKosong, 186);
        for (j = 0; j < ukuran; j++) {
            printf("       %c", 186);
        }

        nBaris++;
    }

    // Tampilkan bawah
    gotoxy(2, baris++);
    printf("%s%c", dimensiKosong, 200);
    for (j = 1; j < ukuran * 8; j++) {
        if (j % 8 == 0) {
            printf("%c", 202);
        } else {
            printf("%c", 205);
        }
    }
    printf("%c", 188);

    gotoxy(4, (baris++) + 1);
    printf("Letakkan simbol pada petak yang kosong dalam waktu kurang dari 10 detik.");

    gotoxy(1, baris + 3);
    printf("Gunakan tombol panah untuk navigasi. Tekan Enter untuk konfirmasi.");
}

bool cek_sel(int letak, int ukuran, int papan[7][7]) {
    int baris, kolom, i, zero;
    i = 1;
    baris = 0;
    zero = false;
    while (baris < ukuran) {
        kolom = 0;
        while (kolom < ukuran) {
            if ((i == letak) && (papan[baris][kolom] == 0)) {
                zero = true;
                break;
            }
            i++;
            kolom++;
        }
        baris++;
    }
    return zero;
}

void put_simbol(int letak, int giliran, int ukuran, int (*papan)[7][7]) {
    int baris, kolom, i;
    i = 1;
    baris = 0;
    while (baris < ukuran) {
        kolom = 0;
        while (kolom < ukuran) {
            if ((i == letak)) {
                (*papan)[baris][kolom] = giliran;
            }
            i++;
            kolom++;
        }
        baris++;
    }
}

int cek_papan(int ukuran, int papan[7][7]) {
    int i, j, k, l, jml;
    bool menang;

    int sMenang = (ukuran == 7) ? 5 : ((ukuran == 5) ? 4 : ukuran);

    menang = false;
    // horizontal check
    for (i = 0; i < ukuran; i++) {
        jml = 0;
        for (j = 0; j < ukuran; j++) {
            k = papan[i][j];
            if (k != 0) {
                if (k == l) {
                    jml++;
                    if (jml == sMenang) {
                        menang = true;
                        break;
                    }
                } else {
                    jml = 1;
                }
                l = k;
            } else {
                jml = 0;
            }
        }
        if (menang) {
            return k;  // mengembalikan pemain yang menang berdasarkan simbol/gilirannya
        }
    }

    // vertical check

    // diagonal check

    // cek seri
    int totalMoves = ukuran * ukuran;
    int filledCells = 0;

    for (i = 0; i < ukuran; i++) {
        for (j = 0; j < ukuran; j++) {
            if (papan[i][j] != 0) {
                filledCells++;
            }
        }
    }

    if (filledCells == totalMoves) {
        return -1;  // permainan seri
    }

    // Jika kondisi menang atau seri belum terpenuhi
    return 0;
}
