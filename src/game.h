#include <stdlib.h>

typedef struct Player {
    char nama[11];
    char simbol;
    int giliran;
    int skor;
} Player;

typedef struct DataGame {
    int mode;
    int level;
    int ukuran;
    char waktu_mulai[22];
    char waktu_selesai[22];
    Player *pemain = (Player *)malloc(sizeof(Player) * 2);
} DataGame;

void Game();
void DisplayGame(int ukuran);
void PlayGame(DataGame *play_data, int *play);
void ChangeGiliran(int *giliran, int *saat_ini, int *w_awal_giliran);
void PrintGiliran(int giliran, Player pemain[2]);
void PrintSkor(Player pemain[2]);
void PrintSisaWaktu(int w_awal_giliran);
int GetSisaWaktu(int saat_ini, int w_awal_giliran);
int EndGame(int mode, int pemainMenang, int pemainKalah, Player pemain[2]);

void InitGame(DataGame *play_data, int *main);
int PilihMode();
struct Player *InputNama(int mode);
int PilihLevel();
int PilihUkuran();
int PilihSimbol();