#include "play.h"

#include <conio.h>
#include <stdio.h>
#include <windows.h>

#include "common.h"
#include "header.h"
#include "menu.h"

void input_nama(int mode);

typedef struct {
    char nama[10];
} Player;

Player pemain_1, pemain_2;

void pilih_mode() {
    system("cls||clear");
    int jml_opsi = 2;
    char menu[20] = "PILIH MODE BERMAIN";
    char opsi[jml_opsi][20] = {"Player vs Computer", "Player vs Player"};
    int select = 0;
    menu_opsi(menu, jml_opsi, opsi, &select, true);
    if (select != 0) {
        input_nama(select);
    } else {
        menu_utama();
    }
}

void input_nama(int mode) {
    system("cls||clear");
    int i, n, baris;
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

    gotoxy(1, tinggi + 14);
    printf("Tekan ESC untuk kembali...");

    // print isi body
    n = 0;
    do {
        gotoxy(4, 12);
        printf("Player 1: ");

        // navigasi menu
        key = getch();
        if (key == 13 || key == 27) {
            break;
        } else {
            gotoxy(4 + n + 1, i + 12);
            pemain_1.nama[n] = key;
            printf("%c", key);
            n++;
        }
    } while (key != 13 || key != 27);
}