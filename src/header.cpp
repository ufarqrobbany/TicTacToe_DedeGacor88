#include "header.h"

#include <conio.h>
#include <stdio.h>
#include <string.h>

#include "common.h"

// header, untuk menampilkan header judul permainan
void header(char subheader[30]) {
    int i;
    int baris = 1;
    int lebar = 94;
    int tinggi = 6;

    // print kotak header
    printf("%c", 201);
    for (i = 0; i < lebar; i++) printf("%c", 205);
    printf("%c\n", 187);

    baris = 2;
    for (i = 0; i < tinggi; i++) {
        printf("%c", 186);
        gotoxy(lebar + 2, baris++);
        printf("%c\n", 186);
    }

    printf("%c", 204);
    for (i = 0; i < lebar; i++) printf("%c", 205);
    printf("%c\n", 185);
    baris++;

    // print kotak sub header
    printf("%c", 186);
    gotoxy(lebar + 2, baris++);
    printf("%c\n", 186);

    printf("%c", 204);
    for (i = 0; i < lebar; i++) printf("%c", 205);
    printf("%c\n", 185);

    // printf judul permainan TIC TAC TOE pada header
    huruf_t(3, 2);
    huruf_i(15, 2);
    huruf_c(19, 2);

    huruf_t(30, 2);
    huruf_a(42, 2);
    huruf_c(52, 2);

    huruf_t(63, 2);
    huruf_o(75, 2);
    huruf_e(85, 2);

    // print tim pengembang
    gotoxy(3, tinggi + 1);
    printf("DedeGacor88");

    // print judul pada sub header
    int p_subheader = strlen(subheader);
    gotoxy((lebar / 2) - (p_subheader / 2) + 2, baris - 1);
    printf("%s", subheader);
}

// print huruf T
void huruf_t(int x, int y) {
    int i;

    // baris 1
    gotoxy(x, y++);
    printf("%c", 201);
    for (i = 0; i < 10; i++) printf("%c", 205);
    printf("%c", 187);

    // baris 2
    gotoxy(x, y++);
    printf("%c%c%c%c%c  %c%c%c%c%c", 200, 205, 205, 205, 187, 201, 205, 205, 205, 188);

    // baris 3 - 4
    for (i = 0; i < 2; i++) {
        gotoxy(x + 4, y++);
        printf("%c  %c", 186, 186);
    }

    // baris 5
    gotoxy(x + 4, y++);
    printf("%c%c%c%c", 200, 205, 205, 188);
}

// print huruf I
void huruf_i(int x, int y) {
    int i;

    // baris 1
    gotoxy(x, y++);
    printf("%c%c%c%c", 201, 205, 205, 187);

    // baris 2 - 4
    for (i = 0; i < 3; i++) {
        gotoxy(x, y++);
        printf("%c  %c", 186, 186);
    }

    // baris 5
    gotoxy(x, y++);
    printf("%c%c%c%c", 200, 205, 205, 188);
}

// print huruf C
void huruf_c(int x, int y) {
    int i;

    // baris 1
    gotoxy(x, y++);
    printf("%c", 201);
    for (i = 0; i < 8; i++) printf("%c", 205);
    printf("%c", 187);

    // baris 2
    gotoxy(x, y++);
    printf("%c  %c", 186, 201);
    for (i = 0; i < 5; i++) printf("%c", 205);
    printf("%c", 188);

    // baris 3
    gotoxy(x, y++);
    printf("%c  %c", 186, 186);

    // baris 4
    gotoxy(x, y++);
    printf("%c  %c", 186, 200);
    for (i = 0; i < 5; i++) printf("%c", 205);
    printf("%c", 187);

    // baris 5
    gotoxy(x, y++);
    printf("%c", 200);
    for (i = 0; i < 8; i++) printf("%c", 205);
    printf("%c", 188);
}

// print huruf A
void huruf_a(int x, int y) {
    int i;

    // baris 1
    gotoxy(x, y++);
    printf("%c", 201);
    for (i = 0; i < 8; i++) printf("%c", 205);
    printf("%c", 187);

    // baris 2
    gotoxy(x, y++);
    printf("%c  %c%c%c%c  %c", 186, 201, 205, 205, 187, 186);

    // baris 3
    gotoxy(x, y++);
    printf("%c  %c%c%c%c  %c", 186, 200, 205, 205, 188, 186);

    // baris 4
    gotoxy(x, y++);
    printf("%c  %c%c%c%c  %c", 186, 201, 205, 205, 187, 186);

    // baris 5
    gotoxy(x, y++);
    printf("%c%c%c%c  %c%c%c%c", 200, 205, 205, 188, 200, 205, 205, 188);
}

// print huruf O
void huruf_o(int x, int y) {
    int i;

    // baris 1
    gotoxy(x, y++);
    printf("%c", 201);
    for (i = 0; i < 8; i++) printf("%c", 205);
    printf("%c", 187);

    // baris 2
    gotoxy(x, y++);
    printf("%c  %c%c%c%c  %c", 186, 201, 205, 205, 187, 186);

    // baris 3
    gotoxy(x, y++);
    printf("%c  %c  %c  %c", 186, 186, 186, 186);

    // baris 4
    gotoxy(x, y++);
    printf("%c  %c%c%c%c  %c", 186, 200, 205, 205, 188, 186);

    // baris 5
    gotoxy(x, y++);
    printf("%c", 200);
    for (i = 0; i < 8; i++) printf("%c", 205);
    printf("%c", 188);
}

// print huruf E
void huruf_e(int x, int y) {
    int i;

    // baris 1
    gotoxy(x, y++);
    printf("%c", 201);
    for (i = 0; i < 8; i++) printf("%c", 205);
    printf("%c", 187);

    // baris 2
    gotoxy(x, y++);
    printf("%c      %c%c%c", 186, 201, 205, 188);

    // baris 3
    gotoxy(x, y++);
    printf("%c  %c%c%c%c%c", 186, 201, 205, 205, 205, 188);

    // baris 4
    gotoxy(x, y++);
    printf("%c  %c", 186, 200);
    for (i = 0; i < 5; i++) printf("%c", 205);
    printf("%c", 187);

    // baris 5
    gotoxy(x, y++);
    printf("%c", 200);
    for (i = 0; i < 8; i++) printf("%c", 205);
    printf("%c", 188);
}