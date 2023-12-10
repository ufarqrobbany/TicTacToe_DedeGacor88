#include "score.h"

#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "common.h"
#include "menu.h"

void FileName(int ukuran, int level, char (*mode)[6], char (*t_level)[6]) {
    strcpy((*mode), "comp");
    if (level == 1) {
        strcpy((*t_level), "_easy");
    } else if (level == 2) {
        strcpy((*t_level), "_medi");
    } else if (level == 3) {
        strcpy((*t_level), "_hard");
    } else {
        strcpy((*mode), "player");
        strcpy((*t_level), "");
    }
}

// add skor
void SaveSkor(int ukuran, int level, char waktu_mulai[22], char nama_p1[11], char nama_p2[11], char simbol_p1, char simbol_p2, int skor_p1, int skor_p2, char waktu_selesai[22]) {
    FILE *data;
    char mode[6], t_level[6], file_s[50];

    FileName(ukuran, level, &mode, &t_level);
    sprintf(file_s, "data/scores/%s_%dx%d%s.txt", mode, ukuran, ukuran, t_level);

    data = fopen(file_s, "a");
    fprintf(data, "%s#%s (%c)#%s (%c)#%d#%d#%s\n", waktu_mulai, nama_p1, simbol_p1, nama_p2, simbol_p2, skor_p1, skor_p2, waktu_selesai);
    fclose(data);
}
// get high score

int PilihUPSkor() {
    ClearScreen();

    int jml_opsi, selection;
    char menu[30];

    jml_opsi = 3;
    strcpy(menu, "LIHAT SKOR PADA UKURAN PAPAN...");

    char opsi[jml_opsi][20];
    strcpy(opsi[0], "3 x 3");
    strcpy(opsi[1], "5 x 5");
    strcpy(opsi[2], "7 x 7");

    selection = MenuOpsi(menu, jml_opsi, opsi, true);

    if (selection != 0) {
        return selection;
    } else {
        return -1;
    }
}

int PilihModeSkor() {
    ClearScreen();

    int jml_opsi, selection;
    char menu[30];

    jml_opsi = 2;
    strcpy(menu, "LIHAT SKOR PADA MODE BERMAIN...");

    char opsi[jml_opsi][20];
    strcpy(opsi[0], "Player vs Computer");
    strcpy(opsi[1], "Player vs Player");

    selection = MenuOpsi(menu, jml_opsi, opsi, true);

    if (selection != 0) {
        return selection;
    } else {
        return -1;
    }
}

int PilihLevelSkor() {
    ClearScreen();

    int jml_opsi, selection;
    char menu[30];

    jml_opsi = 3;
    strcpy(menu, "LIHAT SKOR PADA LEVEL...");

    char opsi[jml_opsi][20];
    strcpy(opsi[0], "Easy");
    strcpy(opsi[1], "Medium");
    strcpy(opsi[2], "Hard");

    selection = MenuOpsi(menu, jml_opsi, opsi, true);

    if (selection != 0) {
        return selection;
    } else {
        return -1;
    }
}

void PrintTabelSkor(int x, int *y, char file[30], char nama_tabel[50]) {
    int i, skor_1, skor_2, jml_data, valid;
    char w_mulai[22], w_selesai[22], pemain_1[15], pemain_2[15], pemain[32];
    FILE *data;

    // print nama tabel
    gotoxy(x, (*y)++);
    printf(nama_tabel);

    // print header tabel
    gotoxy(x, (*y)++);
    printf("%c", 201);
    for (i = 0; i < 23; i++) printf("%c", 205);
    printf("%c", 203);
    for (i = 0; i < 34; i++) printf("%c", 205);
    printf("%c", 203);
    for (i = 0; i < 15; i++) printf("%c", 205);
    printf("%c", 203);
    for (i = 0; i < 23; i++) printf("%c", 205);
    printf("%c", 187);

    gotoxy(x, (*y)++);
    printf("%c      Waktu Mulai      %c              Pemain              %c      Skor     %c     Waktu Selesai     %c", 186, 186, 186, 186, 186);

    gotoxy(x, (*y)++);
    printf("%c", 204);
    for (i = 0; i < 23; i++) printf("%c", 205);
    printf("%c", 206);
    for (i = 0; i < 34; i++) printf("%c", 205);
    printf("%c", 206);
    for (i = 0; i < 15; i++) printf("%c", 205);
    printf("%c", 206);
    for (i = 0; i < 23; i++) printf("%c", 205);
    printf("%c", 185);

    // print data
    data = fopen(file, "r");

    jml_data = 0;
    if (data != NULL) {
        while (!feof(data) && (jml_data < 30)) {
            valid = fscanf(data, "%[^#]#%[^#]#%[^#]#%d#%d#%[^\n]\n", w_mulai, pemain_1, pemain_2, &skor_1, &skor_2, w_selesai);
            if (valid == 6) {
                // print waktu mulai
                gotoxy(x, *y);
                printf("%c %-21s %c", 186, w_mulai, 186);
                // print nama pemain dan simbolnya
                printf(" %s vs %s ", pemain_1, pemain_2);
                // print skor
                gotoxy(x + 59, *y);
                printf("%c %d - %d", 186, skor_1, skor_2);
                // print waktu selesai
                gotoxy(x + 75, *y);
                printf("%c %-21s %c", 186, w_selesai, 186);
                (*y)++;
                jml_data++;
            }
        }
        fclose(data);
    } else {
        gotoxy(x, (*y) + 1);
        printf("Tidak ada file");
    }

    // print penutup tabel
    gotoxy(x, (*y)++);
    printf("%c", 200);
    for (i = 0; i < 23; i++) printf("%c", 205);
    printf("%c", 202);
    for (i = 0; i < 34; i++) printf("%c", 205);
    printf("%c", 202);
    for (i = 0; i < 15; i++) printf("%c", 205);
    printf("%c", 202);
    for (i = 0; i < 23; i++) printf("%c", 205);
    printf("%c", 188);
}

void DisplaySkor(int ukuran, int level) {
    ClearScreen();

    int x, y;
    int lebar = 94;
    char key, tabel[50], file_s[50], file_hs[50];
    char mode[6], t_level[6];

    FileName(ukuran, level, &mode, &t_level);

    sprintf(file_s, "data/scores/%s_%dx%d%s.txt", mode, ukuran, ukuran, t_level);
    sprintf(file_hs, "data/highscores/%s_%dx%d%s.txt", mode, ukuran, ukuran, t_level);

    printf("SKOR %d x %d, %s%s", ukuran, ukuran, (level == 4) ? "VS PLAYER" : "VS COMPUTER", (level == 1) ? ", EASY" : ((level == 2) ? ", MEDIUM" : ((level == 3) ? ", HARD" : "")));

    // print tabel
    x = 1;
    y = 3;
    strcpy(tabel, "SKOR TERTINGGI - TOP 3");
    PrintTabelSkor(x, &y, file_hs, tabel);
    y++;
    strcpy(tabel, "RIWAYAT SKOR (30 Permainan Terakhir)");
    PrintTabelSkor(x, &y, file_s, tabel);

    gotoxy(1, y + 1);
    printf("Tekan ESC untuk kembali...");

    do {
        key = getch();
    } while (key != 27);  // selama tidak menekan tombol ESC
}
