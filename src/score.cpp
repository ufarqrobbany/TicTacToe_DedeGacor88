#include "score.h"

#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "common.h"
#include "header.h"
#include "menu.h"

// add skor
// get high score

void print_tabel_skor(int x, int *y, char file[30], char title[50]) {
    int i, skor_1, skor_2, jml_data, valid;
    char w_mulai[22], w_selesai[22], pemain_1[15], pemain_2[15], pemain[32];
    FILE *data;

    // print nama tabel
    gotoxy(x, (*y)++);
    printf(title);

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

void display_skor(int ukuran) {
    clear_screen();

    int i, x, y, y2;
    int lebar = 94;
    char key, tabel[50], file_sc[50], file_sp[50], file_hsc[50], file_hsp[50];

    if (ukuran == 3) {
        printf("RIWAYAT SKOR 3 x 3");
        strcpy(file_sc, "data/scores/comp_3x3.txt");
        strcpy(file_sp, "data/scores/player_3x3.txt");
        strcpy(file_hsc, "data/highscores/comp_3x3.txt");
        strcpy(file_hsp, "data/highscores/player_3x3.txt");
    } else if (ukuran == 5) {
        printf("RIWAYAT SKOR 5 x 5");
        strcpy(file_sc, "data/scores/comp_5x5.txt");
        strcpy(file_sp, "data/scores/player_5x5.txt");
        strcpy(file_hsc, "data/highscores/comp_5x5.txt");
        strcpy(file_hsp, "data/highscores/player_5x5.txt");
    } else {
        printf("RIWAYAT SKOR 7 x 7");
        strcpy(file_sc, "data/scores/comp_7x7.txt");
        strcpy(file_sp, "data/scores/player_7x7.txt");
        strcpy(file_hsc, "data/highscores/comp_7x7.txt");
        strcpy(file_hsp, "data/highscores/player_7x7.txt");
    }

    // print tabel
    x = 1;
    y = 5;
    gotoxy(x, 3);
    printf("vs Computer");
    strcpy(tabel, "SKOR TERTINGGI - TOP 3");
    print_tabel_skor(x, &y, file_hsc, tabel);
    y++;
    strcpy(tabel, "RIWAYAT SKOR (30 Permainan Terakhir)");
    print_tabel_skor(x, &y, file_sc, tabel);

    x = 104;
    y2 = 5;
    gotoxy(x, 3);
    printf("vs Player");
    strcpy(tabel, "SKOR TERTINGGI - TOP 3");
    print_tabel_skor(x, &y2, file_hsp, tabel);
    y2++;
    strcpy(tabel, "RIWAYAT SKOR (30 Permainan Terakhir)");
    print_tabel_skor(x, &y2, file_sp, tabel);

    gotoxy(1, (y > y2) ? (y + 1) : (y2 + 1));
    printf("Tekan ESC untuk kembali...");

    do {
        key = getch();
    } while (key != 27);  // selama tidak menekan tombol ESC

    menu_riwayat_skor();
}
