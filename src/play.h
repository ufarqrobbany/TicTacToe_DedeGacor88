typedef struct Player {
    char nama[10];
    char simbol;
} Player;

void permainan();
int pilih_mode();
struct Player *input_nama(int mode);
int pilih_level();
int pilih_ukuran();
int pilih_simbol();