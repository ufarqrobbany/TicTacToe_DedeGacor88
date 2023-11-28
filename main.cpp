#include <conio.h>
#include <stdio.h>
#include <windows.h>

#include "src/common.h"
#include "src/header.h"

void menu_utama();
void menu_kredit();
void menu_riwayat_skor();

void menu_utama() {
    system("cls||clear");

    int i;
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

        // navigasi menu
        key = getch();
        if ((key == 72) && (current_selection > 1)) {
            current_selection -= 1;
        } else if ((key == 80) && (current_selection < 5)) {
            current_selection += 1;
        } else if ((key == 13)) {
            switch (current_selection) {
                case 1:
                    menu_kredit();
                    break;
                case 2:
                    menu_riwayat_skor();
                    break;
                case 3:
                    menu_kredit();
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

void menu_kredit() {
    system("cls||clear");

    int i, ch;
    int lebar = 94;
    int tinggi = 14;
    FILE *data;

    // print header
    char str[] = "KREDIT";
    header(str);

    // print body
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
    data = fopen("data/credits.txt", "r");
    gotoxy(4, 12);
    i = 1;
    while ((ch = getc(data)) != EOF) {
        putchar(ch);

        if (ch == '\n') {
            gotoxy(4, i + 12);
            i++;
        }
    }
    fclose(data);

    getch();
    menu_utama();
}

void menu_riwayat_skor() {
    system("cls||clear");

    int i, ch;
    int lebar = 94;
    int tinggi = 14;
    FILE *data;

    // print header
    char str[] = "SKOR TERTINGGI";
    header(str);

    // print body
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
    data = fopen("data/scores.txt", "r");
    gotoxy(4, 12);
    i = 1;
    putchar(ch);
    while ((ch = getc(data)) != EOF) {
        if (ch == '\n') {
            gotoxy(4, i + 12);
            i++;
        }
        putchar(ch);
    }
    fclose(data);
    free(data);

    getch();
    menu_utama();
}

int main() {
    menu_utama();
    gotoxy(10, 22);
    return 0;
}