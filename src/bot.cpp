#include "bot.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "board.h"

int bot(int ukuran, int papan[7][7]) {
    int batasBawah, batasAtas, letak;
    bool kosong;

    batasBawah = 1;
    batasAtas = ukuran * ukuran;

    do {
        srand(time(0));
        letak = (rand() % batasAtas) + batasBawah;
        kosong = cek_sel(letak, ukuran, papan);
    } while (!kosong);

    return letak;
}