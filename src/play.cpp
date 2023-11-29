#include "play.h"

#include <conio.h>
#include <stdio.h>
#include <windows.h>

#include "common.h"
#include "header.h"
#include "menu.h"

void permainan() {
    int mode, level, ukuran;

    mode = 0;
    level = 0;
    ukuran = 0;
    while (mode == 0) {
        mode = pilih_mode();
        if (mode == -1) {
            break;
        } else {
            level = 0;
        }

        while (level == 0) {
            if (mode == 1) {
                level = pilih_tingkat();
                if (level == -1) {
                    mode = 0;
                    break;
                }
            }

            while (ukuran == 0) {
                ukuran = pilih_ukuran();
                if (ukuran == -1) {
                    if (mode == 1) level = 0;
                    if (mode == 2) {
                        level = 0;
                        mode = 0;
                    }
                    break;
                }
            }
            if (mode = 0) break;
        }
    }

    menu_utama();
}

int pilih_mode() {
    system("cls||clear");

    int i, baris;
    int lebar = 94;
    int tinggi = 4;
    char opsi[2][20] = {"Player vs Computer", "Player vs Player"};
    char key;
    int current_selection = 1;

    // print header
    char str[] = "PILIH MODE BERMAIN";
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
        for (i = 0; i < 2; i++) {
            gotoxy(4, i + 12);
            printf("%c %s", (current_selection == i + 1) ? 254 : ' ', opsi[i]);
        }

        gotoxy(1, i + 14);
        printf("Tekan ESC untuk kembali...");

        // navigasi menu
        key = getch();
        if ((key == 72) && (current_selection > 1)) {
            current_selection -= 1;
        } else if ((key == 80) && (current_selection < 2)) {
            current_selection += 1;
        } else if (key == 13) {
            return current_selection;
        } else if (key == 27) {
            return -1;
        }
    } while (key != 13 || key != 27);
}

int pilih_tingkat() {
    system("cls||clear");

    int i, baris;
    int lebar = 94;
    int tinggi = 5;
    char opsi[3][20] = {"Easy", "Medium", "Hard"};
    char key;
    int current_selection = 1;

    // print header
    char str[] = "PILIH TINGKAT KESULITAN";
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
        for (i = 0; i < 3; i++) {
            gotoxy(4, i + 12);
            printf("%c %s", (current_selection == i + 1) ? 254 : ' ', opsi[i]);
        }

        gotoxy(1, i + 14);
        printf("Tekan ESC untuk kembali...");

        // navigasi menu
        key = getch();
        if ((key == 72) && (current_selection > 1)) {
            current_selection -= 1;
        } else if ((key == 80) && (current_selection < 3)) {
            current_selection += 1;
        } else if (key == 13) {
            return current_selection;
        } else if (key == 27) {
            return -1;
        }
    } while (key != 13 || key != 27);
}

int pilih_ukuran() {
    system("cls||clear");

    int i, baris;
    int lebar = 94;
    int tinggi = 5;
    char opsi[3][20] = {"3 x 3", "5 x 5", "7 x 7"};
    char key;
    int current_selection = 1;

    // print header
    char str[] = "PILIH UKURAN PAPAN";
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
        for (i = 0; i < 3; i++) {
            gotoxy(4, i + 12);
            printf("%c %s", (current_selection == i + 1) ? 254 : ' ', opsi[i]);
        }

        gotoxy(1, i + 14);
        printf("Tekan ESC untuk kembali...");

        // navigasi menu
        key = getch();
        if ((key == 72) && (current_selection > 1)) {
            current_selection -= 1;
        } else if ((key == 80) && (current_selection < 3)) {
            current_selection += 1;
        } else if (key == 13) {
            return current_selection;
        } else if (key == 27) {
            return -1;
        }
    } while (key != 13 || key != 27);
}