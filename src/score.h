typedef struct ScoreData {
    char baris[1000];
    int skor;
} ScoreData;

void FileNameSkor(int ukuran, int level, char (*file)[50]);
void SaveSkor(int ukuran, int level, char waktu_mulai[22], char nama_p1[11], char nama_p2[11], char simbol_p1, char simbol_p2, int skor_p1, int skor_p2, char waktu_selesai[22]);
int PilihUPSkor();
int PilihModeSkor();
int PilihLevelSkor();
void DisplaySkor(int ukuran, int level);
void PrintTabelSkor(int x, int *baris, char file[50], char nama_tabel[50]);
void ReverseSkor(int ukuran, int level);
void GetHighScore(int ukuran, int level);
void InsertionSortSkor(ScoreData (*data)[1000], int jml);
