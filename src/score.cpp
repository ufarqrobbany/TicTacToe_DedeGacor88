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

void print_tabel_skor(int *baris, char file[30], char title[50]) {
    int i;
    FILE *data;
    char w_mulai[22], w_selesai[22], pemain_1[11], pemain_2[11], pemain[25], skor_1[3], skor_2[3];

    // print title tabel
    gotoxy(4, (*baris)++);
    printf(title);

    // print header tabel
    gotoxy(4, (*baris)++);
    printf("%c", 201);
    for (i = 0; i < 23; i++) printf("%c", 205);
    printf("%c", 203);
    for (i = 0; i < 26; i++) printf("%c", 205);
    printf("%c", 203);
    for (i = 0; i < 15; i++) printf("%c", 205);
    printf("%c", 203);
    for (i = 0; i < 21; i++) printf("%c", 205);
    printf("%c", 187);

    gotoxy(4, (*baris)++);
    printf("%c      Waktu Mulai      %c          Pemain          %c      Skor     %c    Waktu Selesai    %c", 186, 186, 186, 186, 186);

    gotoxy(4, (*baris)++);
    printf("%c", 204);
    for (i = 0; i < 23; i++) printf("%c", 205);
    printf("%c", 206);
    for (i = 0; i < 26; i++) printf("%c", 205);
    printf("%c", 206);
    for (i = 0; i < 15; i++) printf("%c", 205);
    printf("%c", 206);
    for (i = 0; i < 21; i++) printf("%c", 205);
    printf("%c", 185);

    // print data & body tabel
    data = fopen(file, "r");
    while ((fscanf(data, "%[^#]#%[^#]#%[^#]#%[^#]#%[^#]#%[^\n]\n", w_mulai, pemain_1, pemain_2, skor_1, skor_2, w_selesai) == 6)) {
        gotoxy(4, (*baris)++);
        fflush(stdin);
        printf("%c %-21s %c", 186, w_mulai, 186);
        sprintf(pemain, "%s vs %s", pemain_1, pemain_2);
        printf(" %-24s ", pemain);
        printf("%c", 186);
        gotoxy(62 - (strlen(skor_1) + 1), (*baris) - 1);
        printf(" %s - ", skor_1);
        printf("%s", skor_2);
        for (i = 0; i < 6 - strlen(skor_2); i++) printf(" ");
        printf("%c %-19s %c", 186, w_selesai, 186);
    }
    fclose(data);
    free(data);

    // print penutup tabel
    gotoxy(4, (*baris)++);
    printf("%c", 200);
    for (i = 0; i < 23; i++) printf("%c", 205);
    printf("%c", 202);
    for (i = 0; i < 26; i++) printf("%c", 205);
    printf("%c", 202);
    for (i = 0; i < 15; i++) printf("%c", 205);
    printf("%c", 202);
    for (i = 0; i < 21; i++) printf("%c", 205);
    printf("%c", 188);
    (*baris)++;
}

void menu_riwayat_skor() {
    system("cls||clear");

    int i, baris;
    int lebar = 94;
    int tinggi = 14;
    char key;

    // print header
    char str[] = "SKOR";
    header(str);

    // print isi konten body
    // print tabel
    baris = 12;
    char titlehs[] = "SKOR TERTINGGI - TOP 3";
    char highscore[] = "../data/highscores.txt";
    print_tabel_skor(&baris, highscore, titlehs);

    char titles[] = "RIWAYAT SKOR";
    char score[] = "../data/scores.txt";
    print_tabel_skor(&baris, score, titles);

    // print container body yang tinggi nya menyesuaikan konten
    for (i = 11; i < baris; i++) {
        gotoxy(1, i);
        printf("%c", 186);
        gotoxy(lebar + 2, i);
        printf("%c\n", 186);
    }

    printf("%c", 200);
    for (i = 0; i < lebar; i++) printf("%c", 205);
    printf("%c\n", 188);

    printf("Tekan ESC untuk kembali...");

    do {
        key = getch();
    } while (key != 27);  // selama tidak menekan tombol ESC
    menu_utama();
}
