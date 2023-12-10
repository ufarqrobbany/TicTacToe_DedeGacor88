#include "bot.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "board.h"

int Bot(int ukuran, int papan[7][7], int level, int giliran) {
    int letak;

    if (level == 1) {
        letak = RandomBot(ukuran, papan);
    } else if (level == 2) {
        // medium
        letak = MediumBot(ukuran, papan, giliran);
    } else {
        // hard
        letak = HardBot(ukuran, papan, giliran);
    }

    return letak;
}

int RandomBot(int ukuran, int papan[7][7]) {
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

int CekPotentialWin(int ukuran, int papan[7][7], int giliran) {
    // Cek baris dan kolom
    for (int i = 0; i < ukuran; ++i) {
        int countBaris = 0, countKolom = 0;
        for (int j = 0; j < ukuran; ++j) {
            if (papan[i][j] == giliran) {
                countBaris++;
            }
            if (papan[j][i] == giliran) {
                countKolom++;
            }
        }
        if (countBaris == ukuran - 1) {
            for (int j = 0; j < ukuran; ++j) {
                if (papan[i][j] == 0) {
                    return i * ukuran + j + 1;
                }
            }
        }
        if (countKolom == ukuran - 1) {
            for (int j = 0; j < ukuran; ++j) {
                if (papan[j][i] == 0) {
                    return j * ukuran + i + 1;
                }
            }
        }
    }

    // Cek diagonal
    int countDiagonal = 0;
    for (int i = 0; i < ukuran; ++i) {
        if (papan[i][i] == giliran) {
            countDiagonal++;
        }
    }
    if (countDiagonal == ukuran - 1) {
        for (int i = 0; i < ukuran; ++i) {
            if (papan[i][i] == 0) {
                return i * ukuran + i + 1;
            }
        }
    }

    // Cek anti-diagonal
    int countAntiDiagonal = 0;
    for (int i = 0; i < ukuran; ++i) {
        if (papan[i][ukuran - i - 1] == giliran) {
            countAntiDiagonal++;
        }
    }
    if (countAntiDiagonal == ukuran - 1) {
        for (int i = 0; i < ukuran; ++i) {
            if (papan[i][ukuran - i - 1] == 0) {
                return i * ukuran + (ukuran - i - 1) + 1;
            }
        }
    }

    return -1;  // Tidak ada potensi kemenangan atau blokir
}

int MediumBot(int ukuran, int papan[7][7], int giliran) {
    // Fungsi untuk bot tingkat medium
    int letak;

    // Cek potensi kemenangan lawan dan blokir
    letak = CekPotentialWin(ukuran, papan, 3 - giliran);
    if (letak != -1) {
        return letak;
    }

    // Jika tidak ada potensi kemenangan lawan, gunakan bot acak
    return RandomBot(ukuran, papan);
}

int HardBot(int ukuran, int papan[7][7], int giliran) {
    // Fungsi untuk bot tingkat hard
    int letak;

    // Cek potensi kemenangan sendiri
    letak = CekPotentialWin(ukuran, papan, giliran);
    if (letak != -1) {
        return letak;
    }

    // Cek potensi kemenangan lawan dan blokir
    letak = CekPotentialWin(ukuran, papan, 3 - giliran);
    if (letak != -1) {
        return letak;
    }

    // Jika tidak ada potensi kemenangan atau blokir lawan, gunakan bot acak
    return RandomBot(ukuran, papan);
}