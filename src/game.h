#include <stdlib.h>

typedef struct Player {
    char nama[11];
    char simbol;
    int giliran;
    int skor;
} Player;

typedef struct Game {
    int mode;
    int level;
    int ukuran;
    char waktu_mulai[22];
    char waktu_selesai[22];
    Player *pemain = (Player *)malloc(sizeof(Player) * 2);
} Game;

void game();
void display_game(Player pemain[2], int ukuran);
void play(Game *play_data, int *main);
void change_giliran(int *giliran);
void print_giliran(int giliran, Player pemain[2]);
void print_skor(Player pemain[2]);
int end_game(int mode, int pemainMenang, int pemainKalah, Player pemain[2]);

void init_game(Game *play_data, int *main);
int pilih_mode();
struct Player *input_nama(int mode);
int pilih_level();
int pilih_ukuran();
int pilih_simbol();