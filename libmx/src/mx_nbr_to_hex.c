#include "libmx.h"

char *mx_nbr_to_hex(unsigned long nbr) {
    int cntr = 0;
    char hexadecimal[100];
    char *res_str = NULL;

    if(nbr == 0)
        return "0";
    while(nbr != 0) {
        if((nbr%16) < 10)
            hexadecimal[cntr++] = 48 + (nbr%16);
        else 
            hexadecimal[cntr++] = 87 + (nbr%16);
        nbr /= 16;
    }
    res_str = mx_strnew(cntr);
    mx_strncpy(res_str, hexadecimal, cntr);
    mx_str_reverse(res_str);
    return res_str;
}
