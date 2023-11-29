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
    gotoxy(4, 12);
    printf("Player 1: ");
    n = 0;
    do {
        // navigasi menu
        key = getch();
        // jika menekan tombol ESC atau Enter
        if (key == 13 || key == 27) {
            break;
        } else if (key == 8) {  // jika menekan tombol backspace
            // jika n lebih dari 0 / ada karakter
            if (n > 0) {
                // Pindahkan kursor ke belakang, hapus karakter, dan kurangi n
                printf("\b \b");
                n--;
            }
        } else if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9') || (key == ' ')) {
            pemain_1.nama[n++] = key;
            printf("%c", key);
            gotoxy(14 + n, 12);
        }
    } while (key != 13 || key != 27);  // Selama tidak menekan tombol ESC atau Enter

    if (key == 27) {
        pilih_mode();
    }
    gotoxy(4, 15);
}

// n = 0;
// do {
//     // navigasi menu
//     key = getch();
//     if (key == 13 || key == 27) {
//         break;
//     } else if (key == 8) {  // Check for backspace (ASCII code 8)
//         if (n > 0) {
//             // Move the cursor back, erase the character, and decrement n
//             printf("\b \b");
//             n--;
//         }
//     } else {
//         pemain_1.nama[n++] = key;
//         printf("%c", key);
//         gotoxy(14 + n, 12);
//     }
// } while (key != 13 && key != 27);
