typedef struct {
    char nama[10];
    char simbol;
} Player;

void permainan();
void pilih_mode(int *mode);
void input_nama(int mode, Player *pemain_1, Player *pemain_2);
void pilih_level(int *level);
void pilih_ukuran(int *ukuran);
void pilih_simbol(Player *pemain_1, Player *pemain_2);