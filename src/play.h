typedef struct Player {
    char nama[11];
    char simbol;
    int giliran;
    int skor;
} Player;

void permainan();
int pilih_mode();
struct Player *input_nama(int mode);
int pilih_level();
int pilih_ukuran();
int pilih_simbol();
void menu_permainan(Player pemain[2], int ukuran);
int akhir_permainan(int mode, int pemainMenang, int pemainKalah, Player pemain[2]);