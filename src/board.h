void InitPapan(int ukuran, int (*papan)[7][7]);
void DisplayPapan(int ukuran, int papan[7][7], int selection);
bool CekSel(int letak, int ukuran, int papan[7][7]);
void PutSimbol(int letak, int giliran, int ukuran, int (*papan)[7][7]);
int CekPapan(int ukuran, int papan[7][7]);