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
        // letak = CariLangkahTerbaik(ukuran, papan, giliran);
        letak = computerMove(ukuran, papan, giliran);
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

// Alpha:  nilai terbaik yang pemain harapkan saat ini atau lebih baik. Awalnya disetel ke nilai yang sangat buruk.
// Beta: Ini adalah nilai terbaik yang pemain 'O' harapkan saat ini atau lebih baik. Awalnya disetel ke nilai yang sangat baik.
// Depth: Ini adalah seberapa dalam kita telah menjelajahi pohon permainan. Semakin dalam, semakin banyak langkah atau kedalaman yang diperiksa algoritma.

// // fungsi minimax dengan alpha-beta pruning
// int Minimax(int ukuran, int papan[7][7], int depth, int is_max, int alpha, int beta) {
//     int i, j;
//     int score;

//     // evaluasi semua langkah
//     for (i = 0; i < ukuran; i++) {
//         for (j = 0; j < ukuran; j++) {
//             if (papan[i][j] == 0) {
//                 if (is_max) {
//                     papan[i][j] = 1;
//                     score = Minimax(ukuran, papan, depth + 1, !is_max, alpha, beta);
//                     alpha = alpha > score ? alpha : score;
//                 } else {
//                     papan[i][j] = 2;
//                     score = Minimax(ukuran, papan, depth + 1, !is_max, alpha, beta);
//                     beta = beta < score ? beta : score;
//                 }

//                 // reset nilai papan
//                 papan[i][j] = 0;

//                 // pemangkasan alpha-beta
//                 if (beta <= alpha)
//                     break;
//             }
//         }
//     }

//     // kembalikan skor terbaik
//     return is_max ? alpha : beta;
// }

// // cari langkah terbaik berdasarkan algoritma minimax
// int CariLangkahTerbaik(int ukuran, int papan[7][7], int giliran) {
//     int nilai_terbaik, langkah_terbaik, i, j, nilai_langkah;

//     nilai_terbaik = -99;
//     langkah_terbaik = -1;

//     for (i = 0; i < ukuran; i++) {
//         for (j = 0; j < ukuran; j++) {
//             if (papan[i][j] == 0) {
//                 papan[i][j] = giliran;
//                 nilai_langkah = Minimax(ukuran, papan, 0, 0, -99, 99);
//                 papan[i][j] = 0;

//                 if (nilai_langkah > nilai_terbaik) {
//                     langkah_terbaik = i * ukuran + j + 1;
//                     nilai_terbaik = nilai_langkah;
//                 }
//             }
//         }
//     }

//     return langkah_terbaik;
// }

int minimax(int ukuran, int papan[7][7], int giliran) {
    int move, score, this_score, i, j;

    move = -1;
    score = -2;

    for (i = 0; i < ukuran; i++) {
        for (j = 0; j < ukuran; j++) {
            if (papan[i][j] == 0) {
                papan[i][j] = giliran;
                this_score = -minimax(ukuran, papan, giliran * -1);

                if (this_score > score) {
                    score = this_score;
                    move = i * ukuran + j + 1;
                }

                papan[i][j] = 0;
            }
        }
    }

    if (move == -1) return 0;
    return score;
}

int computerMove(int ukuran, int papan[7][7], int giliran) {
    int move, score, temp_score, i, j;

    move = -1;
    score = -2;

    for (i = 0; i < ukuran; i++) {
        for (j = 0; j < ukuran; j++) {
            if (papan[i][j] == 0) {
                papan[i][j] = giliran;
                int temp_score = -minimax(ukuran, papan, giliran * -1);
                papan[i][j] = 0;
                if (temp_score > score) {
                    score = temp_score;
                    move = i * ukuran + j + 1;
                }
            }
        }
    }

    return move;
}