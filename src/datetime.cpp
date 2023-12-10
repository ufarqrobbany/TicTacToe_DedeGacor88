#include "datetime.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void convertBulan(int ibulan, char (*tbulan)[4]) {
    switch (ibulan) {
        case 0:
            strcpy(*tbulan, "Jan");
            break;
        case 1:
            strcpy(*tbulan, "Feb");
            break;
        case 2:
            strcpy(*tbulan, "Mar");
            break;
        case 3:
            strcpy(*tbulan, "Apr");
            break;
        case 4:
            strcpy(*tbulan, "Mei");
            break;
        case 5:
            strcpy(*tbulan, "Jun");
            break;
        case 6:
            strcpy(*tbulan, "Jul");
            break;
        case 7:
            strcpy(*tbulan, "Agu");
            break;
        case 8:
            strcpy(*tbulan, "Sep");
            break;
        case 9:
            strcpy(*tbulan, "Okt");
            break;
        case 10:
            strcpy(*tbulan, "Nov");
            break;
        default:
            strcpy(*tbulan, "Des");
    }
}

// Modified to return a char array instead of a pointer
// and taking a char array as an argument to store the result
void get_datetime(char (*datetime)[22]) {
    time_t saat_ini;
    struct tm *w_saat_ini;
    char bulan[4];

    saat_ini = time(0);
    w_saat_ini = localtime(&saat_ini);

    convertBulan(w_saat_ini->tm_mon, &bulan);

    // Use snprintf to avoid buffer overflow and format the string
    snprintf((*datetime), 22, "%d %s %d, %d:%d:%d", w_saat_ini->tm_year + 1900, bulan, w_saat_ini->tm_mday, w_saat_ini->tm_hour, w_saat_ini->tm_min, w_saat_ini->tm_sec);
}