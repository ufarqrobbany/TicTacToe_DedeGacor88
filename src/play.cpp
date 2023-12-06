#include "play.h"

#include <conio.h>
#include <stdio.h>
#include <windows.h>

#include "board.h"
#include "common.h"
#include "header.h"
#include "menu.h"

void permainan() {
    Player *pemain = (Player *)malloc(sizeof(Player) * 2);
    int mode, level, ukuran, nama, simbol, mulai;
    int papan[7][7];

    // inisialisasi pengaturan game
    mulai = 0;
    mode = 0;
    while (mode == 0) {
        mode = pilih_mode();
        if (mode == -1) break;

        nama = 0;
        while (nama == 0) {
            pemain = input_nama(mode);
            if (strcmp(pemain[0].nama, "") == 0 && strcmp(pemain[1].nama, "") == 0) {
                nama = -1;
                mode = 0;
                break;
            } else {
                nama = 1;
                level = 0;
                while (level == 0) {
                    if (mode == 1) {
                        level = pilih_level();
                        if (level == -1) {
                            nama = 0;
                            break;
                        }
                    } else {
                        level = 4;
                    }

                    ukuran = 0;
                    while (ukuran == 0) {
                        ukuran = pilih_ukuran();
                        if (ukuran == -1) {
                            if (mode == 1) level = 0;
                            if (mode == 2) nama = 0;
                            break;
                        }

                        simbol = 0;
                        while (simbol == 0) {
                            simbol = pilih_simbol();
                            if (simbol == 1) {
                                pemain[0].simbol = 'X';
                                pemain[1].simbol = 'O';
                            } else if (simbol == 2) {
                                pemain[0].simbol = 'O';
                                pemain[1].simbol = 'X';
                            } else {
                                ukuran = 0;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }

    init_papan(ukuran, &papan);

    system("cls||clear");
    menu_permainan();
    // display_papan(ukuran, papan);

    // menu_utama();
}

void menu_permainan() {
    int i;
    int lebar = 94;
    int tinggi = 30;

    char ket[30] = "Game On, Good Luck!";

    // print header
    header(ket);

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
}

int pilih_mode() {
    system("cls||clear");
    int jml_opsi = 2;
    char menu[20] = "PILIH MODE BERMAIN";
    char opsi[jml_opsi][20] = {"Player vs Computer", "Player vs Player"};
    int select = 0;
    menu_opsi(menu, jml_opsi, opsi, &select, true);
    if (select != 0) {
        return select;
    } else {
        return -1;
    }
}

struct Player *input_nama(int mode) {
    system("cls||clear");
    Player *npemain = (Player *)malloc(sizeof(Player) * 2);
    Player *pemain = (Player *)malloc(sizeof(Player) * 2);
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
                npemain[0].nama[n++] = key;
            } else {
                npemain[1].nama[n++] = key;
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
        pemain[0] = npemain[0];
        if (mode == 1) {
            char name2[10] = "Computer";
            strcpy(pemain[1].nama, name2);
        } else {
            pemain[1] = npemain[1];
        }
        free(npemain);
        return pemain;
    } else if (key == 27) {
        free(npemain);
        strcpy(pemain[0].nama, "");
        strcpy(pemain[1].nama, "");
        return pemain;
    }
}

int pilih_level() {
    system("cls||clear");
    int jml_opsi = 3;
    char menu[30] = "PILIH TINGKAT KESULITAN";
    char opsi[jml_opsi][20] = {"Easy", "Medium", "Hard"};
    int select = 0;
    menu_opsi(menu, jml_opsi, opsi, &select, true);
    if (select != 0) {
        return select;
    } else {
        return -1;
    }
}

int pilih_ukuran() {
    system("cls||clear");
    int jml_opsi = 3;
    char menu[20] = "PILIH UKURAN PAPAN";
    char opsi[jml_opsi][20] = {"3 x 3", "5 x 5", "7 x 7"};
    int select = 0;
    menu_opsi(menu, jml_opsi, opsi, &select, true);
    if (select != 0) {
        return ((select * 2) + 1);
    } else {
        return -1;
    }
}

int pilih_simbol() {
    system("cls||clear");
    int jml_opsi = 2;
    char menu[30] = "PILIH SIMBOL PEMAIN 1";
    char opsi[jml_opsi][20] = {"X", "O"};
    int select = 0;
    menu_opsi(menu, jml_opsi, opsi, &select, true);
    if (select != 0) {
        return select;
    } else {
        return -1;
    }
}