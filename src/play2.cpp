#include "play.h"

#include <conio.h>
#include <stdio.h>
#include <windows.h>

#include "common.h"
#include "header.h"
#include "menu.h"

Player pemain_1, pemain_2;
int mode, level, ukuran;

void permainan() {
    pilih_mode(&mode);
}

void pilih_mode(int *mode) {
    system("cls||clear");
    int jml_opsi = 2;
    char menu[20] = "PILIH MODE BERMAIN";
    char opsi[jml_opsi][20] = {"Player vs Computer", "Player vs Player"};
    int select = 0;
    menu_opsi(menu, jml_opsi, opsi, &select, true);
    if (select != 0) {
        *mode = select;
        input_nama(*mode, &pemain_1, &pemain_2);
    } else {
        menu_utama();
    }
}

void input_nama(int mode, Player *pemain_1, Player *pemain_2) {
    system("cls||clear");
    int i, n, p, baris;
    int lebar = 94;
    int tinggi = mode + 2;
    char key;

    // print header
    char nama_menu[] = "MASUKKAN NAMA PEMAIN";
    header(nama_menu);

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

    gotoxy(1, mode + 14);
    printf("Tekan ESC untuk kembali...");

    // print isi body
    gotoxy(4, 12);
    printf("Player 1: \n");
    if (mode == 2) {
        gotoxy(4, 13);
        printf("Player 2: \n");
    }

    p = 1;
    n = 0;
    gotoxy(14, 12);
    do {
        // navigasi menu
        key = getch();

        if (((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9') || (key == ' ')) && (n < 10)) {
            if (p == 1) {
                (*pemain_1).nama[n++] = key;
            } else {
                (*pemain_2).nama[n++] = key;
            }
            printf("%c", key);
            gotoxy(14 + n, 11 + p);
        } else if ((key == 13) && (n > 0)) {  // jika menekan tombol Enter dan n lebih dari 0 / ada karakter
            if ((mode == 2) && (p == 1)) {
                p = 2;
                n = 0;
                gotoxy(14 + n, 11 + p);
            } else {
                break;
            }
        } else if (key == 8) {  // jika menekan tombol backspace
            // jika n lebih dari 0 / ada karakter
            if (n > 0) {
                // Pindahkan kursor ke belakang, hapus karakter, dan kurangi n
                printf("\b \b");
                n--;
            }
        }
    } while (key != 27);  // Selama tidak menekan tombol ESC

    if (key == 13) {
        if (mode == 1) {
            pilih_level(&level);
        } else {
            pilih_ukuran(&ukuran);
        }
    } else if (key == 27) {
        pilih_mode(&mode);
    }
}

void pilih_level(int *level) {
    system("cls||clear");
    int jml_opsi = 3;
    char menu[30] = "PILIH TINGKAT KESULITAN";
    char opsi[jml_opsi][20] = {"Easy", "Medium", "Hard"};
    int select = 0;
    menu_opsi(menu, jml_opsi, opsi, &select, true);
    if (select != 0) {
        *level = select;
        pilih_ukuran(&ukuran);
    } else {
        input_nama(mode, &pemain_1, &pemain_2);
    }
}

void pilih_ukuran(int *ukuran) {
    system("cls||clear");
    int jml_opsi = 3;
    char menu[20] = "PILIH UKURAN PAPAN";
    char opsi[jml_opsi][20] = {"3 x 3", "5 x 5", "7 x 7"};
    int select = 0;
    menu_opsi(menu, jml_opsi, opsi, &select, true);
    if (select != 0) {
        *ukuran = (select * 2) + 1;
        pilih_simbol(&pemain_1, &pemain_2);
    } else {
        if (mode == 1) {
            pilih_level(&level);
        } else {
            input_nama(mode, &pemain_1, &pemain_2);
        }
    }
}

void pilih_simbol(Player *pemain_1, Player *pemain_2) {
    system("cls||clear");
    int jml_opsi = 2;
    char menu[20] = "PILIH SIMBOL PEMAIN 1";
    char opsi[jml_opsi][20] = {"X", "O"};
    int select = 0;
    menu_opsi(menu, jml_opsi, opsi, &select, true);
    switch (select) {
        case 1:
            *pemain_1.simbol = 'X';
            *pemain_2.simbol = 'O';
            menu_utama();
            break;
        case 2:
            *pemain_1.simbol = 'O';
            *pemain_2.simbol = 'X';
            menu_utama();
            break;
        default:
            pilih_ukuran(&ukuran);
    }
}