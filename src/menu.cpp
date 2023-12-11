#include "menu.h"

#include <conio.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "game.h"
#include "header.h"
#include "score.h"

int MenuOpsi(char nama_menu[20], int jml_opsi, char opsi[10][20], bool can_back) {
    int i, x, y, lebar, tinggi, current_selection;
    char key;

    lebar = 94;
    tinggi = jml_opsi + 2;
    current_selection = 1;

    // print header
    Header(nama_menu);

    // print body menu
    for (y = 11; y < 11 + tinggi; y++) {
        gotoxy(1, y);
        printf("%c", 186);
        gotoxy(lebar + 2, y);
        printf("%c\n", 186);
    }

    printf("%c", 200);
    for (x = 0; x < lebar; x++) printf("%c", 205);
    printf("%c\n", 188);

    // print isi body
    do {
        for (i = 0; i < jml_opsi; i++) {
            y = i + 12;
            gotoxy(4, y);
            printf("%c %s", (current_selection == i + 1) ? 254 : ' ', opsi[i]);
        }

        gotoxy(1, y + 3);
        printf("Gunakan tombol panah untuk navigasi. Tekan Enter untuk konfirmasi.");

        if (can_back) {
            gotoxy(1, y + 4);
            printf("Tekan ESC untuk kembali...");
        }

        // navigasi menu
        key = getch();

        if ((key == 72) && (current_selection > 1)) {
            current_selection -= 1;
        } else if ((key == 80) && (current_selection < jml_opsi)) {
            current_selection += 1;
        } else if (key == 13) {
            return current_selection;
        } else if (key == 27 && can_back) {
            return -1;
        }

    } while (key != 13 || !(key == 27 && can_back));
}

void MenuUtama() {
    ClearScreen();

    int jml_opsi, selection;
    char menu[20];

    jml_opsi = 5;
    strcpy(menu, "MENU UTAMA");

    char opsi[jml_opsi][20];
    strcpy(opsi[0], "Mulai Permainan");
    strcpy(opsi[1], "Riwayat Skor");
    strcpy(opsi[2], "Bantuan");
    strcpy(opsi[3], "Kredit");
    strcpy(opsi[4], "Keluar");

    selection = MenuOpsi(menu, jml_opsi, opsi, false);

    switch (selection) {
        case 1:
            Game();
            break;
        case 2:
            MenuRiwayatSkor();
            break;
        case 3:
            MenuBantuan();
            break;
        case 4:
            MenuKredit();
            break;
        case 5:
            break;
    }
}

void MenuRiwayatSkor() {
    int ukuran_papan, mode, level;

    ukuran_papan = 0;
    while (ukuran_papan == 0) {
        ukuran_papan = PilihUPSkor();
        if (ukuran_papan == -1) break;

        mode = 0;
        while (mode == 0) {
            mode = PilihModeSkor();
            if (mode == -1) {
                ukuran_papan = 0;
                break;
            }

            level = 0;
            while (level == 0) {
                if (mode == 1) {
                    level = PilihLevelSkor();
                    if (level == -1) {
                        mode = 0;
                        break;
                    }
                } else {
                    level = 4;
                }
                DisplaySkor((ukuran_papan * 2) + 1, level);
                if (mode == 1) {
                    level = 0;
                } else {
                    mode = 0;
                }
            }
        }
    }

    MenuUtama();
}

void MenuBantuan() {
    ClearScreen();

    int y;
    char key, ch;
    FILE *data;

    // print data
    data = fopen("data/help.txt", "r");
    y = 1;
    gotoxy(1, y);
    if (data != NULL) {
        while ((ch = getc(data)) != EOF) {
            putchar(ch);

            if (ch == '\n') {
                y++;
                gotoxy(1, y);
            }
        }
        fclose(data);
    } else {
        printf("Tidak ada file");
    }

    gotoxy(1, y + 2);
    printf("Tekan ESC untuk kembali...");

    do {
        key = getch();
    } while (key != 27);  // selama tidak menekan tombol ESC

    MenuUtama();
}

void MenuKredit() {
    ClearScreen();

    int i, x, y;
    int lebar = 94;
    char key, ch, text[100];
    FILE *data;

    // print header
    strcpy(text, "KREDIT");
    Header(text);

    gotoxy(1, 11);
    printf("%c", 186);
    gotoxy(lebar + 2, 11);
    printf("%c\n", 186);

    // print data
    data = fopen("data/credits.txt", "r");
    x = 4;
    y = 12;
    if (data != NULL) {
        while (!feof(data)) {
            ch = getc(data);

            gotoxy(x, y);
            putchar(ch);
            x++;

            if ((ch == '\n') || (ch == EOF)) {
                gotoxy(1, y);
                printf("%c", 186);
                gotoxy(lebar + 2, y);
                printf("%c\n", 186);
                x = 4;
                y++;
            }
        }
        fclose(data);
    } else {
        gotoxy(1, y++);
        printf("%c %-92s %c", 186, "Tidak ada file", 186);
    }

    gotoxy(1, y);
    printf("%c", 186);
    gotoxy(lebar + 2, y);
    printf("%c\n", 186);
    y++;

    gotoxy(1, y);
    printf("%c", 200);
    for (i = 0; i < lebar; i++) printf("%c", 205);
    printf("%c\n", 188);

    printf("Tekan ESC untuk kembali...");

    do {
        key = getch();
    } while (key != 27);  // selama tidak menekan tombol ESC

    MenuUtama();
}
