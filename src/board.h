void init_papan(int ukuran, int (*papan)[7][7]);
void display_papan(int ukuran, int papan[7][7], int selection);
bool cek_sel(int letak, int ukuran, int papan[7][7]);
void put_simbol(int letak, int giliran, int ukuran, int (*papan)[7][7]);