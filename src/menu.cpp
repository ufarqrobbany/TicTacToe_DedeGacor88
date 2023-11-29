#include "menu.h"

#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "common.h"
#include "header.h"
#include "play.h"
#include "score.h"

void menu_utama() {
    system("cls||clear");

    int i, baris;
    int lebar = 94;
    int tinggi = 7;
    char opsi[5][20] = {"Mulai Permainan", "Riwayat Skor", "Bantuan", "Kredit", "Keluar"};
    char key;
    int current_selection = 1;

    // print header
    char str[] = "MENU UTAMA";
    header(str);

    // print body menu utama
    for (i = 11; i < 11 + tinggi; i++) {
        gotoxy(1, i);
        printf("%c", 186);
        gotoxy(lebar + 2, i);
        printf("%c\n", 186);
    }

    printf("%c", 200);
    for (i = 0; i < lebar; i++) printf("%c", 205);
    printf("%c\n", 188);

    // print isi body
    do {
        for (i = 0; i < 5; i++) {
            gotoxy(4, i + 12);
            printf("%c %s", (current_selection == i + 1) ? 254 : ' ', opsi[i]);
        }

        gotoxy(1, i + 14);

        // navigasi menu
        key = getch();
        if ((key == 72) && (current_selection > 1)) {
            current_selection -= 1;
        } else if ((key == 80) && (current_selection < 5)) {
            current_selection += 1;
        } else if ((key == 13)) {
            switch (current_selection) {
                case 1:
                    permainan();
                    break;
                case 2:
                    menu_riwayat_skor();
                    break;
                case 3:
                    menu_bantuan();
                    break;
                case 4:
                    menu_kredit();
                    break;
                case 5:
                    break;
            }
        }
    } while (key != 13);
}

void menu_bantuan() {
    system("cls||clear");

    int i, baris, ch;
    int lebar = 94;
    char key;
    FILE *data;

    // print header
    char str[] = "BANTUAN";
    header(str);

    // print isi konten body
    data = fopen("data/help.txt", "r");
    gotoxy(4, 12);
    baris = 1;
    while ((ch = getc(data)) != EOF) {
        putchar(ch);

        if (ch == '\n') {
            gotoxy(4, baris + 12);
            baris++;
        }
    }
    fclose(data);
    free(data);

    // print container body yang tinggi nya menyesuaikan konten
    for (i = 11; i < 11 + baris + 2; i++) {
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

void menu_kredit() {
    system("cls||clear");

    int i, baris, ch;
    int lebar = 94;
    char key;
    FILE *data;

    // print header
    char str[] = "KREDIT";
    header(str);

    // print isi konten body
    data = fopen("data/credits.txt", "r");
    gotoxy(4, 12);
    baris = 1;
    while ((ch = getc(data)) != EOF) {
        putchar(ch);

        if (ch == '\n') {
            gotoxy(4, baris + 12);
            baris++;
        }
    }
    fclose(data);
    free(data);

    // print container body yang tinggi nya menyesuaikan konten
    for (i = 11; i < 11 + baris + 2; i++) {
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
