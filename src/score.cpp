#include "score.h"

#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "common.h"
#include "menu.h"

void InsertionSortSkor(ScoreData (*data)[1000], int jml) {
    int i, j;
    ScoreData key, temp;
    for (i = 1; i < jml; i++) {
        key = (*data)[i];
        temp = (*data)[i];
        j = i - 1;

        while (j >= 0 && (*data)[j].skor < key.skor) {
            (*data)[j + 1] = (*data)[j];
            j = j - 1;
        }

        (*data)[j + 1] = temp;
    }
}

// cari file
void FileNameSkor(int ukuran, int level, char (*file)[50]) {
    if (ukuran == 3) {
        if (level == 1) strcpy(*file, "comp_3x3_easy.txt");
        if (level == 2) strcpy(*file, "comp_3x3_medi.txt");
        if (level == 3) strcpy(*file, "comp_3x3_hard.txt");
        if (level == 4) strcpy(*file, "player_3x3.txt");
    } else if (ukuran == 5) {
        if (level == 1) strcpy(*file, "comp_5x5_easy.txt");
        if (level == 2) strcpy(*file, "comp_5x5_medi.txt");
        if (level == 3) strcpy(*file, "comp_5x5_hard.txt");
        if (level == 4) strcpy(*file, "player_5x5.txt");
    } else {
        if (level == 1) strcpy(*file, "comp_7x7_easy.txt");
        if (level == 2) strcpy(*file, "comp_7x7_medi.txt");
        if (level == 3) strcpy(*file, "comp_7x7_hard.txt");
        if (level == 4) strcpy(*file, "player_7x7.txt");
    }
}

// simpan skor
void SaveSkor(int ukuran, int level, char waktu_mulai[22], char nama_p1[11], char nama_p2[11], char simbol_p1, char simbol_p2, int skor_p1, int skor_p2, char waktu_selesai[22]) {
    FILE *data;
    char file_s[50], file_sn[50];

    FileNameSkor(ukuran, level, &file_sn);
    sprintf(file_s, "data/scores/%s", file_sn);

    data = fopen(file_s, "a");
    fprintf(data, "%s#%s (%c)#%s (%c)#%d#%d#%s\n", waktu_mulai, nama_p1, simbol_p1, nama_p2, simbol_p2, skor_p1, skor_p2, waktu_selesai);
    fclose(data);
}

// reverse data pada file skor sehingga berurutan ke bawah dari skor terbaru, hasilnya simpan di file yang berbeda
// referensi: https://www.geeksforgeeks.org/c-program-to-reverse-the-content-of-the-file-and-print-it/
void ReverseSkor(int ukuran, int level) {
    FILE *data, *reversed_data;
    char file_s[50], file_rs[50], file_sn[50], file_rsn[50];

    FileNameSkor(ukuran, level, &file_sn);
    FileNameSkor(ukuran, level, &file_rsn);
    sprintf(file_s, "data/scores/%s", file_sn);
    sprintf(file_rs, "data/scores/reversed/%s", file_rsn);

    data = fopen(file_s, "r");
    reversed_data = fopen(file_rs, "w");

    // buf untuk menyimpan data pada setiap baris
    char buffer[1000];
    int baris = 0, i, j;

    if (data != NULL) {
        // hitung jumlah baris
        while (fgets(buffer, sizeof(buffer), data) != NULL) {
            baris++;
        }

        for (i = baris - 1; i >= 0; i--) {
            // kembali ke index 0
            rewind(data);
            for (j = 0; j < i; j++) {
                // baca baris dan abaikan
                fgets(buffer, sizeof(buffer), data);
            }
            // baca baris dan simpan
            fgets(buffer, sizeof(buffer), data);
            fputs(buffer, reversed_data);
        }

        fclose(data);
        fclose(reversed_data);
    }
}

// get high score
void GetHighScore(int ukuran, int level) {
    int i, skor_1, skor_2, valid;
    char w_mulai[22], w_selesai[22], pemain_1[15], pemain_2[15], pemain[32];

    FILE *data_s, *data_hs;
    char file_s[50], file_hs[50], file_sn[50], file_hsn[50];

    FileNameSkor(ukuran, level, &file_sn);
    FileNameSkor(ukuran, level, &file_hsn);
    sprintf(file_s, "data/scores/%s", file_sn);
    sprintf(file_hs, "data/highscores/%s", file_hsn);

    data_s = fopen(file_s, "r");
    data_hs = fopen(file_hs, "w");

    // maksimal 3 data
    ScoreData scores[1000];
    int jml = 0;

    if (data_s != NULL) {
        while (!feof(data_s)) {
            valid = fscanf(data_s, "%[^#]#%[^#]#%[^#]#%d#%d#%[^\n]\n", w_mulai, pemain_1, pemain_2, &skor_1, &skor_2, w_selesai);
            if (valid == 6) {
                sprintf(scores[jml].baris, "%s#%s#%s#%d#%d#%s\n", w_mulai, pemain_1, pemain_2, skor_1, skor_2, w_selesai);
                scores[jml].skor = skor_1;
                jml++;
            }
        }

        InsertionSortSkor(&scores, jml);

        for (i = 0; i < 3; i++) {
            fprintf(data_hs, "%s", scores[i].baris);
        }

        fclose(data_s);
        fclose(data_hs);
    }
}

int PilihUPSkor() {
    ClearScreen();

    int jml_opsi, selection;
    char menu[30];

    jml_opsi = 3;
    strcpy(menu, "LIHAT SKOR PADA UKURAN PAPAN...");

    char opsi[jml_opsi][20];
    strcpy(opsi[0], "3 x 3");
    strcpy(opsi[1], "5 x 5");
    strcpy(opsi[2], "7 x 7");

    selection = MenuOpsi(menu, jml_opsi, opsi, true);

    if (selection != 0) {
        return selection;
    } else {
        return -1;
    }
}

int PilihModeSkor() {
    ClearScreen();

    int jml_opsi, selection;
    char menu[30];

    jml_opsi = 2;
    strcpy(menu, "LIHAT SKOR PADA MODE BERMAIN...");

    char opsi[jml_opsi][20];
    strcpy(opsi[0], "Player vs Computer");
    strcpy(opsi[1], "Player vs Player");

    selection = MenuOpsi(menu, jml_opsi, opsi, true);

    if (selection != 0) {
        return selection;
    } else {
        return -1;
    }
}

int PilihLevelSkor() {
    ClearScreen();

    int jml_opsi, selection;
    char menu[30];

    jml_opsi = 3;
    strcpy(menu, "LIHAT SKOR PADA LEVEL...");

    char opsi[jml_opsi][20];
    strcpy(opsi[0], "Easy");
    strcpy(opsi[1], "Medium");
    strcpy(opsi[2], "Hard");

    selection = MenuOpsi(menu, jml_opsi, opsi, true);

    if (selection != 0) {
        return selection;
    } else {
        return -1;
    }
}

void PrintTabelSkor(int x, int *y, char file[50], char nama_tabel[50]) {
    int i, skor_1, skor_2, jml_data, valid;
    char w_mulai[22], w_selesai[22], pemain_1[15], pemain_2[15], pemain[32];
    FILE *data;

    // print nama tabel
    gotoxy(x, (*y)++);
    printf(nama_tabel);

    // print header tabel
    gotoxy(x, (*y)++);
    printf("%c", 201);
    for (i = 0; i < 23; i++) printf("%c", 205);
    printf("%c", 203);
    for (i = 0; i < 34; i++) printf("%c", 205);
    printf("%c", 203);
    for (i = 0; i < 15; i++) printf("%c", 205);
    printf("%c", 203);
    for (i = 0; i < 23; i++) printf("%c", 205);
    printf("%c", 187);

    gotoxy(x, (*y)++);
    printf("%c      Waktu Mulai      %c              Pemain              %c      Skor     %c     Waktu Selesai     %c", 186, 186, 186, 186, 186);

    gotoxy(x, (*y)++);
    printf("%c", 204);
    for (i = 0; i < 23; i++) printf("%c", 205);
    printf("%c", 206);
    for (i = 0; i < 34; i++) printf("%c", 205);
    printf("%c", 206);
    for (i = 0; i < 15; i++) printf("%c", 205);
    printf("%c", 206);
    for (i = 0; i < 23; i++) printf("%c", 205);
    printf("%c", 185);

    // print data
    data = fopen(file, "r");

    jml_data = 0;
    if (data != NULL) {
        while (!feof(data) && (jml_data < 30)) {
            valid = fscanf(data, "%[^#]#%[^#]#%[^#]#%d#%d#%[^\n]\n", w_mulai, pemain_1, pemain_2, &skor_1, &skor_2, w_selesai);
            if (valid == 6) {
                // print waktu mulai
                gotoxy(x, *y);
                printf("%c %-21s %c", 186, w_mulai, 186);
                // print nama pemain dan simbolnya
                printf(" %s vs %s ", pemain_1, pemain_2);
                // print skor
                gotoxy(x + 59, *y);
                printf("%c %d - %d", 186, skor_1, skor_2);
                // print waktu selesai
                gotoxy(x + 75, *y);
                printf("%c %-21s %c", 186, w_selesai, 186);
                (*y)++;
                jml_data++;
            }
        }
        fclose(data);
    } else {
        gotoxy(x, (*y) + 1);
        printf("Tidak ada file");
    }

    // print penutup tabel
    gotoxy(x, (*y)++);
    printf("%c", 200);
    for (i = 0; i < 23; i++) printf("%c", 205);
    printf("%c", 202);
    for (i = 0; i < 34; i++) printf("%c", 205);
    printf("%c", 202);
    for (i = 0; i < 15; i++) printf("%c", 205);
    printf("%c", 202);
    for (i = 0; i < 23; i++) printf("%c", 205);
    printf("%c", 188);
}

void DisplaySkor(int ukuran, int level) {
    ClearScreen();

    int x, y;
    int lebar = 94;
    char key, tabel[50], file_s[50], file_hs[50], file_sn[50], file_hsn[50];

    FileNameSkor(ukuran, level, &file_sn);
    FileNameSkor(ukuran, level, &file_hsn);
    sprintf(file_s, "data/scores/reversed/%s", file_sn);
    sprintf(file_hs, "data/highscores/%s", file_hsn);

    printf("SKOR %d x %d, %s%s", ukuran, ukuran, (level == 4) ? "VS PLAYER" : "VS COMPUTER", (level == 1) ? ", EASY" : ((level == 2) ? ", MEDIUM" : ((level == 3) ? ", HARD" : "")));

    // print tabel
    x = 1;
    y = 3;
    strcpy(tabel, "SKOR TERTINGGI - TOP 3");
    PrintTabelSkor(x, &y, file_hs, tabel);
    y++;
    strcpy(tabel, "RIWAYAT SKOR (30 Permainan Terakhir)");
    PrintTabelSkor(x, &y, file_s, tabel);

    gotoxy(1, y + 1);
    printf("Tekan ESC untuk kembali...");

    do {
        key = getch();
    } while (key != 27);  // selama tidak menekan tombol ESC
}
