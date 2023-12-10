// File umum yang mungkin berisi definisi konstanta, dan fungsi utilitas yang digunakan secara global di proyek.
#include "common.h"

#include <stdio.h>
#include <windows.h>

// gotoxy, untuk mengatur lokasi kursor
// https://www.quora.com/Why-am-I-not-able-to-use-a-gotoxy-statement-in-C-while-working-in-Code-Blocks
void gotoxy(int x, int y) {
    printf("%c[%d;%df", 0x1B, y, x);
}

void clear_screen() {
    system("cls");
}