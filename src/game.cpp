#include "game.h"

#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>

#include "board.h"
#include "bot.h"
#include "common.h"
#include "datetime.h"
#include "header.h"
#include "menu.h"

void game() {
    Game play_data;
    int main;

    main = 0;
    init_game(&play_data, &main);

    while (main == 1) {
        play(&play_data, &main);
    }

    // jika selesai bermain
    if (main == 2) {
        get_datetime(&play_data.waktu_selesai);
    }

    menu_utama();
}

void play(Game *play_data, int *main) {
    Player *pemain = (Player *)malloc(sizeof(Player) * 2);
    int mode, ukuran, menang, countdown, sisa_waktu, papan[7][7];
    int pemainMenang, pemainKalah;

    int awal_giliran;

    mode = (*play_data).mode;
    ukuran = (*play_data).ukuran;
    pemain = (*play_data).pemain;

    char key;

    time_t saat_ini;
    struct tm *waktu;
    bool isBot;

    int current_giliran, current_selection, last_selection, bot_selection;

    init_papan(ukuran, &papan);

    menang = 0;
    while (menang == 0) {
        clear_screen();

        display_game(pemain, ukuran);
        print_skor(pemain);

        isBot = false;
        current_giliran = 1;
        current_selection = 1;

        // simpan data waktu mulai
        // saat_ini = time(0);
        // waktu = localtime(&saat_ini);
        get_datetime(&(*play_data).waktu_mulai);

        countdown = saat_ini;

        do {
            // jeda pergantian pemain dari computer
            if ((current_giliran == pemain[1].giliran) && (mode == 1) && (isBot)) {
                sleep(2);
                change_giliran(&current_giliran);

                current_selection = last_selection;

                saat_ini = time(0);
                countdown = saat_ini;
            }

            print_giliran(current_giliran, pemain);

            // print sisa waktu
            saat_ini = time(0);
            gotoxy(74, 12);
            sisa_waktu = 10 - (saat_ini - countdown);
            printf("Sisa Waktu: %-2d Detik", (sisa_waktu >= 0) ? sisa_waktu : 0);

            // print papan
            display_papan(ukuran, papan, current_selection);

            // bermain
            if ((current_giliran == pemain[0].giliran) || ((current_giliran == pemain[1].giliran) && (mode == 2))) {
                gotoxy(4, 13 + (ukuran * 4) + 3);
                printf("                                                                        ");
                isBot = false;
                do {
                    // tekan tombol
                    key = getch();

                    saat_ini = time(0);
                    sisa_waktu = 10 - (saat_ini - countdown);
                    gotoxy(74, 12);
                    printf("Sisa Waktu: %-2d Detik", (sisa_waktu >= 0) ? sisa_waktu : 0);

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
                        put_simbol(current_selection, current_giliran, ukuran, &papan);
                        menang = cek_papan(ukuran, papan);
                    } else {
                        gotoxy(4, 13 + (ukuran * 4) + 3);
                        printf("Waktumu sudah habis! sekarang giliran lawan.                                   ");
                        getch();
                    }

                    saat_ini = time(0);
                    countdown = saat_ini;

                    change_giliran(&current_giliran);
                }
            } else {
                last_selection = current_selection;
                current_selection = 0;
                display_papan(ukuran, papan, current_selection);
                bot_selection = 0;
                gotoxy(4, 13 + (ukuran * 4) + 3);
                printf("Tunggu Computer meletakkan simbolnya...                                        ");
                isBot = true;

                // bot komputer
                bot_selection = bot(ukuran, papan);
                put_simbol(bot_selection, current_giliran, ukuran, &papan);
                menang = cek_papan(ukuran, papan);
            }
        } while (menang == 0);

        if (menang != 0) {
            display_papan(ukuran, papan, current_selection);
            sleep(2);
            if (pemain[0].giliran == menang) {
                pemain[0].skor++;
                pemainMenang = 1;
                pemainKalah = 2;
            } else if (pemain[1].giliran == menang) {
                pemain[1].skor++;
                pemainMenang = 2;
                pemainKalah = 1;
            } else {
                pemainMenang = 0;
                pemainKalah = 0;
            }
            *main = end_game(mode, pemainMenang, pemainKalah, pemain);
        } else {
            // pause
            menang = 1;
        }
    }
}

void change_giliran(int *giliran) {
    if (*giliran == 1) {
        *giliran = 2;
    } else {
        *giliran = 1;
    }
}

void print_giliran(int giliran, Player pemain[2]) {
    gotoxy(4, 12);
    if (giliran == pemain[0].giliran) {
        printf("Giliran: %s (%c)         ", pemain[0].nama, pemain[0].simbol);
    } else {
        printf("Giliran: %s (%c)         ", pemain[1].nama, pemain[1].simbol);
    }
}

void print_skor(Player pemain[2]) {
    char skor[10];

    // gabungkan skor menjadi string
    sprintf(skor, "%d - %d", pemain[0].skor, pemain[1].skor);
    // print skor
    gotoxy(48 - (int)(strlen(skor) / 2) + 1, 12);
    printf("%s", skor);
}

void print_waktu() {
}

int end_game(int mode, int pemainMenang, int pemainKalah, Player pemain[2]) {
    system("cls||clear");
    int i;
    int lebar = 94;
    int tinggi = 13;
    char key;
    int current_selection = 1;

    char ket[30];

    gotoxy(4, 12);
    if (pemainMenang == 1) {
        sprintf(ket, "%s (%c) Win The Game!", pemain[0].nama, pemain[0].simbol);
        printf("Good game, %s (%c)!", pemain[0].nama, pemain[0].simbol);
        gotoxy(4, 13);
        printf("Kamu telah mengalahkan %s (%c) dalam permainan ini", pemain[1].nama, pemain[1].simbol);
        gotoxy(4, 15);
        printf("GACOR BANGET BANG!");
    } else if (pemainMenang == 2) {
        if (mode == 1) {
            sprintf(ket, "You Lose!");
            printf("Game over, %s (%c)", pemain[0].nama, pemain[0].simbol);
            gotoxy(4, 13);
            printf("Kamu telah dikalahkan oleh Computer dalam permainan ini");
            gotoxy(4, 15);
            printf("KAMU KURANG GACOR, COBA LAGI YA!");
        } else {
            sprintf(ket, "%s (%c) Win The Game!", pemain[1].nama, pemain[1].simbol);
            printf("Good game, %s (%c)!", pemain[1].nama, pemain[1].simbol);
            gotoxy(4, 13);
            printf("Kamu telah mengalahkan %s (%c) dalam permainan ini", pemain[0].nama, pemain[0].simbol);
            gotoxy(4, 15);
            printf("GACOR BANGET BANG!");
        }
    } else {
        sprintf(ket, "It's a Draw");
        printf("Try again, %s (%c)", pemain[0].nama, pemain[0].simbol);
        gotoxy(4, 13);
        printf("Permainan ini dinyatakan seri");
        gotoxy(4, 15);
        printf("DUA DUANYA GACOR!");
    }

    gotoxy(4, 17);
    printf("Skor saat ini ");
    gotoxy(4, 18);
    printf("    %s (%c) \t: %d", pemain[0].nama, pemain[0].simbol, pemain[0].skor);
    gotoxy(4, 19);
    printf("    %s (%c) \t: %d", pemain[1].nama, pemain[1].simbol, pemain[1].skor);

    // print header
    gotoxy(1, 1);
    header(ket);

    // print body menu permainan
    for (i = 11; i < 11 + tinggi; i++) {
        gotoxy(1, i);
        printf("%c", 186);
        gotoxy(lebar + 2, i);
        printf("%c\n", 186);
    }

    printf("%c", 200);
    for (i = 0; i < lebar; i++) printf("%c", 205);
    printf("%c\n", 188);

    // opsi
    do {
        gotoxy(4, 21);
        printf("%c %s", (current_selection == 1) ? 254 : ' ', "Main lagi!");
        gotoxy(4, 22);
        printf("%c %s", (current_selection == 2) ? 254 : ' ', "Berhenti main");

        key = getch();
        if ((key == 72) && (current_selection > 1)) {
            current_selection -= 1;
        } else if ((key == 80) && (current_selection < 2)) {
            current_selection += 1;
        } else if (key == 13) {
            if (current_selection == 1) {
                return 1;
            } else {
                return 0;
            }
        }
    } while (key != 13);
}

void display_game(Player pemain[2], int ukuran) {
    int i;
    int lebar = 94;
    int tinggi = 3 + (ukuran * 4) + 4;

    char ket[30] = "Game On, Good Luck!";

    // print header
    header(ket);

    // print body menu permainan
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

void init_game(Game *play_data, int *main) {
    int nama, simbol;

    (*play_data).mode = 0;
    while ((*play_data).mode == 0) {
        (*play_data).mode = pilih_mode();
        if ((*play_data).mode == -1) {
            break;
        }

        nama = 0;
        while (nama == 0) {
            (*play_data).pemain = input_nama((*play_data).mode);
            if (strcmp((*play_data).pemain[0].nama, "") == 0 && strcmp((*play_data).pemain[1].nama, "") == 0) {
                nama = -1;
                (*play_data).mode = 0;
                break;
            } else {
                nama = 1;
                (*play_data).level = 0;
                while ((*play_data).level == 0) {
                    if ((*play_data).mode == 1) {
                        (*play_data).level = pilih_level();
                        if ((*play_data).level == -1) {
                            nama = 0;
                            break;
                        }
                    } else {
                        (*play_data).level = 4;
                    }

                    (*play_data).ukuran = 0;
                    while ((*play_data).ukuran == 0) {
                        (*play_data).ukuran = pilih_ukuran();
                        if ((*play_data).ukuran == -1) {
                            if ((*play_data).mode == 1) (*play_data).level = 0;
                            if ((*play_data).mode == 2) nama = 0;
                            break;
                        }

                        simbol = 0;
                        while (simbol == 0) {
                            simbol = pilih_simbol();
                            if (simbol == 1) {
                                (*play_data).pemain[0].simbol = 'X';
                                (*play_data).pemain[1].simbol = 'O';
                                (*play_data).pemain[0].giliran = 1;
                                (*play_data).pemain[1].giliran = 2;
                                *main = 1;
                            } else if (simbol == 2) {
                                (*play_data).pemain[0].simbol = 'O';
                                (*play_data).pemain[1].simbol = 'X';
                                (*play_data).pemain[0].giliran = 2;
                                (*play_data).pemain[1].giliran = 1;
                                *main = 1;
                            } else {
                                (*play_data).ukuran = 0;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }

    if (*main == 1) {
        (*play_data).pemain[0].skor = 0;
        (*play_data).pemain[1].skor = 0;
    }
}

int pilih_mode() {
    clear_screen();
    int jml_opsi = 2;
    char menu[20] = "PILIH MODE BERMAIN";
    char opsi[jml_opsi][20] = {"Player vs Computer", "Player vs Player"};
    int select = 0;
    select = menu_opsi(menu, jml_opsi, opsi, true);
    if (select != 0) {
        return select;
    } else {
        return -1;
    }
}

struct Player *input_nama(int mode) {
    clear_screen();
    char namapemain1[11], namapemain2[11];
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
    printf("Masukkan nama kamu. Tekan Enter untuk konfirmasi.");
    gotoxy(1, mode + 15);
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
        key = getch();

        if (((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9') || (key == ' ')) && (n < 10)) {
            if (p == 1) {
                namapemain1[n] = key;
            } else {
                namapemain2[n] = key;
            }
            n++;
            printf("%c", key);
            gotoxy(14 + n, 11 + p);
        } else if (key == 13) {  // Enter key
            if (n > 0) {
                if ((mode == 2) && (p == 1)) {
                    namapemain1[n] = '\0';
                    p = 2;
                    n = 0;
                    gotoxy(14 + n, 11 + p);
                } else {
                    if ((mode == 1) && (p == 1)) namapemain1[n] = '\0';
                    if ((mode == 2) && (p == 2)) namapemain2[n] = '\0';
                    break;
                }
            }
        } else if (key == 8) {  // Backspace key
            if (n > 0) {
                printf("\b \b");
                n--;
            }
        }
    } while (key != 27);  // ESC key

    if (key == 13) {
        strcpy(pemain[0].nama, namapemain1);

        if (mode == 1) {
            char name2[11] = "Computer";
            name2[sizeof(name2) - 1] = '\0';
            strncpy(pemain[1].nama, name2, sizeof(pemain[1].nama));
        } else {
            strcpy(pemain[1].nama, namapemain2);
        }

        return pemain;
    } else if (key == 27) {
        strcpy(pemain[0].nama, "");
        strcpy(pemain[1].nama, "");
        return pemain;
    }
}

int pilih_level() {
    clear_screen();
    int jml_opsi = 3;
    char menu[30] = "PILIH TINGKAT KESULITAN";
    char opsi[jml_opsi][20] = {"Easy", "Medium", "Hard"};
    int select = 0;
    select = menu_opsi(menu, jml_opsi, opsi, true);
    if (select != 0) {
        return select;
    } else {
        return -1;
    }
}

int pilih_ukuran() {
    clear_screen();
    int jml_opsi = 3;
    char menu[20] = "PILIH UKURAN PAPAN";
    char opsi[jml_opsi][20] = {"3 x 3", "5 x 5", "7 x 7"};
    int select = 0;
    select = menu_opsi(menu, jml_opsi, opsi, true);
    if (select != 0) {
        return ((select * 2) + 1);
    } else {
        return -1;
    }
}

int pilih_simbol() {
    clear_screen();
    int jml_opsi = 2;
    char menu[30] = "PILIH SIMBOL PEMAIN 1";
    char opsi[jml_opsi][20] = {"X", "O"};
    int select = 0;
    select = menu_opsi(menu, jml_opsi, opsi, true);
    if (select != 0) {
        return select;
    } else {
        return -1;
    }
}