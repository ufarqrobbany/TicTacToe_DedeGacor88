void FileName(int ukuran, int level, char (*mode)[6], char (*t_level)[6]);
void SaveSkor(int ukuran, int level, char waktu_mulai[22], char nama_p1[11], char nama_p2[11], char simbol_p1, char simbol_p2, int skor_p1, int skor_p2, char waktu_selesai[22]);
int PilihUPSkor();
int PilihModeSkor();
int PilihLevelSkor();
void DisplaySkor(int ukuran, int level);
void PrintTabelSkor(int x, int *baris, char file[30], char nama_tabel[50]);