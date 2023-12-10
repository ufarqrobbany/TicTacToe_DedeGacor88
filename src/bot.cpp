#include "bot.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "board.h"

int Bot(int ukuran, int papan[7][7]) {
    int batas_bawah, batas_atas, letak;
    bool kosong;

    batas_bawah = 1;
    batas_atas = ukuran * ukuran;

    do {
        srand(time(0));
        letak = (rand() % batas_atas) + batas_bawah;
        kosong = CekSel(letak, ukuran, papan);
    } while (!kosong);

    return letak;
}