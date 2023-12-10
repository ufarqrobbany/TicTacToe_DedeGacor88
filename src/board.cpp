#include "board.h"

#include <stdbool.h>
#include <stdio.h>

#include "common.h"

void InitPapan(int ukuran, int (*papan)[7][7]) {
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

void DisplayPapan(int ukuran, int papan[7][7], int selection) {
    int i, j, nomor, baris;

    baris = 14;
    nomor = 1;

    const char *dimensi_kosong;

    if (ukuran == 3) {
        dimensi_kosong = "                                   ";
    } else if (ukuran == 5) {
        dimensi_kosong = "                           ";
    } else {
        dimensi_kosong = "                   ";
    }

    // Tampilkan atas
    gotoxy(2, baris++);
    printf("%s%c", dimensi_kosong, 201);
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
            printf("%s%c", dimensi_kosong, 204);
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
        printf("%s%c", dimensi_kosong, 186);
        for (j = 1; j <= ukuran; j++) {
            printf("       %c", 186);
        }

        gotoxy(2, baris++);
        printf("%s%c", dimensi_kosong, 186);
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
        printf("%s%c", dimensi_kosong, 186);
        for (j = 0; j < ukuran; j++) {
            printf("       %c", 186);
        }
    }

    // Tampilkan bawah
    gotoxy(2, baris++);
    printf("%s%c", dimensi_kosong, 200);
    for (j = 1; j < ukuran * 8; j++) {
        if (j % 8 == 0) {
            printf("%c", 202);
        } else {
            printf("%c", 205);
        }
    }
    printf("%c", 188);

    gotoxy(1, baris + 4);
    printf("Gunakan tombol panah untuk navigasi. Tekan Enter untuk konfirmasi.");
}

bool CekSel(int letak, int ukuran, int papan[7][7]) {
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

void PutSimbol(int letak, int giliran, int ukuran, int (*papan)[7][7]) {
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

int CekPapan(int ukuran, int papan[7][7]) {
    int i, j, k, l, jml;
    bool menang;

    int syarat_menang = (ukuran == 7) ? 5 : ((ukuran == 5) ? 4 : ukuran);

    menang = false;
    // horizontal check
    for (i = 0; i < ukuran; i++) {
        jml = 0;
        for (j = 0; j < ukuran; j++) {
            k = papan[i][j];
            if (k != 0) {
                if (k == l) {
                    jml++;
                    if (jml == syarat_menang) {
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
    for (j = 0; j < ukuran; j++) {
        jml = 0;
        for (i = 0; i < ukuran; i++) {
            k = papan[i][j];
            if (k != 0) {
                if (k == l) {
                    jml++;
                    if (jml == syarat_menang) {
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

    // diagonal check (main diagonal)
    for (i = 0; i <= ukuran - syarat_menang; i++) {
        for (j = 0; j <= ukuran - syarat_menang; j++) {
            jml = 0;
            for (int d = 0; d < syarat_menang; d++) {
                k = papan[i + d][j + d];
                if (k != 0) {
                    if (k == l) {
                        jml++;
                        if (jml == syarat_menang) {
                            return k;  // mengembalikan pemain yang menang berdasarkan simbol/gilirannya
                        }
                    } else {
                        jml = 1;
                    }
                    l = k;
                } else {
                    jml = 0;
                }
            }
        }
    }

    // diagonal check (anti-diagonal)
    for (i = 0; i <= ukuran - syarat_menang; i++) {
        for (j = syarat_menang - 1; j < ukuran; j++) {
            jml = 0;
            for (int d = 0; d < syarat_menang; d++) {
                k = papan[i + d][j - d];
                if (k != 0) {
                    if (k == l) {
                        jml++;
                        if (jml == syarat_menang) {
                            return k;  // mengembalikan pemain yang menang berdasarkan simbol/gilirannya
                        }
                    } else {
                        jml = 1;
                    }
                    l = k;
                } else {
                    jml = 0;
                }
            }
        }
    }

    // cek seri
    int jml_petak = ukuran * ukuran;
    int sel_terisi = 0;

    for (i = 0; i < ukuran; i++) {
        for (j = 0; j < ukuran; j++) {
            if (papan[i][j] != 0) {
                sel_terisi++;
            }
        }
    }

    if (sel_terisi == jml_petak) {
        return -1;  // permainan seri
    }

    // Jika kondisi menang atau seri belum terpenuhi
    return 0;
}
