#include "board.h"

#include <stdio.h>

void init_papan(int ukuran, int (*papan)[7][7]) {
    int baris, kolom;
    baris = 0;

    while (baris < ukuran) {
        kolom = 0;
        while (kolom < ukuran) {
            (*papan)[baris][kolom] = 0;
            kolom++;
        }
        baris++;
    }
}