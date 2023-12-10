#include "datetime.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void ConvertBulan(int i_bulan, char (*t_bulan)[4]) {
    switch (i_bulan) {
        case 0:
            strcpy(*t_bulan, "Jan");
            break;
        case 1:
            strcpy(*t_bulan, "Feb");
            break;
        case 2:
            strcpy(*t_bulan, "Mar");
            break;
        case 3:
            strcpy(*t_bulan, "Apr");
            break;
        case 4:
            strcpy(*t_bulan, "Mei");
            break;
        case 5:
            strcpy(*t_bulan, "Jun");
            break;
        case 6:
            strcpy(*t_bulan, "Jul");
            break;
        case 7:
            strcpy(*t_bulan, "Agu");
            break;
        case 8:
            strcpy(*t_bulan, "Sep");
            break;
        case 9:
            strcpy(*t_bulan, "Okt");
            break;
        case 10:
            strcpy(*t_bulan, "Nov");
            break;
        default:
            strcpy(*t_bulan, "Des");
    }
}

void GetDatetime(char (*datetime)[22]) {
    time_t saat_ini;
    struct tm *w_saat_ini;
    char bulan[4];

    saat_ini = time(0);
    w_saat_ini = localtime(&saat_ini);

    ConvertBulan(w_saat_ini->tm_mon, &bulan);

    snprintf((*datetime), 22, "%02d %s %d, %02d:%02d:%02d", w_saat_ini->tm_mday, bulan, w_saat_ini->tm_year + 1900, w_saat_ini->tm_hour, w_saat_ini->tm_min, w_saat_ini->tm_sec);
}