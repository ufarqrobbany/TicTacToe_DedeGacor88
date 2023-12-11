#include "game.h"

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>

#include "board.h"
#include "bot.h"
#include "common.h"
#include "datetime.h"
#include "header.h"
#include "menu.h"
#include "score.h"

void Game() {
    DataGame play_data;
    int play;

    play = 0;
    InitGame(&play_data, &play);

    while (play == 1) {
        PlayGame(&play_data, &play);
    }

    // jika selesai bermain
    if (play == 2) {
        GetDatetime(&play_data.waktu_selesai);
        SaveSkor(play_data.ukuran, play_data.level, play_data.waktu_mulai, play_data.pemain[0].nama, play_data.pemain[1].nama, play_data.pemain[0].simbol, play_data.pemain[1].simbol, play_data.pemain[0].skor, play_data.pemain[1].skor, play_data.waktu_selesai);
        ReverseSkor(play_data.ukuran, play_data.level);
        GetHighScore(play_data.ukuran, play_data.level);
    }

    MenuUtama();
}

void PlayGame(DataGame *play_data, int *play) {
    Player *pemain = (Player *)malloc(sizeof(Player) * 2);
    int mode, ukuran, menang, papan[7][7];
    int pemain_menang, pemain_kalah;

    mode = (*play_data).mode;
    ukuran = (*play_data).ukuran;
    pemain = (*play_data).pemain;

    char key;

    int saat_ini, w_awal_giliran, sisa_waktu, initial_time;
    struct tm *waktu;
    bool is_bot, kosong;

    int current_giliran, current_selection, last_selection, bot_selection;

    InitPapan(ukuran, &papan);
    GetDatetime(&(*play_data).waktu_mulai);

    menang = 0;
    while (menang == 0) {
        ClearScreen();

        DisplayGame(ukuran);
        PrintSkor(pemain);

        is_bot = false;
        current_giliran = 2;
        current_selection = 1;
        bot_selection = 0;

        saat_ini = time(0);
        w_awal_giliran = saat_ini;

        do {
            // jeda pergantian pemain dari computer
            if ((current_giliran == pemain[1].giliran) && (mode == 1) && (is_bot)) {
                sleep(2);
                current_selection = last_selection;
            }

            ChangeGiliran(&current_giliran, &saat_ini, &w_awal_giliran);
            // print giliran
            PrintGiliran(current_giliran, pemain);
            // print sisa waktu
            PrintSisaWaktu(w_awal_giliran);
            // display papan
            DisplayPapan(ukuran, papan, current_selection);

            // giliran bermain
            if ((current_giliran == pemain[0].giliran) || ((current_giliran == pemain[1].giliran) && (mode == 2))) {
                // jika giliran pemain 1 atau pemain 2 bukan komputer
                is_bot = false;
                // print pesan
                gotoxy(4, 13 + (ukuran * 4) + 3);
                printf("                                            ");

                do {
                    // aksi pemain
                    key = getch();
                    // print sisa waktu
                    PrintSisaWaktu(w_awal_giliran);

                    kosong = false;
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
                    } else if (key == 13) {
                        // Enter
                        kosong = CekSel(current_selection, ukuran, papan);
                    }

                    // display papan
                    DisplayPapan(ukuran, papan, current_selection);
                } while (!(key == 13 && kosong));

                if (GetSisaWaktu(saat_ini, w_awal_giliran) > 0) {
                    PutSimbol(current_selection, current_giliran, ukuran, &papan);
                    menang = CekPapan(ukuran, papan);
                } else {
                    gotoxy(4, 13 + (ukuran * 4) + 3);
                    printf("Waktumu sudah habis! sekarang giliran lawan.");
                    sleep(2);
                }

                if (mode == 1 && menang == 0) {
                    last_selection = current_selection;
                    current_selection = 0;
                }
            } else {
                // jika bot
                is_bot = true;
                // print pesan
                gotoxy(4, 13 + (ukuran * 4) + 3);
                printf("Tunggu Computer meletakkan simbolnya...     ");

                // bot komputer
                bot_selection = Bot(ukuran, papan, (*play_data).level, current_giliran);
                PutSimbol(bot_selection, current_giliran, ukuran, &papan);
                menang = CekPapan(ukuran, papan);
            }

        } while (menang == 0);

        DisplayPapan(ukuran, papan, current_selection);
        sleep(2);
        if (pemain[0].giliran == menang) {
            pemain[0].skor++;
            pemain_menang = 1;
            pemain_kalah = 2;
        } else if (pemain[1].giliran == menang) {
            pemain[1].skor++;
            pemain_menang = 2;
            pemain_kalah = 1;
        } else {
            pemain_menang = 0;
            pemain_kalah = 0;
        }
        *play = EndGame(mode, pemain_menang, pemain_kalah, pemain);
    }
}

void ChangeGiliran(int *giliran, int *saat_ini, int *w_awal_giliran) {
    if (*giliran == 1) {
        *giliran = 2;
    } else {
        *giliran = 1;
    }

    *saat_ini = time(0);
    *w_awal_giliran = *saat_ini;
}

void PrintGiliran(int giliran, Player pemain[2]) {
    gotoxy(4, 12);
    if (giliran == pemain[0].giliran) {
        printf("Giliran: %s (%c)         ", pemain[0].nama, pemain[0].simbol);
    } else {
        printf("Giliran: %s (%c)         ", pemain[1].nama, pemain[1].simbol);
    }
}

void PrintSkor(Player pemain[2]) {
    char skor[10];
    // gabungkan skor menjadi string
    sprintf(skor, "%d - %d", pemain[0].skor, pemain[1].skor);
    // print skor
    gotoxy(48 - (int)(strlen(skor) / 2) + 1, 12);
    printf("%s", skor);
}

int GetSisaWaktu(int saat_ini, int w_awal_giliran) {
    int sisa_waktu;

    sisa_waktu = 10 - (saat_ini - w_awal_giliran);

    return sisa_waktu;
}

void PrintSisaWaktu(int w_awal_giliran) {
    int saat_ini, sisa_waktu;

    saat_ini = time(0);
    sisa_waktu = GetSisaWaktu(saat_ini, w_awal_giliran);

    gotoxy(74, 12);
    printf("Sisa Waktu: %-2d Detik", (sisa_waktu >= 0) ? sisa_waktu : 0);
}

int EndGame(int mode, int pemain_menang, int pemain_kalah, Player pemain[2]) {
    ClearScreen();
    int i;
    int lebar = 94;
    int tinggi = 13;
    char key;
    int current_selection = 1;

    char ket[30];

    gotoxy(4, 12);
    if (pemain_menang == 1) {
        sprintf(ket, "%s (%c) Win The Game!", pemain[0].nama, pemain[0].simbol);
        printf("Good game, %s (%c)!", pemain[0].nama, pemain[0].simbol);
        gotoxy(4, 13);
        printf("Kamu telah mengalahkan %s (%c) dalam permainan ini", pemain[1].nama, pemain[1].simbol);
        gotoxy(4, 15);
        printf("GACOR BANGET BANG!");
    } else if (pemain_menang == 2) {
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
    printf("    %s (%c) : %d", pemain[0].nama, pemain[0].simbol, pemain[0].skor);
    gotoxy(4, 19);
    printf("    %s (%c) : %d", pemain[1].nama, pemain[1].simbol, pemain[1].skor);

    // print header
    gotoxy(1, 1);
    Header(ket);

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

    // print pesan
    gotoxy(1, 25);
    printf("Skor akan tersimpan jika berhenti bermain");

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
                return 2;
            }
        }
    } while (key != 13);
}

void DisplayGame(int ukuran) {
    int i;
    int lebar = 94;
    int tinggi = 3 + (ukuran * 4) + 4;

    char ket[30] = "Game On, Good Luck!";

    // print header
    Header(ket);

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

void InitGame(DataGame *play_data, int *play) {
    int nama, simbol;

    (*play_data).mode = 0;
    while ((*play_data).mode == 0) {
        (*play_data).mode = PilihMode();
        if ((*play_data).mode == -1) break;

        nama = 0;
        while (nama == 0) {
            (*play_data).pemain = InputNama((*play_data).mode);
            if (strcmp((*play_data).pemain[0].nama, "") == 0 && strcmp((*play_data).pemain[1].nama, "") == 0) {
                nama = -1;
                (*play_data).mode = 0;
                break;
            } else {
                nama = 1;
                (*play_data).level = 0;
                while ((*play_data).level == 0) {
                    if ((*play_data).mode == 1) {
                        (*play_data).level = PilihLevel();
                        if ((*play_data).level == -1) {
                            nama = 0;
                            break;
                        }
                    } else {
                        (*play_data).level = 4;
                    }

                    (*play_data).ukuran = 0;
                    while ((*play_data).ukuran == 0) {
                        (*play_data).ukuran = PilihUkuran();
                        if ((*play_data).ukuran == -1) {
                            if ((*play_data).mode == 1) (*play_data).level = 0;
                            if ((*play_data).mode == 2) nama = 0;
                            break;
                        }

                        simbol = 0;
                        while (simbol == 0) {
                            simbol = PilihSimbol();
                            if (simbol == 1) {
                                (*play_data).pemain[0].simbol = 'X';
                                (*play_data).pemain[1].simbol = 'O';
                                (*play_data).pemain[0].giliran = 1;
                                (*play_data).pemain[1].giliran = 2;
                                *play = 1;
                            } else if (simbol == 2) {
                                (*play_data).pemain[0].simbol = 'O';
                                (*play_data).pemain[1].simbol = 'X';
                                (*play_data).pemain[0].giliran = 2;
                                (*play_data).pemain[1].giliran = 1;
                                *play = 1;
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

    if (*play == 1) {
        (*play_data).pemain[0].skor = 0;
        (*play_data).pemain[1].skor = 0;
    }
}

int PilihMode() {
    ClearScreen();

    int jml_opsi, selection;
    char menu[20];

    jml_opsi = 2;
    strcpy(menu, "PILIH MODE BERMAIN");

    char opsi[jml_opsi][20];
    strcpy(opsi[0], "Player vs Computer");
    strcpy(opsi[1], "Player vs Player");

    selection = MenuOpsi(menu, jml_opsi, opsi, true);

    if (selection != 0) {
        return selection;
    } else {
        return -1;
    }
}

struct Player *InputNama(int mode) {
    ClearScreen();
    char nama_pemain_1[11], nama_pemain_2[11];
    Player *pemain = (Player *)malloc(sizeof(Player) * 2);
    int i, n, p, baris;
    int lebar = 94;
    int tinggi = mode + 2;
    char key, menu[20];

    // print header
    strcpy(menu, "MASUKKAN NAMA PEMAIN");
    Header(menu);

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
                nama_pemain_1[n] = key;
            } else {
                nama_pemain_2[n] = key;
            }
            n++;
            printf("%c", key);
            gotoxy(14 + n, 11 + p);
        } else if (key == 13) {  // Enter key
            if (n > 0) {
                if ((mode == 2) && (p == 1)) {
                    nama_pemain_1[n] = '\0';
                    p = 2;
                    n = 0;
                    gotoxy(14 + n, 11 + p);
                } else {
                    if ((mode == 1) && (p == 1)) nama_pemain_1[n] = '\0';
                    if ((mode == 2) && (p == 2)) nama_pemain_2[n] = '\0';
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
        strcpy(pemain[0].nama, nama_pemain_1);

        if (mode == 1) {
            char name2[11] = "Computer";
            name2[sizeof(name2) - 1] = '\0';
            strncpy(pemain[1].nama, name2, sizeof(pemain[1].nama));
        } else {
            strcpy(pemain[1].nama, nama_pemain_2);
        }
        return pemain;
    } else if (key == 27) {
        strcpy(pemain[0].nama, "");
        strcpy(pemain[1].nama, "");
        return pemain;
    }
}

int PilihLevel() {
    ClearScreen();

    int jml_opsi, selection;
    char menu[30];

    jml_opsi = 3;
    strcpy(menu, "PILIH TINGKAT KESULITAN");

    char opsi[jml_opsi][20];
    strcpy(opsi[0], "Easy");
    strcpy(opsi[1], "Medium");
    strcpy(opsi[2], "Hard");

    selection = MenuOpsi(menu, jml_opsi, opsi, true);

    if (selection != 0) {
        return selection;
    } else {
        return -1;
    }
}

int PilihUkuran() {
    ClearScreen();

    int jml_opsi, selection;
    char menu[30];

    jml_opsi = 3;
    strcpy(menu, "PILIH UKURAN PAPAN");

    char opsi[jml_opsi][20];
    strcpy(opsi[0], "3 x 3");
    strcpy(opsi[1], "5 x 5");
    strcpy(opsi[2], "7 x 7");

    selection = MenuOpsi(menu, jml_opsi, opsi, true);

    if (selection != 0) {
        return (selection * 2) + 1;
    } else {
        return -1;
    }
}

int PilihSimbol() {
    ClearScreen();

    int jml_opsi, selection;
    char menu[30];

    jml_opsi = 2;
    strcpy(menu, "PILIH SIMBOL PEMAIN 1");

    char opsi[jml_opsi][20];
    strcpy(opsi[0], "X");
    strcpy(opsi[1], "O");

    selection = MenuOpsi(menu, jml_opsi, opsi, true);

    if (selection != 0) {
        return selection;
    } else {
        return -1;
    }
}