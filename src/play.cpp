#include "play.h"

#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>

#include "board.h"
#include "common.h"
#include "header.h"
#include "menu.h"

void permainan() {
    Player *pemain = (Player *)malloc(sizeof(Player) * 2);
    int mode, level, ukuran, nama, simbol, mulai, letak, menang;
    int papan[7][7];
    char key;
    int current_selection = 1;

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
                                pemain[0].giliran = 1;
                                pemain[1].giliran = 2;
                            } else if (simbol == 2) {
                                pemain[0].simbol = 'O';
                                pemain[1].simbol = 'X';
                                pemain[0].giliran = 2;
                                pemain[1].giliran = 1;
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

    // https://www.daniweb.com/programming/software-development/threads/91097/countdown-timer
    time_t saat_ini = time(0);
    struct tm *waktu = localtime(&saat_ini);
    int countdown = saat_ini;

    int giliran_saat_ini = 1;

    menang = 0;
    while (menang == 0 && key != 27) {
        system("cls||clear");
        menu_permainan(pemain, ukuran);

        do {
            gotoxy(4, 12);
            if (giliran_saat_ini == pemain[0].giliran) {
                printf("Giliran: %s (%c)         ", pemain[0].nama, pemain[0].simbol);
            } else {
                printf("Giliran: %s (%c)         ", pemain[1].nama, pemain[1].simbol);
            }
            saat_ini = time(0);
            gotoxy(74, 12);
            printf("Sisa Waktu: %-2d Detik", 10 - (saat_ini - countdown));
            display_papan(ukuran, papan, current_selection);

            if ((giliran_saat_ini == pemain[0].giliran) || ((giliran_saat_ini == pemain[1].giliran) && (mode == 2))) {
                do {
                    key = getch();

                    saat_ini = time(0);
                    gotoxy(74, 12);
                    printf("Sisa Waktu: %-2d Detik", 10 - (saat_ini - countdown));

                    if (key == 72 && current_selection > ukuran) {
                        // Up arrow
                        current_selection -= ukuran;
                    } else if (key == 80 && current_selection <= ukuran * (ukuran - 1)) {
                        // Down arrow
                        current_selection += ukuran;
                    } else if (key == 75 && (current_selection % ukuran) != 1) {
                        // Left arrow
                        current_selection -= 1;
                    } else if (key == 77 && (current_selection % ukuran) != 0) {
                        // Right arrow
                        current_selection += 1;
                    } else if (key == 13 && cek_sel(current_selection, ukuran, papan)) {
                        // Enter
                        break;
                    } else if (key == 27) {
                        break;
                    }
                } while (key != 75 && key != 77 && key != 72 && key != 80 && key != 27);

                saat_ini = time(0);
                if (key == 13) {
                    if (saat_ini - countdown < 10) {
                        put_simbol(current_selection, giliran_saat_ini, ukuran, &papan);
                    } else {
                        gotoxy(4, 13 + (ukuran * 4));
                        printf("Kamu meletakkan simbol selama %d detik.               ", (saat_ini - countdown));
                    }

                    // alih giliran
                    if (giliran_saat_ini == 1) {
                        giliran_saat_ini = 2;
                    } else {
                        giliran_saat_ini = 1;
                    }

                    saat_ini = time(0);
                    countdown = saat_ini;
                }
            }
        } while (key != 27);

        menang = 1;

        // gotoxy(4, 12);
        // printf("Giliran");
        // display_papan(ukuran, papan);
        // scanf("%d", &letak);
        // cek_papan();
    }

    // menu_utama();
}

void menu_permainan(Player pemain[2], int ukuran) {
    int i;
    int lebar = 94;
    int tinggi = 3 + (ukuran * 4) + 4;

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