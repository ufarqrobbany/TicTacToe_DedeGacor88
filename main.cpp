#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "src/common.h"
#include "src/header.h"

void menu_utama();
void menu_riwayat_skor();
void menu_bantuan();
void menu_kredit();

void menu_utama() {
    system("cls||clear");

    int i, baris;
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
                    menu_bantuan();
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

void menu_riwayat_skor() {
    system("cls||clear");

    int i, baris;
    int lebar = 94;
    int tinggi = 14;
    FILE *data;

    char w_mulai[22], w_selesai[22], pemain_1[11], pemain_2[11], pemain[25], skor_1[3], skor_2[3];

    // print header
    char str[] = "RIWAYAT SKOR";
    header(str);

    // print isi konten body
    // print table
    gotoxy(4, 11);
    printf("%c", 201);
    for (i = 0; i < 23; i++) printf("%c", 205);
    printf("%c", 203);
    for (i = 0; i < 26; i++) printf("%c", 205);
    printf("%c", 203);
    for (i = 0; i < 15; i++) printf("%c", 205);
    printf("%c", 203);
    for (i = 0; i < 21; i++) printf("%c", 205);
    printf("%c", 187);

    gotoxy(4, 12);
    printf("%c      Waktu Mulai      %c          Pemain          %c      Skor     %c    Waktu Selesai    %c", 186, 186, 186, 186, 186);

    gotoxy(4, 13);
    printf("%c", 204);
    for (i = 0; i < 23; i++) printf("%c", 205);
    printf("%c", 206);
    for (i = 0; i < 26; i++) printf("%c", 205);
    printf("%c", 206);
    for (i = 0; i < 15; i++) printf("%c", 205);
    printf("%c", 206);
    for (i = 0; i < 21; i++) printf("%c", 205);
    printf("%c", 185);

    // print data
    data = fopen("data/scores.txt", "r");
    baris = 0;
    while (!feof(data)) {
        gotoxy(4, baris + 14);
        fscanf(data, "%[^#]#%[^#]#%[^#]#%[^#]#%[^#]#%[^\n]\n", w_mulai, pemain_1, pemain_2, skor_1, skor_2, w_selesai);
        fflush(stdin);
        printf("%c %-21s %c", 186, w_mulai, 186);
        sprintf(pemain, "%s vs %s", pemain_1, pemain_2);
        printf(" %-24s ", pemain);
        printf("%c", 186);
        gotoxy(62 - (strlen(skor_1) + 1), baris + 14);
        printf(" %s - ", skor_1);
        printf("%s", skor_2);
        for (i = 0; i < 6 - strlen(skor_2); i++) printf(" ");
        printf("%c %-19s %c", 186, w_selesai, 186);
        baris++;
    }
    fclose(data);
    free(data);

    gotoxy(4, baris + 14);
    printf("%c", 200);
    for (i = 0; i < 23; i++) printf("%c", 205);
    printf("%c", 202);
    for (i = 0; i < 26; i++) printf("%c", 205);
    printf("%c", 202);
    for (i = 0; i < 15; i++) printf("%c", 205);
    printf("%c", 202);
    for (i = 0; i < 21; i++) printf("%c", 205);
    printf("%c", 188);
    baris++;

    // print container body yang tinggi nya menyesuaikan konten
    for (i = 11; i < 11 + baris + 3; i++) {
        gotoxy(1, i);
        printf("%c", 186);
        gotoxy(lebar + 2, i);
        printf("%c\n", 186);
    }

    printf("%c", 200);
    for (i = 0; i < lebar; i++) printf("%c", 205);
    printf("%c\n", 188);

    getch();
    menu_utama();
}

void menu_bantuan() {
    system("cls||clear");

    int i, baris, ch;
    int lebar = 94;
    FILE *data;

    // print header
    char str[] = "BANTUAN";
    header(str);

    // print isi konten body
    data = fopen("data/help.txt", "r");
    gotoxy(4, 12);
    baris = 1;
    while ((ch = getc(data)) != EOF) {
        putchar(ch);

        if (ch == '\n') {
            gotoxy(4, baris + 12);
            baris++;
        }
    }
    fclose(data);
    free(data);

    // print container body yang tinggi nya menyesuaikan konten
    for (i = 11; i < 11 + baris + 2; i++) {
        gotoxy(1, i);
        printf("%c", 186);
        gotoxy(lebar + 2, i);
        printf("%c\n", 186);
    }

    printf("%c", 200);
    for (i = 0; i < lebar; i++) printf("%c", 205);
    printf("%c\n", 188);

    getch();
    menu_utama();
}

void menu_kredit() {
    system("cls||clear");

    int i, baris, ch;
    int lebar = 94;
    FILE *data;

    // print header
    char str[] = "KREDIT";
    header(str);

    // print isi konten body
    data = fopen("data/credits.txt", "r");
    gotoxy(4, 12);
    baris = 1;
    while ((ch = getc(data)) != EOF) {
        putchar(ch);

        if (ch == '\n') {
            gotoxy(4, baris + 12);
            baris++;
        }
    }
    fclose(data);
    free(data);

    // print container body yang tinggi nya menyesuaikan konten
    for (i = 11; i < 11 + baris + 2; i++) {
        gotoxy(1, i);
        printf("%c", 186);
        gotoxy(lebar + 2, i);
        printf("%c\n", 186);
    }

    printf("%c", 200);
    for (i = 0; i < lebar; i++) printf("%c", 205);
    printf("%c\n", 188);

    getch();
    menu_utama();
}

int main() {
    menu_utama();
    gotoxy(10, 22);
    return 0;
}